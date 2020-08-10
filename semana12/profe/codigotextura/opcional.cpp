//Programa que genera cubos de materiales y de imagenes bitmap
//Antonio Davalos de los Rios
#include <stdio.h>
#include <gl/glut.h>		
#include <GL/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "bitmap.h"

static int spinx = 0;
static int spiny = 0;	
static int p1 = 1;
static int p2 = 1;
static int ry,rx,rz;
BITMAPINFO *TexInfo; /* Texture bitmap information */
GLubyte *TexBits; /* Texture bitmap pixel bits */
//int ry,rx,rz;
/* Inicializa las prpiedaes de material, fuente de luz y el z buffer*/
void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
glShadeModel (GL_SMOOTH);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glEnable(GL_DEPTH_TEST);
}

void display(void)
{
/*Matrices para la luz*/
GLfloat position[] = { 0.0, 0.0, 2.5, 0.0 };
GLfloat position2[] = { 0.0, 3.0, 3.0, 0.0 };
GLfloat light_ambient[]={0.4, 0.4, 0.4, 1.0};
GLfloat light_diffuse[]={0.4, 0.4, 0.4, 1.0};
GLfloat light_specular[]={0.8, 0.8, 0.8, 1.0};
/*Matrices para materiales*/
GLfloat no_mat[] = {0.0,0.0,0.0,1.0};
GLfloat mat_ambient[] = {0.7,0.7,0.7,1.0};
GLfloat mat_ambient_color[] = {0.8,0.8,0.2,1.0};
GLfloat mat_diffuse[] = {0.1,0.5,0.8,1.0};
GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
GLfloat no_shininess[] = {0.0};
GLfloat low_shininess[] = {5.0};
GLfloat high_shininess[] = {100.0};
GLfloat mat_emission[] = {0.3,0.2,0.2,1.0};

GLfloat mat_amb_diff[] = {0.1, 0.5, 0.8, 1.0};
GLfloat mat_amb_diff2[] = {1.0, 0.1, 0.1, 1.0};
GLfloat mat_emission1[] = {0.3,0.8,0.2,1.0};



glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix ();
//gluLookAt (6.0, 6.0, 8.0, 2.0, 3.0, 0.0, 0.0, 1.0, 0.0);
gluLookAt (-7.0, 7.0, 7.0, 2.0, 0.0, 0.0, 0.0, 1.0, 0.0);

/*luz 0*/
glPushMatrix ();
glRotated ((GLdouble) spinx, 1.0, 0.0, 0.0);
glRotated ((GLdouble) spiny, 0.0, 1.0, 0.0);
glLightfv (GL_LIGHT0, GL_POSITION, position);


glTranslated (0.0, 0.0,2.5 );
glDisable (GL_LIGHTING);
glColor3f (1.0, 1.0, 1.0);
glutWireCube (0.1);
glEnable (GL_LIGHTING);
glPopMatrix ();
/*fin luz 0*/

/*luz 1*/
glPushMatrix ();
glLightfv (GL_LIGHT1, GL_POSITION, position2);
glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);//GL_DIFFUSE
glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);

glTranslated (0.0,2.5,2.5);
glDisable (GL_LIGHTING);
glColor3f (1.0, 1.0, 1.0);
glutWireCube (0.1);
glEnable (GL_LIGHTING);
glPopMatrix ();
/*fin luz 1*/

/*cubo materiales*/
glPushMatrix ();
glScalef(2,2,2);
glRotatef(rx,1.0,0.0,0.0);
glRotatef(ry,0.0,1.0,0.0);
glRotatef(rz,0.0,0.0,1.0);

glPushMatrix ();
// Primer lado del cubo de materiales
glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

glBegin(GL_QUADS);
glNormal3f(0.0,0.0,1.0);
glVertex3f(0.5,0.5,0.5);
glVertex3f(-0.5,0.5,0.5);
glVertex3f(-0.5,-0.5,0.5);
glVertex3f(0.5,-0.5,0.5);
glEnd();
glPopMatrix ();

glPushMatrix ();
//Segunda cara del cubo
glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

glBegin(GL_QUADS);
glNormal3f(0.0,0.0,-1.0);
glVertex3f(-0.5,0.5,-0.5);
glVertex3f( 0.5,0.5,-0.5);
glVertex3f(0.5,-0.5,-0.5);
glVertex3f(-0.5,-0.5,-0.5);
glEnd();
glPopMatrix ();

glPushMatrix ();
//Tercera cara del cubo
glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

