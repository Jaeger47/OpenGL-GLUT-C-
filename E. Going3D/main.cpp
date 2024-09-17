/* Going3D by Mark Daniel G. Dacer
 * www.github.com/Jaeger47
 */


#include <GL/glut.h>

float _angle = -70.0f;

//Initializes 3D rendering
void initRendering() {

	glClearColor(0.0f,0.0f,0.0f,1.0f); //set background to black
	glEnable(GL_DEPTH_TEST);
}

//Draws the 3D scene
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display

	glRotatef(_angle, 1, 1, 1); //rotation of all axis

	//front wall
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -4.0f, 2.0f);
		glVertex3f(3.0f, -4.0f, 2.0f);
		glVertex3f(3.0f, 1.0f, 2.0f);
		glVertex3f(0.0f, 4.0f, 2.0f);
		glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right wall
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, -4.0f, 2.0f);
		glVertex3f(3.0f, -4.0f, -2.0f);
		glVertex3f(3.0f, 1.0f, -2.0f);
		glVertex3f(3.0f, 1.0f, 2.0f);
	glEnd();

	//back wall
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -4.0f, -2.0f);
		glVertex3f(3.0f, -4.0f, -2.0f);
		glVertex3f(3.0f, 1.0f, -2.0f);
		glVertex3f(0.0f, 4.0f, -2.0f);
		glVertex3f(-3.0f, 1.0f, -2.0f);
	glEnd();

	//left wall
	glColor3f(1,0,1);
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, -4.0f, 2.0f);
		glVertex3f(-3.0f, -4.0f, -2.0f);
		glVertex3f(-3.0f, 1.0f, -2.0f);
		glVertex3f(-3.0f, 1.0f, 2.0f);
	glEnd();

	//right roof
	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, 1.0f, 2.0f);
		glVertex3f(3.0f, 1.0f, -2.0f);
		glVertex3f(0.0f, 4.0f, -2.0f);
		glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//left roof
	glColor3f(0,1,1);
	glBegin(GL_POLYGON);
		glVertex3f(-3.0f, 1.0f, 2.0f);
		glVertex3f(-3.0f, 1.0f, -2.0f);
		glVertex3f(0.0f, 4.0f, -2.0f);
		glVertex3f(0.0f, 4.0f, 2.0f);
	glEnd();

	//below floor
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
		glVertex3f(3.0f, -4.0f, 2.0f);
		glVertex3f(3.0f, -4.0f, -2.0f);
		glVertex3f(-3.0f, -4.0f, -2.0f);
		glVertex3f(-3.0f, -4.0f, 2.0f);

	glEnd();

	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//rotation animation logic
void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(1000/60, update, 0);
}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	//Create the window
	glutCreateWindow("Going3D - github.com/Jaeger47/Learning-OpenGL");
	initRendering();

	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}




