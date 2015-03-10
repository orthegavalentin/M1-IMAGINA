#include <iostream>
#include <stdio.h>    
#include <stdlib.h>    
#include <math.h>
#include <GL/glut.h> 

#include "Point.cpp"
#include "Vector.cpp"
#include "Fonctions.cpp"

using namespace std;

#define WIDTH  800
#define HEIGHT 800
#define RED   1
#define GREEN 1
#define BLUE  1
#define ALPHA 1
#define KEY_ESC 27

GLint winWidth=600, winHeight=600;
GLfloat eyeX=0.0, eyeY=0.0, eyeZ=2.0;
GLfloat theta=270.0, phi=180.0;
GLfloat upX=0.0, upY=1.0, upZ=0.0;
GLfloat r=2.0;

void init_scene();
void render_scene();
GLvoid initGL();
GLvoid window_display();
GLvoid window_reshape(GLsizei width, GLsizei height); 
GLvoid window_key(unsigned char key, int x, int y); 



GLvoid initGL(){
	glClearColor(RED, GREEN, BLUE, ALPHA); 
	glEnable(GL_DEPTH_TEST);		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1,1,-1,1,.6,300);	       
}

void init_scene(){
}

GLvoid window_display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);		// set to Model View before drawing
	glLoadIdentity();
	gluLookAt(eyeX,eyeY,eyeZ,0,0,0,upX, upY, upZ);
	render_scene();
	glutSwapBuffers();
	glFlush();
}

GLvoid window_reshape(GLsizei width, GLsizei height){  
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

void eyePosition( void ) {
	eyeX = r * sin(theta*0.0174532) * sin(phi*0.0174532);
	eyeY = r * cos(theta*0.0174532);
	eyeZ = r * sin(theta*0.0174532) * cos(phi*0.0174532);
	GLfloat dt=1.0;
	GLfloat eyeXtemp = r * sin(theta*0.0174532-dt) * sin(phi*0.0174532);
	GLfloat eyeYtemp = r * cos(theta*0.0174532-dt);
	GLfloat eyeZtemp = r * sin(theta*0.0174532-dt) * cos(phi*0.0174532); 

	upX=eyeXtemp-eyeX;
	upY=eyeYtemp-eyeY;
	upZ=eyeZtemp-eyeZ;

	glutPostRedisplay();
}

GLvoid window_key(unsigned char key, int x, int y){  
	switch (key) { 
		case KEY_ESC:
		exit(1);
		break;

		default:
		printf ("La touche %d n est pas active.\n", key);
		break;

	}
}

// OpenGL/GLUT C code (by H. Shirokawa)
void onMouseMove(int x, int y) { 
// Mouse point to angle conversion
   theta = (360.0/(double)winHeight)*(double)y*0.7; //3.0 rotations possible
   phi = (360.0/(double)winWidth)*(double)x*0.7; 
// Restrict the angles within 0~360 deg (optional)
   if(theta > 360)theta = fmod((double)theta,360.0);
   if(phi > 360)phi = fmod((double)phi,360.0);
   eyePosition();
}

void render_scene(){
doelia
	drawGrid();
	
	glColor3f(0, 0, 0);
	glLineWidth(1);
	glPointSize(4);
	
	long nb = 6;
	Point** tabPts = new Point*[nb];
	tabPts[0] = new Point(-8,-7,0);
	tabPts[1] = new Point(7,-6,0);
	tabPts[2] = new Point(-1,0,0);
	tabPts[3] = new Point(-4,6,0);
	tabPts[4] = new Point(-1,8,0);
	tabPts[5] = new Point(9,4,0);
	drawCurve(tabPts, nb);

	// Point** tabRetour2 = bezierCurveByBernstein(tabPts, nb, 20);
	// glColor3f(0, 1.0, 0);
	// glLineWidth(2);
	// drawCurve(tabRetour2, 20);

	Point** tabRetourC = bezierCurveByCasteljau(tabPts, nb, 20);
	glColor3f(1.0, 0, 0);
	glLineWidth(1);
	drawCurve(tabRetourC, 20);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Affichage 3D");
	initGL();
	init_scene();
	glutDisplayFunc(&window_display);
	glutReshapeFunc(&window_reshape);
	glutPassiveMotionFunc(onMouseMove);
	glutKeyboardFunc(&window_key);
	glutMainLoop();

	return 1;
}