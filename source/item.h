#include "main.h"
#include <bits/stdc++.h>

#ifndef ITEM_H
#define ITEM_H

using namespace std;

class Item {
    public:
        Item(){}
        Item(int x, int y, string type);
        glm::vec3 position;
        float rotation;
        string type;
        void draw(glm::mat4 VP);
        void tick();
    private:
        VAO *object;
};

#endif