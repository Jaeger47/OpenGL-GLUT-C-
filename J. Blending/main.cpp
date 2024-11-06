
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <gl/glut.h>
#include "stb_image.h"

using namespace std;

void update(int);
void loadTexture(const char*, GLuint&, GLenum);
void loadAllTextures();
void reshape(int, int);
void display();

float angle = 0; //rotation angle

GLuint boxTex; //The id of the texture



void initRendering() {
	glClearColor(0.4, 0.3, 0.3, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	loadAllTextures();
	glEnable (GL_BLEND);



}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Textures - github.com/Jaeger47/Learning-OpenGL");
	initRendering();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000/60,update,0); //add timer
	glutMainLoop();
	return 0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	glPushMatrix();

	glColor4f(0.0f,1.0f,0.0f,1.0);
	glPushMatrix();
	glTranslatef(0,0,-10);
	glRotatef(angle,1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.5,1,24,24);
	glPopMatrix();

    glRotatef(angle,0.0f, 1.0f, 0.0f); //animated rotation

    //ADJUST THE S & D FACTORS
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float alpha = 1.0f;//adjust alpha channel
    glColor4f(1.0f,1.0f,1.0f,alpha);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, boxTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);

		//front
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates

		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		//right
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);

		//back
		glNormal3f(0.0f, 0.0f, -1.5f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);

		//left
		glNormal3f(-1.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);

		//top
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.5f);

		//bottom
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); //texture coordinates
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.5f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_BLEND);
	glPopMatrix();

	glutSwapBuffers();
}

void loadTexture(const char* fileName, GLuint& textureID, GLenum format) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        // Handle error loading texture
        std::cerr << "Failed to load texture: " << fileName << std::endl;
    }
}

void loadAllTextures() {

    loadTexture("vtr.bmp", boxTex, GL_RGBA); // Change GL_RGB to GL_RGBA for blending if needed

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
	angle+=2;
	if(angle>360.0f)
		angle=angle-360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000/60,update,0);
}


