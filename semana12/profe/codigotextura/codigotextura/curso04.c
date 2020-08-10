#include <gl/glut.h>
float angulo=0.0;       // Variable para el angulo en que vamos a rotar nuestro triangulo
GLfloat luzdifusa[]=    { 1.0, 1.0, 1.0, 1.0};	// Definimos valores de luz difusa, maxima intensidad de luz blanca
GLfloat luzambiente[]=  { 0.5, 0.5, 0.5, 1.0};	// Definimos valores de luz ambiente
GLfloat luzspecular[]= { 0.0, 0.0, 0.0, 0.0};	// Definimos el valor specular de la luz
GLfloat posicion[]=     { 1.0, 1.0, 1.0, 0.0};	// La posicion de la luz

void inicializar() {
        glShadeModel(GL_SMOOTH);       // Esto hace que al dibujar las sombran en los objetos, se vean mas parejas haciendo que se vean mejor.
        glClearColor(0.0, 0.0, 0.0, 0.0);       // Pondremos aca la funcion glclearcolor
        // Las 3 lineas siguientes hacen que el depth buffer ordene los objetos que deben ser puestos primero en panatalla y los que deben ser dibujados despues dependiendo de cuan cerca estan de la camara.
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Esto hace que opengl calcule las perspectivas de la mejor forma, quita un poco de rendimiento, pero hace que las perspectivas se vean un poco mejor.
        // Ahora vamos a inicializar las luces.
        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzdifusa);	// Ponemos valores a la luz 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzambiente);	// Ponemos valores a la luz 0
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzspecular); // Ponemos valores a la luz 0
	glLightfv(GL_LIGHT0, GL_POSITION, posicion);	// Ponemos la posicion para gl_light1
	glEnable(GL_LIGHTING);				// Activamos la iluminacion.
	glEnable(GL_LIGHT0);				// Ahora ponemos la luz que ya definimos
}

void dibujar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Se borra el buffer de la pantalla
        glPushMatrix();
        glRotatef(angulo, 1.0, 0.0, 1.0);       // Efectuamos la rotacion
        glutSolidTeapot(0.2);
	glPopMatrix();
        glutSwapBuffers();
        angulo++;
}

void cambiarTamano(int largo, int ancho) {
        if(ancho==0) ancho=1;           // Previene que dividamos por 0
        glMatrixMode(GL_PROJECTION);    // Escojemos la matriz de proyeccion
        glLoadIdentity();               // Se resetea la matriz
        glViewport(0,0,largo, ancho);   // Se va a usar toda la ventana para mostrar graficos
        gluPerspective( 45 ,            // Angulo de vision
                        (float)largo/(float)ancho,
                        1.0,              // Cuan cerca se puede ver
                        1000);          // Cuan lejos se puede ver
        glMatrixMode(GL_MODELVIEW);     // Escojemos la matriz de vista
	glLoadIdentity();
        gluLookAt( 0.0, 0.0, 1.0,       // Hacia donde miramos
                   0.0, 0.0, -3.0,      // Desde donde miramos
                   0.0, 1.0, 0.0);      // Que eje es el que esta hacia arriba
}

int main(int argc, char **argv) {
        glutInit(&argc,argv);
        glutInitWindowPosition(100,100);        
        glutInitWindowSize( 320, 320);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("Animacion!!!");
        inicializar();
        glutDisplayFunc(dibujar);
        glutReshapeFunc(cambiarTamano);
        glutIdleFunc(dibujar);
        glutMainLoop();
}
