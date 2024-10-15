#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_MIRRORED_REPEAT 0x8370

// Texture variables
GLuint textureID;
GLfloat texCoords[4][2] = {
    {0.0f, 5.0f},
    {5.0f, 5.0f},  // Repeat texture coordinates to show wrapping
    {5.0f, 0.0f},
    {0.0f, 0.0f}
};

// Function to load a texture from a file using stb_image
void loadTextureFromFile(const char* filename) {
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);

    if (image == NULL) {
        printf("Failed to load texture file: %s\n", filename);
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters for filtering (minification and magnification)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Specify texture format
    if (channels == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    } else if (channels == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    } else {
        printf("Unsupported image format\n");
    }

    // Free the image memory
    stbi_image_free(image);
}

// Function to set texture wrapping mode
void setTextureWrapping(GLenum mode) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Show different texture wrapping modes
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(i * 2.5f - 2.5f, 0.0f, 0.0f);

        // Set different wrapping modes
        switch (i) {
            case 0: setTextureWrapping(GL_REPEAT); break;
            case 1: setTextureWrapping(GL_CLAMP_TO_EDGE); break;
            case 2: setTextureWrapping(GL_MIRRORED_REPEAT); break;
        }

        // Draw a quad
        glBegin(GL_QUADS);
        glTexCoord2fv(texCoords[0]); glVertex2f(-1.0f, -1.0f);
        glTexCoord2fv(texCoords[1]); glVertex2f(1.0f, -1.0f);
        glTexCoord2fv(texCoords[2]); glVertex2f(1.0f, 1.0f);
        glTexCoord2fv(texCoords[3]); glVertex2f(-1.0f, 1.0f);
        glEnd();

        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

// Reshape callback
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-4.0, 4.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Texture Wrapping Demo with stb_image");

    glEnable(GL_DEPTH_TEST);

    // Load and set up texture from a file
    loadTextureFromFile("texture.jpg");

    // Register callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
