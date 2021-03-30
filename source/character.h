#include "main.h"
#include "cell.h"
#include <bits/stdc++.h>

#ifndef CHARACTER_H
#define CHARACTER_H

using namespace std;

class Character {
    public:
        Character(){}
        Character(int x, int y, bool isImposter);
        bool isImposter;
        glm::vec3 position;
        float rotation;
        void draw(glm::mat4 VP);
        void tick();
        float factor;
        string flag;
        int ticks;
        int health;
        bool checkMove(map<pair<int, int>, vector<pair<int, int>>> graph, float newX, float newY);
        void tick_input(GLFWwindow *window, map<pair<int, int>, vector<pair<int, int>>> graph);
        void move(float x, float y, std::vector<Cell> cells, bool isX);
        void findPlayerAndMove(Character player, map<pair<int, int>, vector<pair<int, int>>> graph);
    private:
        VAO *object;
};

#endif