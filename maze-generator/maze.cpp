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

int main(){
    int v = 5; // 9*9 maze
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
    map<pair<int, int>, vector<pair<int, int>>> graph;
    
    kruskal(graph, v, edges);

    for(int y=0; y<v; y++){
        for(int x=0; x<v; x++){
            vector<pair<int, int>> nodes = graph[make_pair(y, x)];
            cout << "(" << x << " " << y << "): ";
            for(auto n: nodes){
                cout << "(" << n.second << ", " << n.first << "), ";
            }
            cout << endl;
        }
    }
    
    return 0;
}