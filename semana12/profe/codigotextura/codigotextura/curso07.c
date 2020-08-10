#include <gl/glut.h>
#include <stdio.h>

float angulo=0.0;       // Variable para el angulo en que vamos a rotar nuestro triangulo

typedef struct {
        GLubyte  *dibujo;        // Un puntero a los datos de la imagen
	GLuint	bpp;		// bpp significa bits per pixel (bits por punto) es la calidad en palabras sensillas
	GLuint largo;		// Largo de la textura
	GLuint ancho;		// Ancho de la textura
	GLuint ID;		// ID de la textura, es como su nombre para opengl
}textura;

textura	texturas[1];		// Definimos nuestras texturas, por ahora solo 1

int cargarTGA( char *nombre, textura *imagen) {
	GLubyte		cabezeraTGA[12]={0,0,2,0,0,0,0,0,0,0,0,0};		// Cabezera de un tga sin compresion
        GLubyte         compararTGA[12];                                        // Aca vamos a comprar la cabezera
	GLubyte		cabezera[6];						// Los 6 bytes importantes
	GLuint		bytesporpunto;						// Cuantos bytes hay por punto
	GLuint		tamanoimagen;						// Aca guardaremos el tamaño de la imagen
	GLuint		temp,i;							// Variable temporal, y una para usar con el for
	GLuint		tipo=GL_RGBA;						// Nuestro typo por defecto, lo veremos mas abajo

	FILE *archivo=fopen(nombre, "rb");	// Cargamos nuestro archivo en memoria
	if( archivo == NULL ||			// Existe nuestro archivo??
            fread(compararTGA,1,sizeof(compararTGA),archivo)!=sizeof(compararTGA)  ||      // Hay 12 bytes para leer??
	    memcmp(cabezeraTGA,compararTGA,sizeof(compararTGA))!=0		||	// Son iguales??
	    fread(cabezera,1,sizeof(cabezera),archivo)!=sizeof(cabezera)) {
		if(archivo==NULL) {
			printf("No se encontro el archivo %s\n",nombre);
			return 0;		// No se abrio el archivo
		}
		else {
			fclose(archivo);
			return 0;
		}
	}
	/* Ahora hay que leer la cabezera del archivo, para saber cuanto es el largo, ancho, y los bytes por puntos,
	para eso aca hay una ilustracion de la cabezera :
	6 bytes -> xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx xxxxxxx	
		   |--- Largo ---| |---Ancho-----| |-bpp-|
	El dato del largo se guarda en el cabezera[0] y cabezera[1], para leerlo hay que multiplicar cabezera[0] por 256 y 	sumarselo a cabezera[1], para leer ancho y bpp es el mismo procedimiento */
	imagen->largo=256*cabezera[1]+ cabezera[0];
	imagen->ancho=256*cabezera[3]+ cabezera[2];

	/* Ahora vemos si hay datos no validos, como largo o ancho iguales menores a 0 o iguales a 0 */
	if( imagen->largo <= 0 ||	// Largo mayor que 0?? 
	    imagen->ancho <= 0 ||	// Ancho mayor que 0??
	    (cabezera[4]!=24 && cabezera[4]!=32)) {	// bpp es 24 o 32?? (solo se cargan 24 y 32 bpp)
                printf("Daton invalidos\n");
		fclose(archivo);
		return 0;
	}
	imagen->bpp=cabezera[4];	// Aca se guardan los bits por punto
	bytesporpunto=cabezera[4]/8;	// Aca los bytes por punto (1 byte = 8 bits)
        tamanoimagen=imagen->largo * imagen->ancho * bytesporpunto;      // Esta es la memoria que nesecitaremos para guardar los datos de la textura
	/*Ahora reservamos espacio en memoria para nuestra textura, luego leemos la textura del archivo */
	imagen->dibujo = (GLubyte *)malloc(tamanoimagen);	// Reservamos la memoria necesaria para nuestra textura
	if(imagen->dibujo== NULL ||		// Se logro reservar la memoria???
	   fread(imagen->dibujo, 1, tamanoimagen, archivo) != tamanoimagen ) {	// Se lee, y se comprueba que lo leido es de la misma longitud que la asignada a a dibujo.
		if(imagen->dibujo != NULL) {
			printf("Error leyendo imagen\n");
			free(imagen->dibujo);
		} else printf("Error asignando memoria\n");
		fclose(archivo);
		return 0;
	}
	/* El formato tga guarda las imagenes en BGR, y opengl usa RGB,por lo cambiamos de lugares */
        for(i=0; i< (int)tamanoimagen; i+=bytesporpunto)
	{
		temp=imagen->dibujo[i];				// Guardamos el primer valor
		imagen->dibujo[i] = imagen->dibujo[i + 2];	// Asignamos el nuevo primer valor
		imagen->dibujo[i + 2] = temp;			// Asignamos el ultimo valor
	}
	
	fclose (archivo);	// Cerramos el archivo
	
	/* Listo, terminamos con el codigo de carga, volvemos a opengl, ahora hay que asignarle a la textura un ID, luego 	decirle a opengl cuales son el largo, el ancho y los bpp */

        glGenTextures( 1 , &imagen[0].ID);    // Crea un ID para la textura, buscando un id que este vacio
        glBindTexture(GL_TEXTURE_2D, imagen[0].ID);       // Seleccionamos nuestra textura
	if(imagen->bpp ==24) tipo= GL_RGB;	// Si nuestra textura es de 24 bits, entonces se crea una textura rgb, sino una rgba
	/* Ahora creamos nuestra textura, entrando el largo, ancho y tipo */
        glTexImage2D(GL_TEXTURE_2D, 0, tipo, imagen[0].ancho, imagen[0].largo, 0, tipo, GL_UNSIGNED_BYTE, imagen[0].dibujo);
	/* Ahora le decimos a opengl como queremos que se vea nuestra textura, MAG_FILTER es cuando la textura es mas grande que el lugar donde la asignamos, y MIG_FILTER, es cuando la textura es mas pequeña que el lugar donde la asignamos, GL_LINEAR es para que se vea bien tanto cerca como lejos, pero ocupa bastante procesador. Otra opcion el GL_NEARES, que ocupa menos prosesador */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return 1;	// Todo salio bien
}

