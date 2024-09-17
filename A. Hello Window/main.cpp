//Coded by Mark Daniel G. Dacer
//github.com/Jaeger47

#include <iostream>
#include <GL/glut.h>


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);//Indicates the buffers currently enabled for color writing.
	glFlush(); //Send the scene to the screen
}


int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //sets diplay to rgb

	glutInitWindowPosition(200,100); //position of the program in your screen
	glutInitWindowSize(500,500); //size of the program window

   	glutCreateWindow("Hello Window - github.com/Jaeger47"); //window title
	glutDisplayFunc(display);//call display function
	glutMainLoop(); //loop all functions

}

