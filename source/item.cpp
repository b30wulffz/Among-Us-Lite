#include "item.h"
#include "main.h"
#include <bits/stdc++.h>
using namespace std;

Item::Item(int x, int y, string type){
    this->position = glm::vec3(x*1.0, y*1.0, 0.0);
    this->rotation = 0;
    
    this->type = type;

    vector<GLfloat> shape_vertices = {
         0.25f, 0.25f, 0.0f, 
        0.75f, 0.25f, 0.0f, 
        0.25f, 0.75f, 0.0f, 
        0.75f, 0.25f, 0.0f, 
        0.25f, 0.75f, 0.0f, 
        0.75f, 0.75f, 0.0f,
    };

    vector<GLfloat> color_vertices;

    if(type == "button-imposter-kill"){
        color_vertices = {
            0.20392f, 0.59608f, 0.85882f,
            0.20392f, 0.59608f, 0.85882f,
            0.20392f, 0.59608f, 0.85882f,

            0.52157f, 0.75686f, 0.91373f,
            0.52157f, 0.75686f, 0.91373f,
            0.52157f, 0.75686f, 0.91373f,
        };
    }
    else if(type == "button-launch-artefacts"){
        color_vertices = {
            0.90196f, 0.49412f, 0.13333f, 
            0.90196f, 0.49412f, 0.13333f, 
            0.90196f, 0.49412f, 0.13333f, 
            
            0.89804f, 0.59608f, 0.4f,
            0.89804f, 0.59608f, 0.4f,
            0.89804f, 0.59608f, 0.4f,
        };
    }
    else if(type == "coin"){
        color_vertices = {
            0.9451f, 0.76863f, 0.05882f, 
            0.9451f, 0.76863f, 0.05882f, 
            0.9451f, 0.76863f, 0.05882f, 

            0.9451f, 0.76863f, 0.05882f, 
            0.9451f, 0.76863f, 0.05882f, 
            0.9451f, 0.76863f, 0.05882f, 
        };
    }
    else if(type == "bomb"){
        color_vertices = {
            0.140f,  0.616f,  0.489f,
            0.140f,  0.616f,  0.489f,
            0.140f,  0.616f,  0.489f,

            0.140f,  0.616f,  0.489f,
            0.140f,  0.616f,  0.489f,
            0.140f,  0.616f,  0.489f,
        };
    }
    else {
        color_vertices = {
            0.279f,  0.317f,  0.505f,
            0.279f,  0.317f,  0.505f,
            0.279f,  0.317f,  0.505f,

            0.279f,  0.317f,  0.505f,
            0.279f,  0.317f,  0.505f,
            0.279f,  0.317f,  0.505f,
        };
    }

    GLfloat vertex_buffer_data[shape_vertices.size()];
    for(int i=0; i<shape_vertices.size(); i++){
        vertex_buffer_data[i] = shape_vertices[i];
    }
    GLfloat g_color_buffer_data[color_vertices.size()];
    for(int i=0; i<color_vertices.size(); i++){
        g_color_buffer_data[i] = color_vertices[i];
    }

    this->object = create3DObject(GL_TRIANGLES, color_vertices.size()/3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}


void Item::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    // glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 translate = glm::translate (glm::vec3(this->position));    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Item::tick(){
}