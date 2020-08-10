/* texture3D.cpp
Rotación de un Cubo, con la aplicación de Textura
Autor : Ramiro Alcocer
WWW : www.geocities.com/valcoey/index.html
Email : valcoey@hotmail.com
*/
#include <GL/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux>
#include <stdio.h>
//angulos de rotacion
GLfloatxrot=0.0;
GLfloatyrot=0.0;
GLfloatzrot=0.0;
GLuint texture[1];
// unsigned
//parametros de la fuente de luz
GLfloatLightAmbient[]={ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloatLightDiffuse[]={ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloatLightPosition[]={ 1.0f, 1.0f, 1.0f, 0.0f };
AUX_RGBImageRec *LoadBMP(char *Filename) // Loads A Bitmap Image
{
FILE *File=NULL; // File Handle
if (!Filename) // Make Sure A Filename Was Given
{
return NULL; // If Not Return NULL
}
File=fopen(Filename,"r"); // Check To See If The File Exists
if (File) // Does The File Exist?
{
fclose(File); // Close The Handle
return auxDIBImageLoad(Filename); // Load The Bitmap And Return A Pointer
}
return NULL; // If Load Failed Return NULL
}
intLoadGLTextures() // Load Bitmaps And Convert To Textures
{
int Status=FALSE; // Status Indicator
AUX_RGBImageRec *TextureImage[1]; // Create Storage Space For The Texture
memset(TextureImage,0,sizeof(void *)*1); // Set The Pointer To NULL
// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
if (TextureImage[0]=LoadBMP("foto.bmp"))
{
Status=TRUE; // Set The Status To TRUE
glGenTextures(1, &texture[0]); // Create The Texture
// Typical Texture Generation Using Data From The Bitmap
glBindTexture(GL_TEXTURE_2D, texture[0]);
glTexImage2D(GL_TEXTURE_2D, 0, 3,
TextureImage[0]->sizeX,
TextureImage[0]->sizeY,
0, GL_RGB, GL_UNSIGNED_BYTE,
TextureImage[0]->data);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
if (TextureImage[0]) // If Texture Exists
{
if (TextureImage[0]->data) // If Texture Image Exists
{
free(TextureImage[0]->data); // Free The Texture Image Memory
}
free(TextureImage[0]); // Free The Image Structure
}
return Status; // Return The Status
}
voidinit(void)
{
	//Carga la textura
LoadGLTextures();
glEnable(GL_TEXTURE_2D);
glShadeModel(GL_SMOOTH);
glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
glClearDepth(1.0f);
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LEQUAL);
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
//posicion de la fuente de luz
glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
//activa la luz
glEnable(GL_LIGHT1);
}
void display(void)
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();
glTranslatef(0.0f,0.0f,-4.5f);
//Rota el cubo
glRotatef(xrot,1.0f,0.0f,0.0f);
glRotatef(yrot,0.0f,1.0f,0.0f);
glRotatef(zrot,0.0f,0.0f,1.0f);
glBindTexture(GL_TEXTURE_2D, texture[0]);
glBegin(GL_QUADS);
// Frente
glNormal3f( 0.0f, 0.0f, 1.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
// parte de Atras
glNormal3f( 0.0f, 0.0f,-1.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
// Arriba
glNormal3f( 0.0f, 1.0f, 0.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
// Abajo
glNormal3f( 0.0f,-1.0f, 0.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
// lado Derecho
glNormal3f( 1.0f, 0.0f, 0.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
// Lado Izquierdo
glNormal3f(-1.0f, 0.0f, 0.0f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
glEnd();
glFlush ();
glutSwapBuffers();
}
void reshape (int width, int height)
{
if (height==0)
{
height=1;
}
glViewport(0,0,width,height);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
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
//Incremento los angulos de rotacion
void Idle(void)
{
xrot+=1.0f;
yrot+=1.0f;
zrot+=0.0f;
display();
}
int main(intargc, char** argv)
{
//Inicializar el estado de GLUT
glutInit(&argc, argv);
//Seleccionar el tipo de modo de display Buffer doble y color RGBA
glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//Poner el tamaño y posición de la ventana
glutInitWindowSize (300, 300);
glutInitWindowPosition (0, 0);
glutCreateWindow ("Textura 3D");
init ();
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
glutIdleFunc(Idle);
glutMainLoop();
return 0;
}
