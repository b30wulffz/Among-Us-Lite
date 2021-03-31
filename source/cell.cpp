#include "cell.h"
#include "main.h"
#include <vector>

Cell::Cell(int x, int y, bool top, bool bottom, bool left, bool right, bool isOverlay, bool isGoal){
    this->position = glm::vec3(x*1.0, y*1.0, 0.0);
    this->rotation = 0;

    this->shape_vertices = {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
    };

    if(!isOverlay){
        if(!isGoal){
            this->color_vertices = {
                0.517f,  0.713f,  0.338f,
                0.517f,  0.713f,  0.338f,
                0.517f,  0.713f,  0.338f,

                0.517f,  0.713f,  0.338f,
                0.517f,  0.713f,  0.338f,
                0.517f,  0.713f,  0.338f,
            };
        }
        else{
            this->color_vertices = {
                0.96078f, 0.6902f, 0.2549f,
                0.96078f, 0.6902f, 0.2549f,
                0.96078f, 0.6902f, 0.2549f,
                
                0.96078f, 0.6902f, 0.2549f,
                0.96078f, 0.6902f, 0.2549f,
                0.96078f, 0.6902f, 0.2549f,
            };
        }
    }
    else{
        this->color_vertices = {
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,

            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
        };
    }

    if(top){
        // top wall
        this->shape_vertices.insert(this->shape_vertices.end(), {
            0.0f, 0.0f, 0.0f,
            0.1f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,

            0.1f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.1f, 1.0f, 0.0f,
        });
        this->color_vertices.insert(this->color_vertices.end(), {
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
        });
    }

    if(bottom){
        // bottom wall
        this->shape_vertices.insert(this->shape_vertices.end(), {
            0.9f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.9f, 1.0f, 0.0f,

            1.0f, 0.0f, 0.0f,
            0.9f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
        });
        this->color_vertices.insert(this->color_vertices.end(), {
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
        });
    }

    if(left){
        // left wall
        this->shape_vertices.insert(this->shape_vertices.end(), {
            0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,
            0.0f, 0.1f, 0.0f,

            1.0f, 0.0f, 0.0f,
            0.0f, 0.1f, 0.0f,
            1.0f, 0.1f, 0.0f,
        });
        this->color_vertices.insert(this->color_vertices.end(), {
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
        });
    }
    if(right){
        // right wall
        this->shape_vertices.insert(this->shape_vertices.end(), {
            0.0f, 0.9f, 0.0f,
            1.0f, 0.9f, 0.0f,
            0.0f, 1.0f, 0.0f,

            1.0f, 0.9f, 0.0f,
            0.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,
        });
        this->color_vertices.insert(this->color_vertices.end(), {
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
            0.393f,  0.621f,  0.362f,
        });
    }

    GLfloat vertex_buffer_data[this->shape_vertices.size()];
    for(int i=0; i<this->shape_vertices.size(); i++){
        vertex_buffer_data[i] = this->shape_vertices[i];
    }
    GLfloat g_color_buffer_data[this->color_vertices.size()];
    for(int i=0; i<this->color_vertices.size(); i++){
        g_color_buffer_data[i] = this->color_vertices[i];
    }

    this->object = create3DObject(GL_TRIANGLES, this->color_vertices.size()/3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
}

// void Cell::hideWalls(bool hide){
//     std::vector<GLfloat> nowall_shape_vertices = {
//         0.0f, 0.0f, 0.0f,
//         1.0f, 0.0f, 0.0f,
//         0.0f, 1.0f, 0.0f,

//         1.0f, 0.0f, 0.0f,
//         0.0f, 1.0f, 0.0f,
//         1.0f, 1.0f, 0.0f,
//     };

//     std::vector<GLfloat> nowall_color_vertices = {
//         0.517f,  0.713f,  0.338f,
//         0.517f,  0.713f,  0.338f,
//         0.517f,  0.713f,  0.338f,

//         0.517f,  0.713f,  0.338f,
//         0.517f,  0.713f,  0.338f,
//         0.517f,  0.713f,  0.338f,
//     };

//     std::vector<GLfloat> shape_vertices;
//     std::vector<GLfloat> color_vertices;

//     if(hide){
//         shape_vertices = nowall_shape_vertices;
//         color_vertices = nowall_color_vertices;
//     }
//     else{
//         shape_vertices = this->shape_vertices;
//         color_vertices = this->color_vertices;
//     }
    
//     int count = shape_vertices.size();
//     GLfloat vertex_buffer_data[count];
//     for(int i=0; i<count; i++){
//         vertex_buffer_data[i] = shape_vertices[i];
//     }
//     GLfloat g_color_buffer_data[count];
//     for(int i=0; i<count; i++){
//         g_color_buffer_data[i] = color_vertices[i];
//     }

//     this->object = create3DObject(GL_TRIANGLES, count/3, vertex_buffer_data, g_color_buffer_data, GL_FILL);
// }

void Cell::draw(glm::mat4 VP){
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

void Cell::tick(){
}