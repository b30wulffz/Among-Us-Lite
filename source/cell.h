#include "main.h"

#ifndef CELL_H
#define CELL_H

class Cell {
    public:
        Cell(){}
        Cell(int x, int y, bool top, bool bottom, bool left, bool right, bool isOverlay);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void tick();
        // void hideWalls(bool hide);
        std::vector<GLfloat> shape_vertices;
        std::vector<GLfloat> color_vertices;
    private:
        VAO *object;
};

#endif