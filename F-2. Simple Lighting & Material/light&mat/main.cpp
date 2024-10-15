#include <GL/glut.h>

// Initialize lighting and material properties
void initLighting() {
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  // Use default light 0

    // Define light properties
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
   // GLfloat light_ambient[]  = { 0.0, 0.0, 0.8, 1.0f };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    // Set light parameters
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
      glLightfv(GL_LIGHT0, GL_POSITION, light_position);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
      //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);


    // Enable depth test for correct 3D rendering
    glEnable(GL_DEPTH_TEST);
}

// Initialize material properties
void initMaterial_1() {
    // Define material properties
    GLfloat mat_ambient[]  = { 0.0, 0.0, 1.0, 1.0 };
    GLfloat mat_diffuse[]  = { 1.0, 0.0, 0.0, 1.0 };  // Red color
    //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    // Set material parameters
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void initMaterial_2() {
    // Define material properties
    GLfloat mat_ambient[]  = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_diffuse[]  = { 0.0, 1.0, 0.0, 1.0 };  // Red color
    //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    // Set material parameters
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


// Display callback function
void display() {
    // Clear the screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0 ,0, -5);

    // Render the teapot
    initMaterial_1();
    glTranslated(-1 ,0, 0);
    glutSolidTeapot(0.6);


    initMaterial_2();
    glTranslated(2 ,0, 0);
    glutSolidTeapot(0.6);

    // Swap the front and back buffers
    glutSwapBuffers();
}

// Window reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Teapot with Lighting");

    // Initialize lighting and material
    initLighting();


    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Start the main loop
    glutMainLoop();
    return 0;
}
