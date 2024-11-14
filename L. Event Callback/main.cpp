#include <GL/glut.h>
#include <cmath>

// Position, size, and movement step for the movable cube
float posX = 0.0f, posY = 0.0f;
float moveStep = 0.1f;
float cubeSize = 0.5f;

// Position of the stationary cube
float solidCubeX = 1.0f;
float solidCubeY = 0.0f;

// Function to check if the cubes collide
bool checkCollision() {
    return std::abs(posX - solidCubeX) < cubeSize && std::abs(posY - solidCubeY) < cubeSize;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up a basic 3D view with rotation for depth perception
    glTranslatef(0.0f, 0.0f, -5.0f); // Move back to view the scene
    glRotatef(25.0f, 1.0f, 0.0f, 0.0f); // Rotate around the x-axis
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f); // Rotate around the y-axis

    // Draw the stationary cube as a wireframe
    glPushMatrix();
    glTranslatef(solidCubeX, solidCubeY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the stationary cube
    glutWireCube(cubeSize);
    glPopMatrix();

    // Draw the movable cube as a wireframe
    glPushMatrix();
    glTranslatef(posX, posY, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color for the movable cube
    glutWireCube(cubeSize);
    glPopMatrix();

    glutSwapBuffers();
}

void handleKeys(int key, int x, int y) {
    // Store previous position in case of collision
    float prevPosX = posX;
    float prevPosY = posY;

    // Move the cube based on arrow key input
    switch (key) {
        case GLUT_KEY_UP:
            posY += moveStep;
            break;
        case GLUT_KEY_DOWN:
            posY -= moveStep;
            break;
        case GLUT_KEY_LEFT:
            posX -= moveStep;
            break;
        case GLUT_KEY_RIGHT:
            posX += moveStep;
            break;
    }

    // Check for collision and reset position if collision is detected
    if (checkCollision()) {
        posX = prevPosX;
        posY = prevPosY;
    }

    glutPostRedisplay(); // Request display update
}

void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    // Set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Cube Collision");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(handleKeys); // Register special keys handler (for arrow keys)

    glutMainLoop();
    return 0;
}
