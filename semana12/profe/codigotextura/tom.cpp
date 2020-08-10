/* 
   El siguiente codigo lee un archivo .asc exportado por el
   3D Studio MAX 3.1 y lo representa usando OpenGL. 
   
   Modulo Principal : main.cpp
*/

#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "textura.h"
#include "asc.h"
#include "objeto.h"

char *nombre_archivo_asc="cubo.asc";
char *nombre_archivo_bmp="cubo.bmp";
float yrot=0.0;
COGLTexture MyTextura;
Object3D	obj;

//esta rutina me calcula el vector normal de cada cara
//esto es necesario, tanto para la iluminacion como para
//que OpenGL determine que caras dibujar
//es algo asi como un producto vectorial, los vectores los
//formo a partir de los  vertices de cada uno de los piligonos
//el vector resultante es normal a la cara, y esta normalizado
void CalcularNormales(Object3D &object)
{
 float x1, y1, z1;
 float x2, y2, z2;
 float x3, y3, z3;
 float length;
 int   a, b, c;
 int   i;

 for (i=0; i<object.nFaces; i++)
	{
	Face& face = object.pFaces[i];
	a = face.vertexIndices[0];
	b = face.vertexIndices[1];
	c = face.vertexIndices[2];
	x1 = object.pVertices[b].x - object.pVertices[a].x;
	y1 = object.pVertices[b].y - object.pVertices[a].y;
	z1 = object.pVertices[b].z - object.pVertices[a].z;
	x2 = object.pVertices[c].x - object.pVertices[a].x;
	y2 = object.pVertices[c].y - object.pVertices[a].y;
	z2 = object.pVertices[c].z - object.pVertices[a].z;
	z3 = x1*y2 - y1*x2;
	x3 = y1*z2 - z1*y2;
	y3 = z1*x2 - x1*z2;
	length = sqrt(x3*x3 + y3*y3 + z3*z3);
	if (length == 0)
		{
		face.faceNormal.x=1;
		face.faceNormal.y=1;
		face.faceNormal.z=1;
		}
	else
		{
		face.faceNormal.x=x3/length;
		face.faceNormal.y=y3/length;
		face.faceNormal.z=z3/length;
		}
	}
}

void LiberarMemoria(Object3D &object)
{
 delete[] object.pFaces;
 object.pFaces = NULL;
 object.nFaces = 0;
 delete[] object.pVertices;
 object.pVertices = NULL;
 object.nVertices = 0;
}

//inicializo las texturas
void InitTextures(char *archivo_bmp)
{
 MyTextura.LoadFromFile(archivo_bmp);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void init(void)
{
 float LightPos[] = { 0.0f, 0.0f, 1.0f, 0.0f};  

 glClearColor(0.0, 0.0, 0.0, 0.0);

 //activo la fuente de luz
 glLightfv(GL_LIGHT0, GL_POSITION, LightPos);     
 glEnable(GL_LIGHT0);                               
 glEnable(GL_LIGHTING);
 glDepthFunc(GL_LESS);
 glEnable(GL_DEPTH_TEST);
 glPolygonMode(GL_FRONT, GL_FILL); 
 CargarObjeto(nombre_archivo_asc, obj);
 CalcularNormales(obj);
 InitTextures(nombre_archivo_bmp);
}

void display(void)
{
 int a, b, c;
 int i;
 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glEnable(GL_TEXTURE_2D);
 MyTextura.SetActive();

 glPushMatrix();
 gluLookAt(0.0, 75.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 glRotatef(yrot, 0.0, 1.0, 0.0);
 glBegin(GL_TRIANGLES);
 for (i=0; i<obj.nFaces; i++)
	{
	const Face& face = obj.pFaces[i];
	a=face.vertexIndices[0];
	b=face.vertexIndices[1];
	c=face.vertexIndices[2];
	glNormal3f(face.faceNormal.x, face.faceNormal.y, face.faceNormal.z); 
	glTexCoord2f(obj.pVertices[a].u, obj.pVertices[a].v);
	glVertex3f(obj.pVertices[a].x, obj.pVertices[a].y, obj.pVertices[a].z);
    glTexCoord2f(obj.pVertices[b].u, obj.pVertices[b].v);
	glVertex3f(obj.pVertices[b].x, obj.pVertices[b].y, obj.pVertices[b].z);
    glTexCoord2f(obj.pVertices[c].u, obj.pVertices[c].v);
	glVertex3f(obj.pVertices[c].x, obj.pVertices[c].y, obj.pVertices[c].z);
	}
 glEnd();
 glPopMatrix();
 glutSwapBuffers();
}

void reshape(int w, int h)
{
 if (!h)
	return;
 glViewport(0, 0,  (GLsizei) w, (GLsizei) h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
 switch (key)
   {
   case 27: exit(0);
             break;
   }
}

void idle(void)
{
 yrot=yrot+0.5;
 glutPostRedisplay();
}

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitWindowSize(400, 400);
 glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
 glutCreateWindow("Carga de un archivo .asc");
 init();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutIdleFunc(idle);
 glutMainLoop();
 LiberarMemoria(obj);
 return 0;
}
