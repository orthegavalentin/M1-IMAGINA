///////////////////////////////////////////////////////////////////////////////
// IUT de Provence, site d'Arles                                      2003-2004
// D�partement Informatique
// 2�me ann�e
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Rendu r�aliste
// Auteur : S�bastien Thon
// ----------------------------------------------------------------------------
// Base du TP 1
// Base d'un programme permettant d'afficher une sc�ne compos�e d'un sol, de
// maisons et d'arbres. On placera des sources de lumi�re, on sp�cifiera les
// mat�riaux des diff�rents objets et on utilisera un effet de brouillard.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> 

#define WIDTH   640										// Largeur de la fen�tre OpenGL
#define HEIGHT  480										// Hauteur de la fen�tre OpenGl

#define KEY_ESC 27										// Code ASCII de la touche Echap

#define MAISON  1										// Code identificant la display list de la maison
#define ARBRE   2										// Code identificant la display list de l'arbre

float	xpos = 0, zpos = -50;							// Position de la cam�ra
int		angle_x = 0, angle_y = 0;						// Orientation de la cam�ra
int		mouse_x = 0, mouse_y = 0;						// Position de la souris

float vx=0,vy=0;

//*****************************************************************
//* A FAIRE :
//* D�clarer des tableaux contenant les caract�ristiques (Ambient,
//* diffus, sp�culaire) pour diff�rents mat�riaux :
//*    - sol
//*    - mur de maison
//*    - toit de maison
//*    - tronc d'arbre
//*    - feuillage d'arbre
//* Ex:
//*   GLfloat MatAmbient_sol[] = {0.0f, 0.5f, 0.0f, 1.0f};
//*   GLfloat MatDiffuse_sol[] = {0.0f, 0.7f, 0.0f, 1.0f};
//*   GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};
//*   GLfloat MatShininess_sol[1]={5.0f};
//*****************************************************************



///////////////////////////////////////////////////////////////////////////////
// Intitialisation de certains param�tres d'OpenGL.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid initGL()
{
	glClearColor(0, 0, 0, 1);							// Couleur servant � effacer la fen�tre (noir)
    glShadeModel(GL_SMOOTH);							// Mod�le d'ombrage : lissage de Gouraud
	glEnable(GL_CULL_FACE);								// Ne traite pas les faces cach�es
	glEnable(GL_DEPTH_TEST);							// Active le Z-Buffer
	glDepthFunc(GL_LEQUAL);								// Mode de fonctionnement du Z-Buffer
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Active la correction de perspective (pour ombrage, texture, ...)


	//*****************************************************************
	//* A FAIRE :
	//*
	//* 1. Cr�er la source de lumi�re 0 (GL_LIGHT0) en tant que source de
	//*    lumi�re directionnelle, en pr�cisant :
	//*      - sa position
	//*      - sa couleur ambiante
	//*      - sa couleur diffuse
	//*      - sa couleur sp�culaire
	//*
	//* 2. Activer la source de lumi�re 0.
	//*
	//* 3. Activer l'�clairage g�n�ral
	//*****************************************************************


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat fogColor[4] = {0.6f,0.6f,0.6f,0.0f};
	glFogf(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 40);
	glFogf(GL_FOG_END, 130);
	glFogfv(GL_FOG_COLOR, fogColor);
	glEnable(GL_FOG);


}



///////////////////////////////////////////////////////////////////////////////
// Affiche le sol de la sc�ne.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_sol()
{
	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du mat�riau
	//* cr�e pour le sol.
	//*****************************************************************


	GLfloat MatAmbient_sol[] = {0.0f, 0.8f, 0.0f, 1.0f};
	GLfloat MatDiffuse_sol[] = {0.0f, 0.8f, 0.0f, 1.0f};
	GLfloat MatSpecular_sol[]= {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat MatShininess_sol[1]={5.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_sol);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_sol);
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_sol);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_sol);

	glColor3f(0.0f,0.8f,0.0f);							// Couleur courante : vert

	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);									// Affichage d'un quadrilat�re
	glVertex3d(-100, 0, -100);
	glVertex3d(-100, 0,  100);
	glVertex3d( 100, 0,  100);
	glVertex3d( 100, 0, -100);
	glEnd();
}



