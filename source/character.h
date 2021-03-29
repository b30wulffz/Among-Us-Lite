#include "main.h"
#include "cell.h"
#include <vector>

#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
    public:
        Character(){}
        Character(int x, int y, bool isImposter);
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void tick();
        void tick_input(GLFWwindow *window);
        void move(float x, float y, std::vector<Cell> cells, bool isX);
    private:
        VAO *object;
};

#endif