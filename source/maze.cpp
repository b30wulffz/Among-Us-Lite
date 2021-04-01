#include "maze.h"
#include "main.h"
#include "item.h"
#include <bits/stdc++.h>

using namespace std;

bool verifyOverlap(float x1, float y1, float x2, float y2){
    int xa = x1 + 0.5;
    int ya = y1 + 0.5;
    int xb = x2 + 0.5;
    int yb = y2 + 0.5;
    if(xa == xb && ya == yb){
        return true;
    }
    return false;
}

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

int Maze::getTimeLeft(){
    if(!this->isGameOver){
        int cutoff = 90;
        int timeLeft = cutoff - (int)this->gameTimer.getSec();
        return timeLeft;
    }
    return 0;
}

Maze::Maze(int vertices){
    this->position = glm::vec3(0, 0, 0);
    int v = vertices; // v*v maze
    this->vertices = vertices;
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
            // cout << "(" << x << " " << y << "): ";
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
                // cout << "(" << n.second << ", " << n.first << "), ";
            }
            // cout << top << " " << bottom << " " << left << " " << right << endl;

            if(x == v-1 && y == v-1){
                this->cells.push_back(Cell(y, x, top, bottom, left, right, false, true));
            }
            else{
                this->cells.push_back(Cell(y, x, top, bottom, left, right, false, false));
            }
        }
    }
    
    this->player = Character(0,0,false);
    this->goal = make_pair(this->vertices-1, this->vertices-1);

    vector<pair<int, int>> nodes;
    for(int y=0; y < this->vertices; y++){
        for(int x=0; x < this->vertices; x++){
            if(!verifyOverlap(this->player.position.x, this->player.position.y, x, y) && !verifyOverlap(this->goal.first, this->goal.second, x, y)){
                nodes.push_back(make_pair(x, y));
            }
        }
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(nodes.begin(), nodes.end(), default_random_engine(seed));

    this->imposter = Character(nodes[0].first,nodes[0].second,true);

    this->buttonImposterKill = Item(nodes[1].first,nodes[1].second,"button-imposter-kill");
    this->buttonLaunchArtefacts = Item(nodes[2].first,nodes[2].second, "button-launch-artefacts");
    this->isTask1 = false;
    this->isTask2 = false;
    this->scoreMultiplier = 1;
    this->score = 0;
    this->blindMode = false;
    this->gameTimer.init();
    this->gameOverStatus = false;
    this->isGameOver = false;
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
    this->buttonImposterKill.draw(VP);
    this->buttonLaunchArtefacts.draw(VP);
    for(auto item : this->items){
        item.draw(VP);
    }
    if(this->imposter.health > 0){
        this->imposter.draw(VP);
    }
    if(this->player.health > 0){
        this->player.draw(VP);
    }
    if(this->blindMode){
        pair<int, int> playerVertex = make_pair(this->player.position.x+0.5, this->player.position.y+0.5);
        vector<pair<int, int>> avoidVertices;
        avoidVertices.push_back(playerVertex);
        vector<pair<int, int>> nodes = this->graph[playerVertex];
        avoidVertices.insert(avoidVertices.end(), nodes.begin(), nodes.end());
        for(int i=0; i<this->vertices; i++){
            for(int j=0; j<this->vertices; j++){
                bool check = false;
                for(auto avoid: avoidVertices){
                    if(avoid.first == i && avoid.second == j){
                        check = true;
                        break;
                    }
                }
                if(!check){
                    Cell overlay_cell = Cell(i, j, true, true, true, true, true, false);
                    overlay_cell.draw(VP);
                }
            }
        }
    }  

}

void Maze::tick_input(GLFWwindow *window) {
    if(this->player.health > 0){
        this->player.tick_input(window, this->graph, this->isGameOver);    
    }

    if(this->getTimeLeft() <= 0 || this->player.health <= 0){
        this->isGameOver = true;
    }

    if(this->blindMode){
        this->scoreMultiplier = ((int)this->blindTimer.getSec() / 2) + 1;
    }

    if(glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        if(!this->blindMode){
            this->blindMode = true;
            this->blindTimer.init();
        }
    }    
    if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS){
        if(this->blindMode){
            this->blindMode = false;
            this->scoreMultiplier = 1;
        }
    }

    if(this->imposter.health > 0 && !this->isGameOver){
        this->imposter.findPlayerAndMove(this->player, this->graph);
        if(verifyOverlap(this->player.position.x, this->player.position.y, this->imposter.position.x, this->imposter.position.y) ){
            this->player.health--;
        }
    }
    if(verifyOverlap(this->player.position.x, this->player.position.y, this->buttonImposterKill.position.x, this->buttonImposterKill.position.y) && !(this->isTask1)){
        this->isTask1 = true;
        this->imposter.health = 0;
    }
    if(verifyOverlap(this->player.position.x, this->player.position.y, this->buttonLaunchArtefacts.position.x, this->buttonLaunchArtefacts.position.y) && !(this->isTask2)){
        this->isTask2 = true;
        vector<pair<int, int>> nodes;
        for(int y=0; y < this->vertices; y++){
            for(int x=0; x < this->vertices; x++){
                if(!verifyOverlap(this->player.position.x, this->player.position.y, x, y) && !verifyOverlap(this->buttonImposterKill.position.x, this->buttonImposterKill.position.y, x, y) && !verifyOverlap(this->buttonLaunchArtefacts.position.x, this->buttonLaunchArtefacts.position.y, x, y) && !verifyOverlap(this->goal.first, this->goal.second, x, y)){
                    nodes.push_back(make_pair(x, y));
                }
            }
        }

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(nodes.begin(), nodes.end(), default_random_engine(seed));
        // vector<string> itemChoices={"coin", "bomb"};
        int itemCount = (nodes.size()/4);
        for(int i=0; i<itemCount; i++){
            string itemType;
            if(i < (itemCount * 2/3)){
                itemType = "coin";
            }
            else{
                itemType = "bomb";
            }
            this->items.push_back(Item(nodes[i].first, nodes[i].second, itemType));
        }
    }
    for(auto i = this->items.begin(); i != this->items.end(); ++i){
        Item item = *i;
        if(verifyOverlap(this->player.position.x, this->player.position.y, item.position.x, item.position.y)){
            if(item.type == "coin"){
                this->score += (this->scoreMultiplier * 1);
            }
            else{
                if(this->score > 0){
                    this->score--;
                }
            }
            this->items.erase(i);
            break;
        }
    }
    
    if(this->isTask1 && this->isTask2 && verifyOverlap(this->player.position.x, this->player.position.y, this->goal.first, this->goal.second)){
        this->isGameOver = true;
        this->gameOverStatus = true;
    }
}