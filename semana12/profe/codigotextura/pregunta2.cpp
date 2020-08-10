#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265
#define TWOPI 6.2831853
#define PID 1.5707963

/* Vector que contiene a las texturas utilizadas */
int texturas[100];


/* Alto y ancho de la ventana, principalmente utilizado para el reajuste tras 
*  maximizar
*/
int altoPantalla = 640;
int anchoPantalla = 480;

/*
 * FUNCTION LoadBitmap(char *)
 *
 * La carga de la textura se realiza por medio de esta función 
 *
 */
 
int LoadBitmap(char *filename) 
{
    

    int i, j=0; //Index variables
    FILE *l_file; //File pointer
    unsigned char *l_texture; //The pointer to the memory zone in which we will load the texture
     
    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    int num_texture=-1;
    num_texture++; // The counter of the current texture is increased

    if( (l_file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading
    
    fread(&fileheader, sizeof(fileheader), 1, l_file); // Read the fileheader
    
    fseek(l_file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, l_file); // and read the infoheader

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // At this point we can read every pixel of the image
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {            
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, l_file); 

            // And store it
            l_texture[j+0] = rgb.rgbtRed; // Red component
            l_texture[j+1] = rgb.rgbtGreen; // Green component
            l_texture[j+2] = rgb.rgbtBlue; // Blue component
            l_texture[j+3] = 255; // Alpha value
            j += 4; // Go to the next position
    }

    fclose(l_file); // Closes the file stream
     
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}


void DibujarCuadrado() {
   glBegin(GL_QUADS);
   glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 5.0, 0.0);
   glTexCoord2f(1.0, 1.0); glVertex3f(5.0, 5.0, 0.0);
   glTexCoord2f(1.0, 0.0); glVertex3f(5.0, 0.0, 0.0);
   glEnd();
}

void  init(void){
      
         
    /* Situamos el fondo de pantalla en azul oscuro*/  
    glClearColor(0.0, 0.0, 0.2, 0.0);
       	
    /* Activamos el Texture mapping */
    glEnable(GL_TEXTURE_2D);

    /* La funcion de carga de bmp nos devolverá el identificador de la textura
    * correspondiente
    */
    texturas[0]=LoadBitmap("fotoTapa.bmp");
}

void resize (int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0f, (GLfloat)w/(GLfloat)h, 1.0f, 20.0f);
}

void keyboard (unsigned char key, int x, int y){      
    switch (key)
    {
        case 27:
             exit(0);
    }
}



void  display(void){
    
    /* Situamos el fondo de pantalla en azul oscuro, por decorar un poco */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* Cargamos la matriz de modelado */
    glMatrixMode(GL_MODELVIEW);
    /* Inicializamos la matriz */
    glLoadIdentity();
    gluLookAt (0.0, 0.0,10., 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    /* Se establece el texture mapping en lo relativo a sus características y ambiente */
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    
       
    //CUADRADO
    glBindTexture(GL_TEXTURE_2D, texturas[0]); // Textura a emplear
    DibujarCuadrado(); 
      
    glFlush();
    glutSwapBuffers();
}



int main(int argc, char **argv){
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(altoPantalla, anchoPantalla);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("Textura");    
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
        
    init();
    glutMainLoop();

    return(0);    
}
