#include <GL/glut.h>
#include <stdio.h>

// Camera position and orientation
float camX = 0.0f, camY = 0.0f, camZ = 5.0f;   // Initial camera position
float lookX = 0.0f, lookY = 0.0f, lookZ = 0.0f; // Initial look-at position
float angle = 0.0f;  // Rotation angle for the teapot

// Function to display text on screen
void renderText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Function to handle the display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera view using gluLookAt
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

    // Draw a rotating teapot
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Rotate the teapot around the Y-axis
    glutSolidTeapot(1.0);  // Draw a solid teapot
    glPopMatrix();

    // Set up orthogonal projection for text display
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // Set orthogonal projection
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    // Display camera position and look-at position
    char info[128];
    sprintf(info, "Camera Position: (%.2f, %.2f, %.2f)", camX, camY, camZ);
    renderText(-0.9f, 0.9f, info);
    sprintf(info, "Look At Position: (%.2f, %.2f, %.2f)", lookX, lookY, lookZ);
    renderText(-0.9f, 0.85f, info);
    glEnable(GL_LIGHTING);

    // Restore projection and modelview matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glutSwapBuffers();
}

// Function to handle keyboard input
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': camY += 0.1f; break;  // Move camera up
        case 's': camY -= 0.1f; break;  // Move camera down
        case 'a': camX -= 0.1f; break;  // Move camera left
        case 'd': camX += 0.1f; break;  // Move camera right
        case 'z': camZ += 0.1f; break;  // Move camera closer
        case 'x': camZ -= 0.1f; break;  // Move camera away
        case 'i': lookY += 0.1f; break; // Move look-at up
        case 'k': lookY -= 0.1f; break; // Move look-at down
        case 'j': lookX -= 0.1f; break; // Move look-at left
        case 'l': lookX += 0.1f; break; // Move look-at right
        case 'o': lookZ += 0.1f; break; // Move look-at closer
        case 'p': lookZ -= 0.1f; break; // Move look-at away
        case 27: exit(0); break;        // ESC key to exit
    }
    glutPostRedisplay();
}

// Function to update the rotation angle
void update(int value) {
    angle += 2.0f;
    if (angle > 360) {
        angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // 16ms for ~60 FPS
}

// Function to initialize OpenGL settings
void init() {
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
    glEnable(GL_LIGHTING);    // Enable lighting
    glEnable(GL_LIGHT0);      // Enable light #0

    // Set light properties
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };  // Light position
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // Ambient light
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // Diffuse light
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Specular light

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Set material properties
    GLfloat matAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat matDiffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };  // Red teapot
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat matShininess[] = { 50.0f };  // Shininess

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Set clear color

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spinning Teapot with Lighting and Camera Controls");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