///////////////////////////////////////////////////////////////////////////////
// Affiche une maison.
//-----------------------------------------------------------------------------
// Param�tres :
//    xp,yp,zp (in) : position de la maison.
//    yr       (in) : angle de rotation (en degr�s) de la maison p/r � l'axe y.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_maison( float xp, float yp, float zp, float yr )
{
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation
	glRotatef(yr, 0,1,0);								// et une rotation
	glCallList(MAISON);									// Appelle la display list de la maison
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche un arbre.
//-----------------------------------------------------------------------------
// Param�tres :
//    xp,yp,zp (in) : position de l'arbre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void affiche_arbre( float xp, float yp, float zp )
{
	//*****************************************************************
	//* A FAIRE :
	//* Afficher un arbre en faisant appel � sa display list.
	//*****************************************************************
	glPushMatrix();										// Sauve la matrice de vue actuelle
	glTranslatef(xp, yp, zp);							// Positionne la maison avec une translation							// Positionne la maison avec une translation
	glRotatef(90, 1,0,0);	
	glCallList(ARBRE);									// Appelle la display list de la maison
	glPopMatrix();										// Restaure la matrice de vue
}



///////////////////////////////////////////////////////////////////////////////
// Affiche les diff�rents objets de la sc�ne.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////


void affiche_scene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLfloat Light0Dif[4] = {1.0f, 0.37f, 0.0f, 1.0f};
	GLfloat Light0Spec[4] = {1.0f, 0.37f, 0.0f, 1.0f};
	GLfloat Light0Amb[4] = {0.5f, 0.5f, 0.5f, 1.0f};

	glLightfv(GL_LIGHT0,GL_DIFFUSE, Light0Dif);
	glLightfv(GL_LIGHT0,GL_SPECULAR, Light0Spec);
	glLightfv(GL_LIGHT0,GL_AMBIENT, Light0Amb);
	//GLfloat direction[] = {1.0,1.0,1.0,0.0};
	//glLightfv(GL_LIGHT0, GL_POSITION, direction);
	GLfloat position[] = {vx,vy,1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	affiche_sol();

	//*****************************************************************
	//* A FAIRE :
	//* Afficher quelques maisons et quelques arbres.
	//*****************************************************************
	affiche_maison( 0, 0, -6, 30 );
	affiche_maison( 12, 0, 4, -45 );
	affiche_maison( -9, 0, 7, 90 );

	affiche_arbre(-1,5,2);
	affiche_arbre(-13,5,15);

	GLfloat MatAmbient_s[] = {0.8f, 0.8f, 0.0f, 1.0f};
	GLfloat MatDiffuse_s[] = {0.8f, 0.8f, 0.0f, 1.0f};
	GLfloat MatSpecular_s[]= {0.9f, 0.9f, 0.9f, 1.0f};
	GLfloat MatShininess_s[1]={10.0f};
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_s);
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_s);
	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_s);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_s);

	glPushMatrix();
	glTranslatef(vx, vy, 0);
	glColor3f(0.8f,0.8f,0.0f);
	glutSolidSphere(2,24,24);
	glPopMatrix();

	glutSwapBuffers();							// Affiche la sc�ne (affichage en double buffer)

}



///////////////////////////////////////////////////////////////////////////////
// Call-back : affichage dans la fen�tre.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_display()
{
	// On efface les pixels de l'image (color buffer) et le Z-Buffer (depth buffer).
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// On initialise la matrice de vue avec la matrice identit�.
	glLoadIdentity();

	// On applique une translation et une rotation � la sc�ne pour simuler
	// un d�placement de cam�ra.
	glTranslatef(xpos,0,zpos);
	glRotatef(angle_x, 1,0,0);
	glRotatef(angle_y, 0,1,0);

	//*****************************************************************
	//* A FAIRE :
	//* Re-sp�cifier la position des sources de lumi�re avec
	//* glLightfv() pour qu'elles soient aussi affect�es par la
	//* translation et la rotation qu'on vient d'appliquer � la sc�ne.
	//*****************************************************************

	// On affiche la sc�ne.
	affiche_scene();

	// On force OpenGL � afficher avant de passer � la suite.
	glFlush();
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : redimensionnement de la fen�tre.
//-----------------------------------------------------------------------------
// Param�tres :
//    width, height (in) : nouvelles largeur et hauteur de la fen�tre.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_reshape(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);

	glMatrixMode(GL_MODELVIEW);
}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des �v�nements clavier.
//-----------------------------------------------------------------------------
// Param�tres :
//    key (in) : code ascii de la touche utilis�e.
//    x,y (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
GLvoid callback_keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case KEY_ESC:						// 'ECHAP' :
			exit(1);						// on quitte le programme
			break;
		case 'z':						// 'ECHAP' :
			vy+=1;						// on quitte le programme
			affiche_scene();
			break;
		case 's':						// 'ECHAP' :
			vy-=1;						// on quitte le programme
			affiche_scene();
			break;
		case 'q':						// 'ECHAP' :
			vx-=1;						// on quitte le programme
			affiche_scene();
			break;
		case 'd':						// 'ECHAP' :
			vx+=1;						// on quitte le programme
			affiche_scene();
			break;
		}
	}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des touches speciales du clavier.
