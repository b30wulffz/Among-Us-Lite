#include "character.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Character::Character(int x, int y, bool isImposter){
    this->position = glm::vec3(x, y, 0);
    GLfloat vertex_buffer_data[] = {
        0.25f, 0.25f, 0.0f, 
        0.75f, 0.25f, 0.0f, 
        0.25f, 0.75f, 0.0f, 
        0.75f, 0.25f, 0.0f, 
        0.25f, 0.75f, 0.0f, 
        0.75f, 0.75f, 0.0f,
    };

    GLfloat g_color_buffer_data[] = {

        0.543f,  0.021f,  0.978f,
        0.543f,  0.021f,  0.978f,
        0.543f,  0.021f,  0.978f,

        0.543f,  0.021f,  0.978f,
        0.543f,  0.021f,  0.978f,
        0.543f,  0.021f,  0.978f,
    };
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, g_color_buffer_data, GL_FILL);

}

void Character::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Character::tick(){
}

void Character::move(float x, float y, std::vector<Cell> cells, bool isX){
    // if(isX){
    //     // change in x
    //     if(x > this->position.x){
    //         // right coordinates
    //         float width = 0.75-0.25;
    //         float beforeX = this->position.x+width;
    //         for(auto cell : cells){
                
    //         }
    //     }
    // }
    // else{
    //     // change in y
    // }

}
 

float factor = 1.0;
string flag = "";

void Character::tick_input(GLFWwindow *window) {
    float unitStep = 1.0, speed = 0.1, cutoff = 0.0001;
    
    if(fabs(factor - unitStep) < cutoff){ // factor == 1.0
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            flag = "+x";
            factor = 0.0;
        }
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            flag = "-x";
            factor = 0.0;
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            flag = "+y";
            factor = 0.0;
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            flag = "-y";
            factor = 0.0;
        }
    }
    else{
        if(flag == "+x"){
            this->position.x+=speed;
        }
        else if(flag == "-x"){
            this->position.x-=speed;
        }
        else if(flag == "+y"){
            this->position.y+=speed;
        }
        else if(flag == "-y"){
            this->position.y-=speed;
        }
        factor += speed;
    }


}