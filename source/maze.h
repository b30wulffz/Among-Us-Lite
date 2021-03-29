#include "main.h"
#include "cell.h"
#include <vector>

#ifndef MAZE_H
#define MAZE_H

class Maze {
    public:
        Maze() {}
        Maze(int vertices);
        glm::vec3 position;
        void draw(glm::mat4 VP);
        std::vector<Cell> cells;
    private:
        VAO *object;
};

#endif 