//-----------------------------------------------------------------------------
// Param�tres :
//    key (in) : code ascii de la touche utilis�e.
//    x,y (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
	GLvoid callback_special(int key, int x, int y)
	{
	float speed = 1.0f;						// Vitesse de d�placement de la cam�ra

	switch (key)
	{
		case GLUT_KEY_UP:					// Fl�che vers le haut : 
			zpos += speed;					// on d�place la cam�ra selon z-
			affiche_scene();			// et on demande le r�affichage.
			break;

		case GLUT_KEY_DOWN:					// Fl�che vers le bas :
			zpos -= speed;					// on d�place la cam�ra selon z+
			affiche_scene();			// et on demande le r�affichage.
			break;

		case GLUT_KEY_LEFT:					// Fl�che vers la gauche :
			xpos += speed;					// on d�place la cam�ra selon x-
			affiche_scene();			// et on demande le r�affichage.
			break;

		case GLUT_KEY_RIGHT:				// Fl�che vers la droite :
			xpos -= speed;					// on d�place la cam�ra selon x+
			affiche_scene();			// et on demande le r�affichage.
			break;
		}
	}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion de clics souris.
//-----------------------------------------------------------------------------
// Param�tres :
//    button (in) : code du bouton utilis�.
//    state  (in) : �tat du bouton.
//    x,y    (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
	GLvoid callback_mouse(int button, int state, int x, int y)
	{
		if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		{
			mouse_x = x;
			mouse_y = y;
		}
	}



///////////////////////////////////////////////////////////////////////////////
// Call-back : gestion des d�placements de la souris.
//-----------------------------------------------------------------------------
// Param�tres :
//    x,y    (in) : coordonn�es de la souris.
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
	GLvoid callback_motion(int x, int y)
	{
	angle_x += y - mouse_y;						// Modifie la direction de vue de la cam�ra
	angle_y += x - mouse_x;						// en fonction de la position de la souris
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();						// Demande le r�affichage
}



