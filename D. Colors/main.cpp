/* Colour by Mark Daniel G. Dacer
 * www.github.com/Jaeger47/Learning-OpenGL
 */

#include <GL/glut.h>

float angle = 0; //rotation angle

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//clear color

	glLoadIdentity();//clear transforms

	glPushMatrix();
	glTranslatef(5.0f, 5.0, 0.0f); // move object from origin
	glRotatef(angle, 0.0f, 0.0f, 1.0f); //animated rotation

	//draw triangle
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); //red
		glVertex2f(-2.0f, -2.0f);
		glColor3f(0.0f, 1.0f, 0.0f); //green
		glVertex2f(2.0f, -2.0f);
		glColor3f(0.0f, 0.0f, 1.0f); //blue
		glVertex2f(0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5.0f, 5.0, 0.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	//draw square
	glBegin(GL_QUADS);
		glColor3f(0.0f, 1.0f, 1.0f); //cyan
		glVertex2f(-2.0f, -2.0f);
		glVertex2f(2.0f, -2.0f);
		glVertex2f(2.0f, 2.0f);
		glVertex2f(-2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -5.0, 0.0f);
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	//draw pentagon
	glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 1.0f); //magenta
		glVertex2f(-1.0f, -2.0f);
		glVertex2f(1.0f, -2.0f);
		glVertex2f(2.0f, 1.0f);
		glVertex2f(0.0f, 3.0f);
		glVertex2f(-2.0f, 1.0f);
	glEnd();
	glPopMatrix();

	glFlush(); //Send the scene to the screen
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10,10,-10,10);//size of the world
	glMatrixMode(GL_MODELVIEW);
}

void update(int)
{

	//looping animation logic
	angle+=0.8;
	if(angle>360.0f)
		angle=angle-360.0f;

	glutPostRedisplay();
	glutTimerFunc(1000/60,update,0);

}


void init()
{

	glClearColor(0.1,0.1f,0.1f,1.0f); //set background to black

}

int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //display modes

	glutInitWindowPosition(200,100); //window postion
	glutInitWindowSize(500,500); //window size
	glutCreateWindow ("Colour - github.com/Jaeger47/Learning-OpenGL"); //create the initialized window with name

	glutDisplayFunc(display); //initialize display function
	glutReshapeFunc(reshape); //initialize reshape function

	init();

	glutTimerFunc(1000/60,update,0); //add timer

	glutMainLoop();//loop at the functions

}

