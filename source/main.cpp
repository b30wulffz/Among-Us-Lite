#include "main.h"
#include "timer.h"
#include "ball.h"
#include "cell.h"
#include "maze.h"
#include "hud.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

// // Ball ball1;
// Cell board, board2;
Maze maze;
Hud hud;

glm::vec3 eye ( 0, 0, 5);
glm::vec3 cameraFront ( 0, 0, -5);
// glm::vec3 target (0, 0, 0);
glm::vec3 up (-1, 0, 0);
glm::vec3 target = eye + cameraFront;

bool view_mode = false;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // // Eye - Location of camera. Don't change unless you are sure!!
    // // camera_rotation_angle = 1;
    // glm::vec3 eye ( 0, 0, 5);
    // // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (-1, 0, 0);
    // // glm::vec3 up (-1, 0, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    /*
    glm::mat4 VP = Matrices.projection * Matrices.view;
    */
   Matrices.projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);  
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    // board.draw(VP);
    // board2.draw(VP);

    // glUseProgram (programID);
    maze.draw(VP);
    hud.draw(maze);
//     glMatrixMode(GL_PROJECTION);
// glLoadIdentity();

// glMatrixMode(GL_MODELVIEW);
// glLoadIdentity();

// glPushMatrix();
// glBegin(GL_QUADS);
// glVertex3f(-0.5f,  0.5f, 0.0f);
// glVertex3f(-0.5f, -0.5f, 0.0f);
// glVertex3f( 0.5f, -0.5f, 0.0f);
// glVertex3f( 0.5f,  0.5f, 0.0f);
// glEnd();
// glPopMatrix();

}

void tick_input(GLFWwindow *window) {
    // For Camera Translation
    const float cameraSpeed = 0.2f;
    if(glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){
        view_mode = true;
        // eye = glm::vec3( 0, 0, 5);
        target = eye + cameraFront;
    }
    if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        view_mode = false;
    }

    maze.tick_input(window);

    if(view_mode){
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
            eye -= cameraSpeed * cameraFront;
            target = eye + cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
            eye += cameraSpeed * cameraFront;
            target = eye + cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
            eye -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
            target = eye + cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS){
            eye += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
            target = eye + cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){
            eye -= up* cameraSpeed;
            target = eye + cameraFront;
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){
            eye += up* cameraSpeed;
            target = eye + cameraFront;
        }
    }
    else {
        target = glm::vec3(maze.player.position);
        eye = target-cameraFront;
    }
}


void tick_elements() {
    // ball1.tick();
    // board.tick();
    camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    // ball1       = Ball(0, 0, COLOR_RED);
    // board = Cell(0,0,1,0,1,1);
    maze = Maze(10);
    hud = Hud(5);
    target = glm::vec3(maze.player.position);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    glEnable(GL_BLEND);

	glClearColor(0.70588f, 0.95686f, 0.84314f, 0.0);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