void inicializar() {
        glShadeModel(GL_SMOOTH);       // Esto hace que al dibujar las sombran en los objetos, se vean mas parejas haciendo que se vean mejor.
        glClearColor(0.0, 0.0, 0.0, 0.0);       // Pondremos aca la funcion glclearcolor
        // Las 3 lineas siguientes hacen que el depth buffer ordene los objetos que deben ser puestos primero en panatalla y los que deben ser dibujados despues dependiendo de cuan cerca estan de la camara.
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Esto hace que opengl calcule las perspectivas de la mejor forma, quita un poco de rendimiento, pero hace que las perspectivas se vean un poco mejor.
	glEnable(GL_TEXTURE_2D);
        if(!cargarTGA("textura.tga", &texturas[0])) { 
                printf("Error cargando textura\n");
		exit(); // Cargamos la textura y chequeamos por errores
	}
}

void dibujar () {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Se borra el buffer de la pantalla y el de profundidad
	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.0, -3.0);
	glRotatef(angulo, 0.0, 1.0, 1.0);	// Rotamos nuestro objeto
        glBindTexture(GL_TEXTURE_2D,texturas[0].ID);
	// Vamos a usar un cubo
	glBegin(GL_QUADS);
	/* La textura es una imagen cuadrada, ahora hay que asignarle los lugares donde va, para eso esta glTexCoord2f(float x, float y) donde x e y son las coordenadas de la textura que van a coincidir con el punto que vamos a definir */	
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5,  0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, -0.5,  0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f( 0.5,  0.5,  0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5,  0.5);

		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5,  0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f( 0.5,  0.5, -0.5);
		glTexCoord2f(0.0, 0.0); glVertex3f( 0.5, -0.5, -0.5);

		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5, -0.5);
		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5,  0.5,  0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f( 0.5,  0.5,  0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f( 0.5,  0.5, -0.5);

		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f( 0.5, -0.5, -0.5);
		glTexCoord2f(0.0, 0.0); glVertex3f( 0.5, -0.5,  0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5,  0.5);

		glTexCoord2f(1.0, 0.0); glVertex3f( 0.5, -0.5, -0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f( 0.5,  0.5, -0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f( 0.5,  0.5,  0.5);
		glTexCoord2f(0.0, 0.0); glVertex3f( 0.5, -0.5,  0.5);

		glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, -0.5);
		glTexCoord2f(1.0, 0.0); glVertex3f(-0.5, -0.5,  0.5);
		glTexCoord2f(1.0, 1.0); glVertex3f(-0.5,  0.5,  0.5);
		glTexCoord2f(0.0, 1.0); glVertex3f(-0.5,  0.5, -0.5);
	glEnd();
	angulo++;
	glLoadIdentity();
	glPopMatrix();
	glutSwapBuffers();
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
	glLoadIdentity();		// Se resetea la matriz
        gluLookAt( 0.0, 0.0, 0.0,       // Hacia donde miramos
                   0.0, 0.0, -3.0,      // Desde donde miramos
                   0.0, 1.0, 0.0);      // Que eje es el que esta hacia arriba
}

int main(int argc, char **argv) {
        glutInit(&argc,argv);
        glutInitWindowPosition(100,100);        
        glutInitWindowSize( 320, 320);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutCreateWindow("Un cubo con textura");
        inicializar();
        glutDisplayFunc(dibujar);
        glutIdleFunc(dibujar);
        glutReshapeFunc(cambiarTamano);
        glutMainLoop();
}
