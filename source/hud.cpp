#include "main.h"
#include "hud.h"
#include "maze.h"

#include <iostream>
#include <map>
#include <string>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
// #include <freetype/freetype.h>

GLuint     textShaderID;

/// Holds all state information relevant to a character as loaded using FreeType
struct TextCharacter {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, TextCharacter> Characters;
unsigned int VAO1, VBO;

// render line of text
// -------------------
void RenderText(int shaderId, std::string text, float x, float y, float scale, glm::vec3 color)
{
    // activate corresponding render state	
    // shader.use();
    glUseProgram(shaderId);
    glUniform3f(glGetUniformLocation(shaderId, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO1);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        TextCharacter ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// const unsigned int SCR_WIDTH = 600;
// const unsigned int SCR_HEIGHT = 600;

Hud::Hud(int scr_width, int scr_height){
    textShaderID = LoadShaders("../source/shaders/text.vert", "../source/shaders/text.frag");
    glUseProgram(textShaderID);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(scr_width), 0.0f, static_cast<float>(scr_height));
    glUniformMatrix4fv(glGetUniformLocation(textShaderID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // FreeType
    // --------
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

	// // find path to font
    // std::string font_name = FileSystem::getPath("resources/fonts/Antonio-Bold.ttf");
    // if (font_name.empty())
    // {
    //     std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
    //     return;
    // }
	
	// load font as face
    FT_Face face;
    if (FT_New_Face(ft, "../source/resources/fonts/Lexend-Regular.ttf", 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }
    else {
        // set size to load glyphs as
        FT_Set_Pixel_Sizes(face, 0, 48);

        // disable byte-alignment restriction
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // load first 128 characters of ASCII set
        for (unsigned char c = 0; c < 128; c++)
        {
            // Load character glyph 
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            TextCharacter character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, TextCharacter>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    
    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Hud::draw(Maze maze){
    glDisable(GL_DEPTH_TEST);								// never occluded, always visible
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE   );
	glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);				// makes the HUD a bit easier to see
	glActiveTexture(GL_TEXTURE0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_FUNC_ADD);
    // printf("hii\n");
    // RenderText(textShaderID, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
    // RenderText(textShaderID, "This is sample text", 25.0f, 540.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.2f));
    // RenderText(textShaderID, "This is sample text", 0.0f, 0.0f, 0.5f, glm::vec3(0.5, 0.8f, 0.2f));
    // RenderText(textShaderID, "(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));
        RenderText(textShaderID, "Health: "+std::to_string(maze.player.health), 425.0f, 540.0f, 0.4f, glm::vec3(0, 0.0f, 0.0f));
        RenderText(textShaderID, "Score: "+std::to_string(maze.score), 425.0f, 520.0f, 0.4f, glm::vec3(0, 0.0f, 0.0f));
        RenderText(textShaderID, (maze.blindMode) ? "Light: Off" : "Light: On", 425.0f, 500.0f, 0.4f, glm::vec3(0, 0.0f, 0.0f));
        
        int timeLeft = maze.getTimeLeft();
        // if(timeLeft <= 0){
        //     maze.isGameOver = true;
        //     maze.gameOverStatus = "You Lost";
        // }
        RenderText(textShaderID, "Time Left: "+std::to_string(timeLeft), 425.0f, 480.0f, 0.4f, glm::vec3(0, 0.0f, 0.0f));
        
        RenderText(textShaderID, "Tasks: ", 25.0f, 540.0f, 0.4f, glm::vec3(0, 0.0f, 0.0f));
        RenderText(textShaderID, "> Kill the imposter", 25.0f, 500.0f, 0.4f, (!maze.isTask1) ? glm::vec3(0.78039f, 0.0f, 0.22353f) : glm::vec3(0.09804f, 0.43529f, 0.23922f));
        RenderText(textShaderID, "> Release powerups and obstacles", 25.0f, 480.0f, 0.4f, (!maze.isTask2) ? glm::vec3(0.78039f, 0.0f, 0.22353f) : glm::vec3(0.09804f, 0.43529f, 0.23922f));
    
    if(maze.isGameOver){
        RenderText(textShaderID, "Game Over", 40.0f, 250.0f, 2.0f, glm::vec3(0.42353f, 0.85098f, 1.0f));
        if(maze.gameOverStatus){
            RenderText(textShaderID, "You win", 210.0f, 200.0f, 1.0f, glm::vec3(0.80784f, 1.0f, 0.73725f));
        }
        else{
            RenderText(textShaderID, "You lose", 210.0f, 200.0f, 1.0f, glm::vec3(1.0f, 0.78431f, 0.78039f));
        }
    }


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}