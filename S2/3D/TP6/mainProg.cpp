#include <iostream>
#include <stdio.h>    
#include <stdlib.h>    
#include <math.h>
#include <GL/glut.h> 

#include "Point.cpp"
#include "Vector.cpp"
#include "tp6.cpp"

using namespace std;

#define WIDTH  700
#define HEIGHT 700
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
	//glFrustum(-0.1,0.1,-0.1,0.1,0.01,300);	       
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
   theta = (360.0/(double)winHeight)*(double)y*1.0; //3.0 rotations possible
   phi = (360.0/(double)winWidth)*(double)x*1.0; 
// Restrict the angles within 0~360 deg (optional)
   if(theta > 360)theta = fmod((double)theta,360.0);
   if(phi > 360)phi = fmod((double)phi,360.0);
   eyePosition();
}

void drawGrid(){
	glBegin(GL_LINES);
	for(int i=-10;i<=10;i++) {
		if (i==0) { 
			glColor3f(.5,.5,.5);
		} else { 
			glColor3f(.8,.8,.8);
		}
		glVertex3f(i,-10,0);
		glVertex3f(i,10,0);
		if (i==0) {
			glColor3f(.5,.5,.5);
		} else {
			glColor3f(.8,.8,.8);
		}
		glVertex3f(-10,i,0);
		glVertex3f(10,i,0);
	}
	for(int i=-10;i<=10;i++) {
		if (i==0) { 
			glColor3f(.5,.5,.5);
		} else { 
			glColor3f(.8,.8,.8);
		}
		glVertex3f(i,0,-10);
		glVertex3f(i,0,10);
		if (i==0) {
			glColor3f(.5,.5,.5);
		} else {
			glColor3f(.8,.8,.8);
		}
		glVertex3f(-10,0,i);
		glVertex3f(10,0,i);
	}
	for(int i=-10;i<=10;i++) {
		if (i==0) { 
			glColor3f(.5,.5,.5);
		} else { 
			glColor3f(.8,.8,.8);
		}
		glVertex3f(0,-10,i);
		glVertex3f(0,10,i);
		if (i==0) {
			glColor3f(.5,.5,.5);
		} else {
			glColor3f(.8,.8,.8);
		}
		glVertex3f(0,i,-10);
		glVertex3f(0,i,10);
	}
	glEnd();
}

void render_scene(){

	//drawGrid();
	
	glColor3f(1.0, 0.37, 0);
	//glColor3f(0.3, 0.3, 0.3);
	glLineWidth(1);
	glPointSize(4);

	drawFile();

}

GLvoid window_reshape(GLsizei width, GLsizei height){  
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double a =  drawFile();
	cout << a << " ";
	glOrtho(-a, a, -a, a, -a, a);
	glMatrixMode(GL_MODELVIEW);
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