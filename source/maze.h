#include "main.h"
#include "cell.h"
#include "character.h"
#include <bits/stdc++.h>


#ifndef MAZE_H
#define MAZE_H

using namespace std;

class Maze {
    public:
        Maze() {}
        Maze(int vertices);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        map<pair<int, int>, vector<pair<int, int>>> graph;
        std::vector<Cell> cells;
        Character player;
        Character imposter;
        void tick_input(GLFWwindow *window);
    private:
        VAO *object;
};

#endif 