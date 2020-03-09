// Mason Hamilton
// CST-310
// Project 6
// 3-8-20

//All the inlcluded libaries
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <string>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "Fractal.h"

using namespace std;
//reading in the file name
string fileName = "tree.txt";
//setting the file to the fractal
Fractal treeFractal(fileName);

GLuint plane;
//assigning fucntions for our camera to rotate around 
//also used for our arrow keys to move the camera in the terminal
float angle = 5.5f;
float lx = 0.0f, lz=1.0f;
float x = 0.0f, z = -2.0f;
//disoplay fucntion that creates the view for us to use openGL
//also used to move the camera
void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(x, 1.0f, z, x+lx, 1.0f, z+lz, 0.0f, 1.0f, -1.0f);
	gluLookAt(x, 10.0, z, x+lx, 0.0, z+lz, 0.0, 0.0, -1.0);
	glTranslatef(0,0,0);
	glColor3f(8.0f, 0.5f, 0.09f);
	glCallList(plane);
	glFlush();
	glutSwapBuffers();
}
//reshape is used to alter our view of the openGL scene
void reshape(GLint w, GLint h)
{
    glViewport(0,0,w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, (GLfloat)w/(GLfloat)h, 1, 40);
    glMatrixMode(GL_MODELVIEW);
}
//Fucntion used to move the camera after the scene is loaded
//can be used to get a better view of the fractal
void keyMovement(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_RIGHT :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}
//our main fucntion that calls all of our other fucntions
//this is what shows the screen, the size, postion
// also shows our output of what our fractal created.
int main(int argc, char**argv){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500,500);
	glutInitWindowSize(800,800);
	glutCreateWindow("Fractal Plane");
	plane = glGenLists(1);
	glNewList(plane,GL_COMPILE);
        treeFractal.draw();
    glEndList();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutSpecialFunc(keyMovement);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    return 1;


}