glBegin(GL_QUADS);
glNormal3f(-1.0,0.0,0.0);
glVertex3f(-0.5,0.5,0.5);
glVertex3f(-0.5,0.5,-0.5);
glVertex3f(-0.5,-0.5,-0.5);
glVertex3f(-0.5,-0.5,0.5);
glEnd();
glPopMatrix ();

glPushMatrix ();
//Cuarta cara del cubo de materiales
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

glBegin(GL_QUADS);
glNormal3f(1.0,0.0,0.0);
glVertex3f(0.5,0.5,0.5);
glVertex3f(0.5,-0.5,0.5);
glVertex3f( 0.5,-0.5,-0.5);
glVertex3f(0.5,0.5,-0.5);
glEnd();
glPopMatrix ();

glPushMatrix ();
//Quinta cara
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

glBegin(GL_QUADS);
glNormal3f(0.0,1.0,0.0);
glVertex3f(-0.5,0.5,-0.5);
glVertex3f(-0.5,0.5,0.5);
glVertex3f(0.5,0.5,0.5);
glVertex3f( 0.5,0.5,-0.5);
glEnd();
glPopMatrix ();

glPushMatrix ();
//Sexta cara
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

glBegin(GL_QUADS);
glNormal3f(0.0,-1.0,0.0);
glVertex3f(0.5,-0.5,-0.5);
glVertex3f(-0.5,-0.5,-0.5);
glVertex3f(-0.5,-0.5,0.5);
glVertex3f(0.5,-0.5,0.5);
glEnd();
glPopMatrix ();
glPopMatrix ();

/*fin cubo de materiales*/

//Despliegue del cubo con imagenes

glPushMatrix();

glTranslated (-2.0, 3.5,3.5 );
glRotatef(rx,1.0,0.0,0.0);
glRotatef(ry,0.0,1.0,0.0);
glRotatef(rz,0.0,0.0,1.0);
glColor3f(1.0, 1.0, 1.0);

//se activa el mapeado de texturas
glEnable(GL_TEXTURE_2D);
//Despliegue de primer textura
TexBits = LoadDIBitmap("abe.bmp", &TexInfo);
glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
GL_UNSIGNED_BYTE, TexBits);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//Fin despliegue primer textura
glBegin(GL_QUADS);
glNormal3f(0.0,0.0,1.0);
glTexCoord2f(1.0,1.0); glVertex3f(0.5,0.5,0.5);
glTexCoord2f(0.0,1.0); glVertex3f(-0.5,0.5,0.5);
glTexCoord2f(0.0,0.0); glVertex3f(-0.5,-0.5,0.5);
glTexCoord2f(1.0,0.0); glVertex3f(0.5,-0.5,0.5);
glEnd();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
//Despliegue de segunda textura
TexBits = LoadDIBitmap("galleta.bmp", &TexInfo);
glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
GL_UNSIGNED_BYTE, TexBits);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//Fin despliegue segunda textura
glBegin(GL_QUADS);
glNormal3f(0.0,0.0,-1.0);
glTexCoord2f(1.0,1.0); glVertex3f(-0.5,0.5,-0.5);
glTexCoord2f(0.0,1.0); glVertex3f( 0.5,0.5,-0.5);
glTexCoord2f(0.0,0.0); glVertex3f(0.5,-0.5,-0.5);
glTexCoord2f(1.0,0.0); glVertex3f(-0.5,-0.5,-0.5);
glEnd();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
//Despliegue de tercera textura
TexBits = LoadDIBitmap("sirenoman.bmp", &TexInfo);
glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
GL_UNSIGNED_BYTE, TexBits);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//Fin despliegue tercera textura
glBegin(GL_QUADS);
glNormal3f(-1.0,0.0,0.0);
glTexCoord2f(1.0,1.0); glVertex3f(-0.5,0.5,0.5);
glTexCoord2f(0.0,1.0); glVertex3f(-0.5,0.5,-0.5);
glTexCoord2f(0.0,0.0); glVertex3f(-0.5,-0.5,-0.5);
glTexCoord2f(1.0,0.0); glVertex3f(-0.5,-0.5,0.5);
glEnd();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
//Despliegue de cuarta textura
TexBits = LoadDIBitmap("carlito.bmp", &TexInfo);
glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
GL_UNSIGNED_BYTE, TexBits);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//Fin despliegue cuarta textura
glBegin(GL_QUADS);
glNormal3f(1.0,0.0,0.0);
glTexCoord2f(0.0,1.0); glVertex3f(0.5,0.5,0.5);
glTexCoord2f(0.0,0.0); glVertex3f(0.5,-0.5,0.5);
glTexCoord2f(1.0,0.0); glVertex3f( 0.5,-0.5,-0.5);
glTexCoord2f(1.0,1.0); glVertex3f(0.5,0.5,-0.5);
glEnd();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
//Despliegue de quinta textura
TexBits = LoadDIBitmap("towelie.bmp", &TexInfo);
glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
GL_UNSIGNED_BYTE, TexBits);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//Fin despliegue quinta textura
glBegin(GL_QUADS);
glNormal3f(0.0,1.0,0.0);
glTexCoord2f(0.0,1.0); glVertex3f(-0.5,0.5,-0.5);
glTexCoord2f(0.0,0.0); glVertex3f(-0.5,0.5,0.5);
glTexCoord2f(1.0,0.0); glVertex3f(0.5,0.5,0.5);
glTexCoord2f(1.0,1.0); glVertex3f( 0.5,0.5,-0.5);
glEnd();
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
//Despliegue de sexta textura
TexBits = LoadDIBitmap("Dr_Abe.bmp", &TexInfo);
glTexImage2D(GL_TEXTURE_2D, 0, 3, TexInfo->bmiHeader.biWidth,
TexInfo->bmiHeader.biHeight, 0, GL_BGR_EXT,
GL_UNSIGNED_BYTE, TexBits);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//Fin despliegue sexta textura
glBegin(GL_QUADS);
glNormal3f(0.0,-1.0,0.0);
glTexCoord2f(0.0,0.0); glVertex3f(0.5,-0.5,-0.5);
glTexCoord2f(1.0,0.0); glVertex3f(-0.5,-0.5,-0.5);
glTexCoord2f(1.0,1.0); glVertex3f(-0.5,-0.5,0.5);
glTexCoord2f(0.0,1.0); glVertex3f(0.5,-0.5,0.5);
glEnd();
glDisable(GL_TEXTURE_2D);
glutSwapBuffers() ;
glPopMatrix();
//Fin del despliegue del cubo con imagenes

