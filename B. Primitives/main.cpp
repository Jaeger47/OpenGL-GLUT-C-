/* Coded by Mark Daniel G. Dacer
 * www.github.com/Jaeger47
 */

#include <iostream>
#include <GL/glut.h>


void init()
{
	//set background to black
	glClearColor(0.0,0.0,0.0,1.0);
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	//size of the world
	gluOrtho2D(-10,10,-10,10);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);//clear color

	glLoadIdentity();//clear transforms

	//draw triangle
	glBegin(GL_TRIANGLES);
		glVertex2f(-6.0f, 1.0f);
		glVertex2f(-2.0f, 1.0f);
		glVertex2f(-4.0f, 5.0f);
	glEnd();

	//draw square
	glBegin(GL_QUADS);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(5.0f, 1.0f);
		glVertex2f(5.0f, 5.0f);
		glVertex2f(1.0f, 5.0f);
	glEnd();

	//draw star
	glBegin(GL_LINE_LOOP);
		glVertex2f(-7.0f, -7.0f);
		glVertex2f(-4.0f, -5.5f);
		glVertex2f(-1.0f, -7.0f);
		glVertex2f(-2.0f, -5.0f);
		glVertex2f(-1.0f, -3.0f);
		glVertex2f(-3.0f, -3.0f);
		glVertex2f(-4.0f, -1.0f);
		glVertex2f(-5.0f, -3.0f);
		glVertex2f(-7.0f, -3.0f);
		glVertex2f(-6.0f, -5.0f);
	glEnd();

	//draw pentagon
	glBegin(GL_POLYGON);
		glVertex2f(2.0f, -7.0f);
		glVertex2f(6.0f, -7.0f);
		glVertex2f(7.0f, -4.0f);
		glVertex2f(4.0f, -2.0f);
		glVertex2f(1.0f, -4.0f);
	glEnd();


	glFlush(); //Send the scene to the screen
}



int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //display modes

	glutInitWindowPosition(200,100); //window postion
	glutInitWindowSize(500,500); //window size
	glutCreateWindow ("Primitives - github.com/Jaeger47"); //create the initialized window with name

	glutDisplayFunc(display); //initialize display function
	glutReshapeFunc(reshape); //initialize reshape function

	init();
	glutMainLoop();//loop at the functions

}



