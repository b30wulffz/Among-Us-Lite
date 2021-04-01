#include "main.h"
#include "maze.h"

#ifndef HUD_H
#define HUD_H

class Hud {
    public:
        Hud(){}
        Hud(int scr_width, int scr_height);
        void draw(Maze maze);
};

#endif