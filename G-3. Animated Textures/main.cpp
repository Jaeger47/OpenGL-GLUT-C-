#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <gl/glut.h>
#include "stb_image.h"


void update(int);
void reshape(int, int);
void display();
void loadTexture(const char *, GLuint);


GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat directedLightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };

float angle = 0; //rotation angle
GLuint textures[3]; // Array to store texture IDs
int currentTexture = 0; // Index for the currently active texture


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);

    glGenTextures(3, textures); // Generate 3 texture IDs

    //load image file 8-32bit .jpg, .png, .bmp, .tga
	loadTexture("frame1.bmp", textures[0]);
	loadTexture("frame2.bmp", textures[1]);
	loadTexture("frame3.bmp", textures[2]);

	//optimal size 256x256, 512x512, 1024x1024
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize(800, 600);

	glutCreateWindow("Textures - github.com/Jaeger47/Learning-OpenGL");

	initRendering();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);


	glutTimerFunc(1000 / 60, update, 0); //add timer
	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();




	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[currentTexture]); // Bind the current texture

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -5.0f);

        glRotated(angle, 0, 1, 0);

        glBegin(GL_QUADS);//start of the primitive //front



		glNormal3f(-0.707107f, 0.707107f, 0); //normal map
        glTexCoord2f(0.0f, 0.0f); //TC1
        glVertex3f(-1.0f, 1.0f, 0.0f);//V4

		glNormal3f(0.707107f, 0.707107f, 0);
		glTexCoord2f(1.0f, 0.0f);//TC2
        glVertex3f(1.0f, 1.0f, 0.0f);//VglVertex3f(1.0f, -1.0f, 0.0f);//V23

        glNormal3f(0.707107f, 0.707107f, 0);
        glTexCoord2f(1.0f, 1.0f);//TC3
        glVertex3f(1.0f, -1.0f, 0.0f);//V2

        glNormal3f(-0.707107f, -0.707107f, 0);
        glTexCoord2f(0.0f, 1.0f);//TC4
        glVertex3f(-1.0f, -1.0f, 0.0f); //V1



	glEnd();//end of the primitive

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}



void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}


void update(int)
{
	//looping animation logic
	angle += 0.8f;
	if (angle > 360.0f)
		angle = angle - 360.0f;


    // Update the texture every second (adjust the timing as needed)
    static int textureTimer = 0;
    textureTimer++;
    if (textureTimer > 15) { // timer
        currentTexture = (currentTexture + 1) % 3; // Cycle through 3 textures
        textureTimer = 0;
    }


	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);

}

void loadTexture(const char *filename, GLuint textureID) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//change GL_RGB to GL_RGBA for blending
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture: %s\n", filename);
    }
}
