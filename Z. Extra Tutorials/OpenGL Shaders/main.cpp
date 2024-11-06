#include <GL/glew.h>
#include <GL/glut.h>
#include <string.h>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

float angle = 0.0f;  // Angle for rotation
const int NUM_SHADERS = 1; // Number of shaders
GLuint shaderProgramHandles[NUM_SHADERS];
int currentShaderIndex = 0; // Current shader index
GLint timeLocation; // Location of the time uniform
int switchInterval = 3000; // Time in milliseconds to switch shaders

void readTextFile(string filename, char* &output) {
    string buf = string("");
    string line;

    ifstream in(filename.c_str());
    while(getline(in, line))
        buf += line + "\n";
    output = new char[buf.length()+1];
    strncpy(output, buf.c_str(), buf.length());
    output[buf.length()] = '\0';

    in.close();
}

void setupShader(int index, const char* vertexFile, const char* fragmentFile) {
    char *vertexShaderString, *fragmentShaderString;

    readTextFile(vertexFile, vertexShaderString);
    readTextFile(fragmentFile, fragmentShaderString);

    GLuint vertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShaderHandle, 1, (const char**)&vertexShaderString, NULL);
    glShaderSource(fragmentShaderHandle, 1, (const char**)&fragmentShaderString, NULL);

    delete [] vertexShaderString;
    delete [] fragmentShaderString;

    glCompileShader(vertexShaderHandle);
    glCompileShader(fragmentShaderHandle);

    shaderProgramHandles[index] = glCreateProgram();
    glAttachShader(shaderProgramHandles[index], vertexShaderHandle);
    glAttachShader(shaderProgramHandles[index], fragmentShaderHandle);
    glLinkProgram(shaderProgramHandles[index]);

     timeLocation = glGetUniformLocation(shaderProgramHandles[index], "time");
}

void setupShaders() {
    setupShader(0, "toon.vert", "toon.frag");


    glUseProgram(shaderProgramHandles[currentShaderIndex]);
}

// Function to initialize the OpenGL rendering settings
void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat position[] = { 0.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_NORMALIZE);
}

// Function to handle window resizing
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

// Function to update the rotation angle (idle callback)
void update(int value) {
    angle += 1.0f;
    if (angle > 360) {
        angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

// Function to switch shaders
void switchShaders(int value) {
    currentShaderIndex = (currentShaderIndex + 1) % NUM_SHADERS;
    glUseProgram(shaderProgramHandles[currentShaderIndex]); // Use the new shader program
    glutTimerFunc(switchInterval, switchShaders, 0); // Schedule next switch
}

// Function to display the teapot with rotation animation
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Translate the entire scene back (optional, can adjust for different view)
    glTranslatef(0.0f, 0.0f, -5.0f);

    setupShaders();
    float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Get time in seconds
    glUniform1f(timeLocation, currentTime); // Pass time to shader // ADD THIS LINE

    // First object (Teapot)
    glPushMatrix();
    glTranslatef(1.0f, 0.0f, 0.0f);  // Move to the side
    glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Rotate around its own Y-axis
    glColor3f(0.5f, 0.5f, 0.9f);
    glutSolidTeapot(0.5);  // Render teapot
    glPopMatrix();

    // Second object (Torus)
    glPushMatrix();
    glTranslatef(-1.0f, -1.0f, 0.0f);  // Move to the other side
    glRotatef(angle, 0.0f, 1.0f, 0.0f);  // Rotate around its own Y-axis
    glColor3f(0.9f, 0.5f, 0.5f);
    glutSolidTorus(0.2, 0.4, 32, 32);  // Render torus
    glPopMatrix();

    glUseProgram(0);

    glutSwapBuffers();
}

// Main function to set up the GLUT and OpenGL environment
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Teapot with Multiple Shaders");

    glewInit();
    if(!glewIsSupported("GL_VERSION_2_0")) {
        fprintf(stderr, "Error! OpenGL 2.0 not supported on this machine.\n");
        exit(1);
    }

    initRendering();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);

    // Start the shader switch timer
    glutTimerFunc(switchInterval, switchShaders, 0);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