///////////////////////////////////////////////////////////////////////////////
// Construit une maison dans une display-list.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
void construit_maison()
{
	//*****************************************************************
	//* A FAIRE :
	//* Associer une normale � chacun des polygones suivants.
	//*****************************************************************

	glNewList(MAISON, GL_COMPILE);

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du mat�riau
	//* cr�e pour les murs (glMaterialfv()).
	//*****************************************************************
		glColor3f(1.0f,1.0f,1.0f);			// Couleur courante : blanc

		GLfloat MatAmbient_mur[] = {0.9f, 0.9f, 0.9f, 1.0f};
		GLfloat MatDiffuse_mur[] = {0.9f, 0.9f, 0.9f, 1.0f};
		GLfloat MatSpecular_mur[]= {0.1f, 0.1f, 0.1f, 1.0f};
		GLfloat MatShininess_mur[1]={0.5f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_mur);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_mur);
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_mur);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_mur);

		// Mur de face
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3d(-4, 0, 5);
		glVertex3d( 4, 0, 5);
		glVertex3d( 4, 5, 5);
		glVertex3d(-4, 5, 5);
		glEnd();

		// Mur arri�re
		glNormal3f(0.0f, 0.0f, -1.0f);
		glBegin(GL_QUADS);
		glVertex3d(-4, 0, -5);
		glVertex3d(-4, 5, -5);
		glVertex3d( 4, 5, -5);
		glVertex3d( 4, 0, -5);
		glEnd();

		// Mur gauche
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3d(-4, 0, -5);
		glVertex3d(-4, 0,  5);
		glVertex3d(-4, 5,  5);
		glVertex3d(-4, 5, -5);
		glEnd();

		// Mur droit
		glNormal3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3d(4, 0, -5);
		glVertex3d(4, 5, -5);
		glVertex3d(4, 5,  5);
		glVertex3d(4, 0,  5);
		glEnd();

		// Triangle avant
		glNormal3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3d(-4, 5, 5);
		glVertex3d( 4, 5, 5);
		glVertex3d( 0, 8, 5);
		glEnd();

		// Triangle arri�re
		glNormal3f(0.0f, 0.0f, -1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3d( 4, 5, -5);
		glVertex3d(-4, 5, -5);
		glVertex3d( 0, 8, -5);
		glEnd();

	//*****************************************************************
	//* A FAIRE :
	//* Remplacer le glColor3f() suivant par l'utilisation du mat�riau
	//* cr�e pour le toit (glMaterialfv()).
	//*****************************************************************
		glColor3f(1.0f,0.0f,0.0f);			// Couleur courante : rouge

		GLfloat MatAmbient_toit[] = {0.9f, 0.2f, 0.2f, 1.0f};
		GLfloat MatDiffuse_toit[] = {0.9f, 0.2f, 0.2f, 1.0f};
		GLfloat MatSpecular_toit[]= {0.4f, 0.4f, 0.4f, 1.0f};
		GLfloat MatShininess_toit[1]={6.0f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_toit);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_toit);
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_toit);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_toit);

		// Toit versant droit
		glNormal3f(0.6f, 0.8f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3d(0, 8,  5);
		glVertex3d(4, 5,  5);
		glVertex3d(4, 5, -5);
		glVertex3d(0, 8, -5);
		glEnd();

		// Toit versant gauche
		glNormal3f(-0.6f, 0.8f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3d( 0, 8,  5);
		glVertex3d( 0, 8, -5);
		glVertex3d(-4, 5, -5);
		glVertex3d(-4, 5,  5);
		glEnd();

		glEndList();
	}



///////////////////////////////////////////////////////////////////////////////
// Construit un arbre dans une display-list.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
	void construit_arbre()
	{
	//*****************************************************************
	//* A FAIRE :
	//* Cr�er dans une display list un arbre dont le tronc sera un c�ne :
	//*     glutSolidCone()
	//* et le feuillage une sph�re :
	//*     glutSolidSphere()
	//* Pr�ciser le mat�riau pour chacun de ces �l�ments.
	//*****************************************************************

		glNewList(ARBRE, GL_COMPILE);

		glColor3f(0.4f,0.2f,0.4f);			// Couleur courante : marron

		GLfloat MatAmbient_arbre[] = {0.4f,0.2f,0.4f, 1.0f};
		GLfloat MatDiffuse_arbre[] = {0.4f,0.2f,0.4f, 1.0f};
		GLfloat MatSpecular_arbre[]= {0.1f, 0.1f, 0.1f, 1.0f};
		GLfloat MatShininess_arbre[1]={0.2f};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpecular_arbre);
		glMaterialfv(GL_FRONT, GL_SHININESS, MatShininess_arbre);
		glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmbient_arbre);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDiffuse_arbre);

		glutSolidSphere(3,12,12);

		glutSolidCone(2.0f,10.0f,12,12);


		glEndList();

	}



///////////////////////////////////////////////////////////////////////////////
// Initialise la sc�ne.
//-----------------------------------------------------------------------------
// Param�tres :
//    _
// Retour :
//    _
///////////////////////////////////////////////////////////////////////////////
	void initialise_scene()
	{
		construit_maison();
		construit_arbre();
	}



///////////////////////////////////////////////////////////////////////////////
// Fonction principale du programme.
//-----------------------------------------------------------------------------
// Param�tres :
//    argc (in) : nombre d'arguments de la ligne de commande.
//    argv (in) : tableau de cha�nes de caract�res contenant les arguments.
// Retour :
//    Un entier contenant le code de retour du programme.
///////////////////////////////////////////////////////////////////////////////
	int main(int argc, char *argv[])
	{
	// Initialisation de param�tres de Glut
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(WIDTH, HEIGHT);
		glutInitWindowPosition(0, 0);
		glutCreateWindow("Maison");

	// Intitialisation de param�tres d'OpenGL
		initGL();

	// Initialisation de la sc�ne
		initialise_scene();

	// D�claration des fonctions de call-back.
		glutDisplayFunc(&callback_display);
		glutReshapeFunc(&callback_reshape);
		glutKeyboardFunc(&callback_keyboard);
		glutSpecialFunc(&callback_special);
		glutMouseFunc(&callback_mouse);
		glutMotionFunc(&callback_motion);

	// Boucle principale de Glut.
		glutMainLoop();

	// Code de retour
		return 1;
	}
