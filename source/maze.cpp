#include "maze.h"
#include "main.h"
#include <bits/stdc++.h>

using namespace std;

pair<int, int> find(pair<int, int> i, vector<vector<pair<int, int>>> &parent){
    while(parent[i.first][i.second] != i){
        i = parent[i.first][i.second];
    }
    return i;
}

void kruskal(map<pair<int, int>, vector<pair<int, int>>>  &graph, int vertex_count, vector<pair<pair<int, int>, pair<int, int>>> &edges){
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(edges.begin(), edges.end(), default_random_engine(seed));

    vector<vector<pair<int, int>>> parent(vertex_count, vector<pair<int, int>>(vertex_count));
    for(int y=0; y<vertex_count; y++){
        for(int x=0; x<vertex_count; x++){
            parent[y][x] = make_pair(y, x);
        }
    }

    while(edges.size() > 0){
        pair<pair<int, int>, pair<int, int>> edge = edges[edges.size()-1];
        pair<int, int> v1 = edge.first;
        pair<int, int> v2 = edge.second;
        
        pair<int, int> parent_v1 = find(v1, parent);
        pair<int, int> parent_v2 = find(v2, parent);
        if(parent_v1 != parent_v2){
            // union 
            parent[parent_v1.first][parent_v1.second] = parent_v2;
            graph[v1].push_back(v2);
            graph[v2].push_back(v1);
        }

        edges.pop_back();
    } 
}


Maze::Maze(int vertices){
    this->position = glm::vec3(0, 0, 0);
    int v = vertices; // v*v maze
    vector<pair<pair<int, int>, pair<int, int>>> edges;
    // coordinates are stored as (y,x)
    for(int y=0; y<v; y++){
        for(int x=0; x<v; x++){
            // left
            if(x-1 >= 0){
                edges.push_back(make_pair(make_pair(y, x), make_pair(y, x-1)));
            }
            // right
            if(x+1 < v){
                edges.push_back(make_pair(make_pair(y, x), make_pair(y, x+1)));
            }
            // top
            if(y-1 >= 0){
                edges.push_back(make_pair(make_pair(y, x), make_pair(y-1, x)));
            }
            // bottom
            if(y+1 < v){
                edges.push_back(make_pair(make_pair(y, x), make_pair(y+1, x)));
            }
        }
    }

    // map<pair<int, int>, map<pair<int, int>, int>> graph;
    // map<pair<int, int>, vector<pair<int, int>>> graph;
    
    kruskal(this->graph, v, edges);

    for(int y=0; y<v; y++){
        for(int x=0; x<v; x++){
            vector<pair<int, int>> nodes = this->graph[make_pair(y, x)];
            cout << "(" << x << " " << y << "): ";
            bool top, bottom, left, right;
            top = bottom = left = right = true;
            for(auto n: nodes){
                int xn = n.second;
                int yn = n.first;
                if((xn < x) && (yn == y)){
                    left = false;
                }
                else if((xn > x) && (yn == y)){
                    right = false;
                }
                else if((xn == x) && (yn < y)){
                    top = false;
                }
                else if((xn == x) && (yn > y)){
                    bottom = false;
                }
                cout << "(" << n.second << ", " << n.first << "), ";
            }
            cout << top << " " << bottom << " " << left << " " << right << endl;
            this->cells.push_back(Cell(y, x, top, bottom, left, right));
        }
    }
    
    this->player = Character(0,0,false);
    this->imposter = Character(5,0,true);
}

void Maze::draw(glm::mat4 VP){
    // Matrices.model = glm::mat4(1.0f);
    // // glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 translate = glm::translate (glm::vec3(this->position));    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    // glm::mat4 MVP = VP * Matrices.model;
    // glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    for(auto cell: this->cells){
        cell.draw(VP);
    }
    this->player.draw(VP);
    this->imposter.draw(VP);
}

void Maze::tick_input(GLFWwindow *window) {
    this->player.tick_input(window, this->graph);    
    this->imposter.findPlayerAndMove(this->player, this->graph);
}