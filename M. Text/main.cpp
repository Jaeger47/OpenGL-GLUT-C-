#include <GL/glut.h>

float angle = 0.0f;  // rotation angle for the teapot

void displayText(const char *text, float x, float y) {
    glDisable(GL_LIGHTING); // disable lighting for text
    glRasterPos2f(x, y); // set position for text
    for (const char *c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // render each character
    }
    glEnable(GL_LIGHTING); // enable lighting after text
}

void initLighting() {
    glEnable(GL_LIGHTING);  // enable lighting
    glEnable(GL_LIGHT0);    // enable light 0

    // Set up light properties
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // light position
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f }; // ambient light
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f }; // diffuse light
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // specular light

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    // Set up material properties
    GLfloat matAmbient[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // green ambient color
    GLfloat matDiffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f }; // green diffuse color
    GLfloat matSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white specular color
    GLfloat matShininess[] = { 50.0f };

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,  // eye position
              0.0, 0.0, 0.0,  // look at position
              0.0, 1.0, 0.0); // up vector

    // Draw text
    glColor3f(1.0f, 1.0f, 1.0f); // set text color to white
    displayText("Spinning Solid Teapot", -0.9f, 1.8f);
    glColor3f(0.0, 1.0, 0.0);// set text color to green
    displayText("Sample Text using glutBitmapCharacter", -1.3f, -1.9f);

    // Draw spinning teapot
    glPushMatrix();
    glRotatef(angle, 0.0f, 1.0f, 0.0f); // rotate teapot
    glutSolidTeapot(1.0); // render solid teapot
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    angle += 2.0f; // increase the rotation angle
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    glutPostRedisplay(); // request display update
    glutTimerFunc(16, timer, 0); // 16ms for ~60fps
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Spinning Solid Teapot with Text");
    glEnable(GL_DEPTH_TEST);  // enable depth test
    initLighting();           // initialize lighting

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
