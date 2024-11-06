#include <GL/glut.h>
#include "model.h"
#include "model2.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  // Include the stb_image header

// Rotation angle for the teapot
float angle = 0.0f;

// Animation frame index
int frameIndex = 0;
const int numFrames = 18;  // Total number of frames in the animation

// Array of model functions (for frame-by-frame animation)
void (*modelFrames[numFrames])() = {model1, model2, model3, model4, model5, model6, model7, model8, model9,
        model10, model11, model12, model13, model14, model15, model16, model17, model18};  // Define each model function in "model.h"

// Texture variables
GLuint textureID;

// Initialize lighting settings
void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = {5.0f, 5.0f, 5.0f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// Load texture from file
void loadTexture(const char* filename) {
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        printf("Failed to load texture\n");
    }
    stbi_image_free(data);
}

// Initialize scene settings
void initScene() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    initLighting();

    loadTexture("harryfull.png"); // Replace with your texture file path
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    /*// Set camera position to see the model in the middle
    float cameraDistance = 3.5f; // Adjust this value based on your model's size
    float cameraHeight = 5.0f;     // Adjust this value for desired height

    // Set camera position using gluLookAt
    gluLookAt(cameraDistance, cameraHeight, cameraDistance,  // Camera position
              0.0, 0.5, 0.0,                               // Look at the origin (center of model)
              0.0, 1.0, 0.0);            */                  // Up vector

    // Bind the texture before drawing the model
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Rotate the current model
    // glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Draw the current frame of the animationns
    glTranslated(0, -1.5, -5);
    glRotated(angle, 0, 1, 0);
    modelFrames[frameIndex]();

    glDisable(GL_TEXTURE_2D);  // Disable texturing after drawing
    glutSwapBuffers();
}

// Update function to animate the rotation and frame change
void update(int value) {
    angle += 1.0f;
    if (angle > 360) angle -= 360;

    // Advance to the next frame in the animation
    frameIndex = (frameIndex + 1) % numFrames;

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);  // Adjust delay as needed
}

// Reshape function to maintain the aspect ratio
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Model Animation");

    initScene();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(50, update, 0);  // Initial timer call

    glutMainLoop();
    return 0;
}