glPopMatrix ();
glFlush ();
}

void reshape (int w, int h)
{
glViewport (0, 0, (GLsizei) w, (GLsizei) h);
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

/* ARGSUSED2 */
void mouse(int button, int state, int x, int y)
{
switch (button) {
case GLUT_LEFT_BUTTON:
if (state == GLUT_DOWN) {
if (p1 == 1)
{
glDisable(GL_LIGHT0);
p1 = 0;
glutPostRedisplay();
}
else
{
glEnable(GL_LIGHT0);
p1 = 1;
glutPostRedisplay();
}
}
break;
case GLUT_RIGHT_BUTTON:
if (state == GLUT_DOWN) {
if (p1 == 1)
{
glDisable(GL_LIGHT1);
p1 = 0;
glutPostRedisplay();
}
else
{
glEnable(GL_LIGHT1);
p1 = 1;
glutPostRedisplay();
}
}
break;
default:
break;
}
}
void special(int key, int x, int y)
{
switch (key)
{
case GLUT_KEY_RIGHT:
spiny = (spiny + 3) % 360;
glutPostRedisplay();
break;
case GLUT_KEY_LEFT:
spiny = (spiny - 3) % 360;
glutPostRedisplay();
break;
case GLUT_KEY_UP:
spinx = (spinx - 3) % 360;
glutPostRedisplay();
break;
case GLUT_KEY_DOWN:
spinx = (spinx + 3) % 360;
glutPostRedisplay();
break;
default:
break;
}
}
void keyboard(unsigned char key, int x, int y)
{
switch (key) {
case 27:
exit(0);
break;
case 'a':
ry = (ry + 3)%360;
glutPostRedisplay();
break;
case 's':
rx = (rx + 3)%360;
glutPostRedisplay();
break;
case 'd':
rz = (rz + 3)%360;
glutPostRedisplay();
break;
case 'p':
spinx = 0;
spiny = 0;
rx = 0;
rz = 0;
ry = 0;
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glutPostRedisplay();
break;

}
}

int main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize (600, 600);
glutInitWindowPosition (200, 100);
glutCreateWindow ("Las flechas mueven las luces, A S y D rotan el cubo" );
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutMouseFunc(mouse);
glutKeyboardFunc(keyboard);
glutSpecialFunc(special);
glutMainLoop();
return 0;
}
