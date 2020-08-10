#include <gl/glut.h>

void dibujar() {
        glClear(GL_COLOR_BUFFER_BIT);   // Se borra el buffer de la pantalla
                glBegin(GL_TRIANGLES);  // Se va a empezar una secuencia de triangulos.
                      glColor3f(1.0, 0.0, 0.0);
                      glVertex3f(-0.5, -0.5, 0.0);    // glVertex3f se usa para definir puntos con 3 coordenadas que sean flota, glvertex3d para 3 coordenadas que sean double.
                      glColor3f(0.0, 1.0, 0.0);
                      glVertex3f(0.5, 0.0, 0.0);
                      glColor3f(0.0, 0.0, 1.0);
                      glVertex3f(-0.5, 0.5, 0.0);
                glEnd();
}

void cambiarTamano(int largo, int ancho) {
        if(ancho==0) ancho=1;           // Previene que dividamos por 0
        glMatrixMode(GL_PROJECTION);    // Escojemos la matriz de proyeccion
        glLoadIdentity();               // Se resetea la matriz
        glViewport(0,0,largo, ancho);   // Se va a usar toda la ventana para mostrar graficos
        gluPerspective( 45 ,            // Angulo de vision
                        (float)largo/(float)ancho,
                        1,              // Cuan cerca se puede ver
                        1000);          // Cuan lejos se puede ver
        glMatrixMode(GL_MODELVIEW);     // Escojemos la matriz de vista
	glLoadIdentity();
        gluLookAt( 0.0, 0.0, 2.0,       // Hacia donde miramos
                   0.0, 0.0, -1.0,      // Desde donde miramos
                   0.0, 1.0, 0.0);      // Que eje es el que esta hacia arriba
}

int main(int argc, char **argv) {
        glutInit(&argc,argv);
        glutInitWindowPosition(100,100);        
        glutInitWindowSize( 320, 320);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
        glutCreateWindow("Un triangluo!!");
        glutDisplayFunc(dibujar);
        glutReshapeFunc(cambiarTamano);
        glutMainLoop();
}
