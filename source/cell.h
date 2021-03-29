#include "main.h"

#ifndef CELL_H
#define CELL_H

class Cell {
    public:
        Cell(){}
        Cell(int x, int y, bool top, bool bottom, bool left, bool right);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void tick();
    private:
        VAO *object;
};

#endif