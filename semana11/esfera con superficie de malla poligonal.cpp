#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265

float traslacion_esfera = 0.0;
float rotacion_esfera = 0.0;

int modo_rotacion = 0;
int modo_traslacion = 0;

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-6.4, 6.4, -4.8, 4.8, 5.0, -5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//-5 -4 10 0
/*************/
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1, 0, 0);

    // ESFERA
    glPushMatrix();
    glScalef(5.0f, 5.0f, 5.0f);
    glRotatef(rotacion_esfera, 0, 0, 1.0);
    // glColor3f(0.0, 0.0, 1.0
    glColor3f(0.1, 1.0, 1.0);
    glutWireSphere(0.3, 20, 20);
    glPopMatrix();
    glutSwapBuffers();
}

/*************/
static void idle(void)
{
    glutPostRedisplay();
}

/*************/
static void timer(int x)
{
    if (modo_rotacion == 1)
    {

        rotacion_esfera += 5.0;
    }
    if (modo_traslacion == 1)
    {
        traslacion_esfera += 2.0;
    }
    glutTimerFunc(25, timer, 0);
}

/*************/
void ControlTeclado(unsigned char key, int x, int y)
{ // Necesario describir?
    switch (key)
    {
    case 'r': // activa o desactiva el modo de rotacion
        if (modo_rotacion == 0)
        {
            modo_rotacion = 1;
        }
        else
        {
            modo_rotacion = 0;
        }
        break;
    case 't': // activa o desactiva el modo de traslacion
        if (modo_traslacion == 0)
        {
            modo_traslacion = 1;
        }
        else
        {
            modo_traslacion = 0;
        }

        break;
    case 'n': // activa o descativa el modo de ambas funciones
        if (modo_traslacion == 0 || modo_rotacion == 0)
        {                      // si esta uno de los dos modos descativados, o bien los dos
            modo_rotacion = 1; // 'n' activa ambos modos
            modo_traslacion = 1;
        }
        else
        { // si ambos modos estan activados, 'n' desactiva ambos modos
            modo_rotacion = 0;
            modo_traslacion = 0;
        }

        break;
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}

/*************/
void ControlFlechas(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: // GLUT_KEY_UP y GLUT_KEY_DOWN para control de rotacion general vertical
        glRotatef(-1.0, 1.0, 0.0, 0.0);
        break;

    case GLUT_KEY_DOWN:
        glRotatef(1.0, 1.0, 0.0, 0.0);
        break;

    case GLUT_KEY_LEFT: // GLUT_KEY_LEFT y GLUT_KEY_RIGHT para control de rotacion general horizontal
        glRotatef(-1.0, 0.0, 1.0, 0.0);
        break;

    case GLUT_KEY_RIGHT:
        glRotatef(1.0, 0.0, 1.0, 0.0);
        break;
    }
    glutPostRedisplay();
}

/*************/
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("ESFERA CON SUPERFICIE DE MALLA POLIGONAL");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(ControlTeclado);
    glutSpecialFunc(ControlFlechas);
    glutIdleFunc(idle);
    glutTimerFunc(25, timer, 0);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return EXIT_SUCCESS;
}
// gcc -m32 -Wall -o 4.out 4.c -L"C:\MinGW\lib" -lglu32 -lglut32 -lopengl32 -lstdc++
