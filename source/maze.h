#include "main.h"
#include "cell.h"
#include "character.h"
#include "item.h"
#include "clocktime.h"
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
        vector<Cell> cells;
        Character player;
        Character imposter;
        bool isTask1;
        bool isTask2;
        int vertices;
        int score;
        int scoreMultiplier;
        bool blindMode;
        Clocktime gameTimer;
        int getTimeLeft();
        bool gameOverStatus;
        bool isGameOver;
        pair<int, int> goal;
        Item buttonImposterKill;
        Item buttonLaunchArtefacts;
        vector<Item> items;
        void tick_input(GLFWwindow *window);
    private:
        VAO *object;
};

#endif 