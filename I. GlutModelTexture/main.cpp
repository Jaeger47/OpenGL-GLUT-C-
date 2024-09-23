
 /* Source code for glutModelTextures by Mark Daniel G. Dacer
  * www.github.com/Jaeger47
  */


#define STB_IMAGE_IMPLEMENTATION
#include <gl/glut.h>
#include "stb_image.h"


void update(int);

void reshape(int, int);
void display();
void loadTexture(const char *, GLuint, GLenum);

GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat directedLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat directedLightPos[] = { 0.0f, 0.0f, 5.0f, 1.0f };

GLuint textures[2]; // Array to store texture IDs

float angle = 0.0f;


void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

    glGenTextures(2, textures);//generate 2 texture ID

	loadTexture("texture1.bmp", textures[0], GL_RGB);//load from file
	loadTexture("texture2.bmp", textures[1], GL_RGB);

}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);

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


	glTranslatef(0.0f, 0.0f, -5.0f);


	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);

    glEnable(GL_TEXTURE_2D);


    //---Sphere-------------------------------------------------------------------//
	glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, textures[0]); // Bind the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//must be implemented to use textures to glut solids
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	///////////////////////////////////////////////////////

	glTranslatef(-1.5,0,0);
	glRotatef(angle, 1,1, 0);

	glutSolidSphere(0.8,12,12);

	glPopMatrix();
	//---Sphere-------------------------------------------------------------------//


    //---Teapot-------------------------------------------------------------------//
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[1]); // Bind the current texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//must be implemented to use textures to glut solids
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	///////////////////////////////////////////////////////

	glTranslatef(1.0,0,0);
	glRotatef(angle, 1, 0, 0);

	glutSolidTeapot(0.8);

	glPopMatrix();
	//---Teapot-------------------------------------------------------------------//

    glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

//Makes the image into a texture, and returns the id of the texture
void loadTexture(const char *filename, GLuint textureID, GLenum format) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);//change GL_RGB to GL_RGBA for blending
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture: %s\n", filename);
    }
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
	angle += 0.8;
	if (angle > 360.0f)
		angle = angle - 360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);

}





