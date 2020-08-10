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
                glEnd();                                // Se termina de definir los triangulos.
}

int main(int argc, char **argv) {
        glutInit(&argc,argv);
        glutInitWindowPosition(100,100);
        glutInitWindowSize( 320, 320);
        glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
        glutCreateWindow("Un triangluo!!");

        glutDisplayFunc(dibujar);
        glutMainLoop();
}
