#include <GL/glut.h>
#include "bass.h"
#include <stdio.h>


float angle = 0.0f; // Angle of rotation


void init() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0); // Field of view, aspect ratio, near and far planes

    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen and depth buffer
    glLoadIdentity(); // Reset transformations

    // Move the camera back along the z-axis
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Rotate the teapot around the Y axis
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    glColor3f(1.0, 0.0, 0.0);

    glutSolidTeapot(1.0); // Draw the teapot

    glutSwapBuffers(); // Swap buffers for smooth animation
}

void update(int value) {
    angle += 2.0f; // Increment the angle
    if (angle > 360) {
        angle -= 360;
    }

    glutPostRedisplay(); // Redisplay the scene
    glutTimerFunc(16, update, 0); // Call update every 16 milliseconds (~60 FPS)
}

void asyncPlayAudio(const char* filename) {
    // Initialize BASS (only call this once in the main program)
    if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
        printf("Can't initialize device\n");
        return;
    }

    // Create a stream from the file
    HSTREAM stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, 0);
    if (!stream) {
        printf("Can't play file\n");
        return;
    }

    // Play the stream asynchronously
    BASS_ChannelPlay(stream, FALSE);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Initialize display mode with double buffering and depth buffer
    glutInitWindowSize(800, 600); // Set window size
    glutCreateWindow("Spinning Teapot"); // Create the window

    init(); // Initialize settings

    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Register timer callback for animation

    asyncPlayAudio("cf.mp3");

    glutMainLoop(); // Enter the GLUT main loop
    return 0;
}
