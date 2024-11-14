#include <GL/glut.h>
#include <cmath>  // For trigonometric functions

int currentScene = 1;  // Keeps track of the current scene

// Function to render Scene 1
void renderScene1() {
    // Set the background color for Scene 1 (Red)
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render objects for Scene 1 (e.g., a green triangle)
    glColor3f(0.0f, 1.0f, 0.0f);  // Green color
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.0f,  0.5f);
    glEnd();
}

// Function to render Scene 2
void renderScene2() {
    // Set the background color for Scene 2 (Blue)
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render objects for Scene 2 (e.g., a yellow square)
    glColor3f(1.0f, 1.0f, 0.0f);  // Yellow color
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f(-0.5f,  0.5f);
    glEnd();
}

// Function to render Scene 3
void renderScene3() {
    // Set the background color for Scene 3 (Green)
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render objects for Scene 3 (e.g., a magenta circle)
    glColor3f(1.0f, 0.0f, 1.0f);  // Magenta color
    float radius = 0.5f;
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 10) {
            float theta = i * 3.14159f / 180.0f;  // Convert degrees to radians
            glVertex2f(radius * cos(theta), radius * sin(theta));
        }
    glEnd();
}

// Display callback function
void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the current scene
    switch (currentScene) {
        case 1:
            renderScene1();
            break;
        case 2:
            renderScene2();
            break;
        case 3:
            renderScene3();
            break;
        // Add more cases here for additional scenes
        default:
            break;
    }

    // Swap buffers for double buffering
    glutSwapBuffers();
}

// Timer function for updating the scene
void update(int value) {
    // Switch to the next scene
    currentScene = (currentScene % 3) + 1;  // Cycle through 1, 2, 3
    glutPostRedisplay();  // Redraw the scene

    // Set the timer for the next scene change
    glutTimerFunc(3000, update, 0);  // Change scene every 3000ms (3 seconds)
}

// Initialize OpenGL settings
void initOpenGL() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing
    glShadeModel(GL_SMOOTH);  // Smooth shading
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Scene Transition Demo");

    // Initialize OpenGL
    initOpenGL();

    // Register callback functions
    glutDisplayFunc(display);      // Register display function
    glutTimerFunc(3000, update, 0);  // Start the timer for scene transitions

    // Start the main loop
    glutMainLoop();
    return 0;
}
