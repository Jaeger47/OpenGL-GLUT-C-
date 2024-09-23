#include <GL/glut.h>

float _angle = -0.0f;

//set materials
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 60.0 };

//set world light
GLfloat light_position[] = { 0.0, 0.0, 5.0, 0.0 };
GLfloat light[] = { 0.5, 0.5, 0.5 };
GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };


//Initializes 3D rendering
void initRendering() {

	glClearColor(0.0,0.0,0.0,1.0); //set background to black

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glEnable(GL_AUTO_NORMAL);

	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

//cube
void cube(){
	glBegin(GL_QUADS);
		//front
		glColor3f(1.0f,0.0f,0.0f); //red
		glNormal3f(0.0f,0.0f,1.0f);//face normals
		glNormal3f(-0.7f,-0.7,0.0f);//normalized vertex
			glVertex3f(-1.0f, -1.0f, 0.0f);
		glNormal3f(0.7f,-0.7,0.0f);//
			glVertex3f(1.0f, -1.0f, 0.0f);
		glNormal3f(0.7f,0.7,0.0f);//
			glVertex3f(1.0f, 1.0f, 0.0f);
		glNormal3f(-0.7f,0.7,0.0f);//
			glVertex3f(-1.0f, 1.0f, 0.0f);

		//right
		glColor3f(0.0f,1.0f,0.0f); //green
		glNormal3f(1.0f,0.0f,0.0f);//face normals
		glNormal3f(0.7f,-0.7f,0.0f);
			glVertex3f(1.0f, -1.0f, 0.0f);
		glNormal3f(0.48f,-0.48f,-0.72f);
			glVertex3f(1.0f, -1.0f, -1.5f);
		glNormal3f(0.48f,0.48f,-0.72f);
			glVertex3f(1.0f, 1.0f, -1.5f);
		glNormal3f(0.70f,0.70f,0.0f);
			glVertex3f(1.0f, 1.0f, 0.0f);

		//back
		glColor3f(0.0f,0.0f,1.0f); //blue
		glNormal3f(0.0f,0.0f,-1.0f);//face normals
		glNormal3f(-0.48f,-0.48f,-0.72f);
			glVertex3f(-1.0f, -1.0f, -1.5f);
		glNormal3f(0.48f,-0.48f,-0.72f);
			glVertex3f(1.0f, -1.0f, -1.5f);
		glNormal3f(0.48f,0.48f,-0.72f);
			glVertex3f(1.0f, 1.0f, -1.5f);
		glNormal3f(-0.48f,0.48f,-0.72f);
			glVertex3f(-1.0f, 1.0f, -1.5f);

		//left
		glColor3f(1.0f,1.0f,0.0f); //yellow
		glNormal3f(-1.0f,0.0f,0.0f);//face normals
		glNormal3f(-0.70f,-0.70f,0.0f);
			glVertex3f(-1.0f, -1.0f, 0.0f);
		glNormal3f(-0.48f,-0.48f,-0.72f);
			glVertex3f(-1.0f, -1.0f, -1.5f);
		glNormal3f(-0.48f,0.48f,-0.72f);
			glVertex3f(-1.0f, 1.0f, -1.5f);
		glNormal3f(-0.70f,0.70f,0.0f);
			glVertex3f(-1.0f, 1.0f, 0.0f);


	glEnd();

}

//Draws the 3D scene
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//setting world lighting
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); //add ambient lighting

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light ); //add diffuse specular lighting
    glLightfv(GL_LIGHT0, GL_SPECULAR, light ); //add specular lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);//set light position


	//setting object materials
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //set object specular mateial
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// set shininess

	glTranslatef(0.0f, 0.0f, -15.0f); //move object in -z axis to seen in display

	glPushMatrix();
        glColor3f(0.0f, 1.0f, 0.0f);//add color material to object
        glTranslatef(3.0f, -3.0f, 0.0f); //location
        glRotatef(_angle, 0.0f, 1.0f, 0.0f);//rotation animation
        glutSolidTeapot (1.5);
	glPopMatrix();

	glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
        glTranslatef(-3.0f, -3.0f, 0.0f); //location
        glRotatef(_angle, 1.0f, 0.0f, 0.0f); //rotation animation
        glutSolidTorus(0.5,1,24,48);
	glPopMatrix();

	glPushMatrix();
        glColor3f(0.0f, 0.0f, 1.0f);//add color material to object
        glTranslatef(0.0f, 1.0f, 6.0f); //location
        glRotatef(_angle, 0.0f, 1.0f, 0.0f); //rotation animation
        cube();
	glPopMatrix();


	glutSwapBuffers();
}


//Called when the window is resized
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void update(int value) {
	_angle += 1.5f;
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
	glutCreateWindow("Lighting - github.com/Jaeger47/Learning-OpenGL");
	initRendering();

	//Set handler functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}


