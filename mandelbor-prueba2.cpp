/*
* Jonathan Senning <jonathan.senning@gordon.edu>
* Gordon College
*
* Muestra el conjunto de Mandelbrot y permite al usuario seleccionar una región rectangular
* para acercar.
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <complex>
using namespace std;
const int WX = 400; // Initial window dimensions, and dimensions of image
const int WY = 400;
int wx = WX;
int wy = WY;

double width = 2.0; // Initial width and height of portion of complex plane
double height = 2.0;
double center_x = -0.5; // Initial center of portion of complex plane to view
double center_y = 0.0;
int max_iterations = 100;
// These are used for the region selection
int dx0, dx1;
int dy0, dy1;
int rubberOn = 0;
// The image buffer
GLubyte image[WX][WY];
//----------------------------------------------------------------------------
void graphicsInit( void )
{
 glClearColor(0.0, 0.0, 0.0, 1.0 );
 glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
}
//----------------------------------------------------------------------------
void installColorMap( void )
{
 float redmap[256], greenmap[256], bluemap[256];
 // Define pseudocolor maps, ramps for red and blue, zero for green
 for ( int i = 0; i < 256; i++ )
 {
 redmap[i] = i / 255.0;
 greenmap[i] = 0.0;
 bluemap[i] = 1.0 - i / 255.0;
 }
 redmap[0] = greenmap[0] = bluemap[0] = 0.0;
 glPixelMapfv( GL_PIXEL_MAP_I_TO_R, 256, redmap );
 glPixelMapfv( GL_PIXEL_MAP_I_TO_G, 256, greenmap );
 glPixelMapfv( GL_PIXEL_MAP_I_TO_B, 256, bluemap );
}
//----------------------------------------------------------------------------
void buildMandelbrotSet( double width, double height,
double center_x, double center_y,
int max_iterations )
{
 double x, y;
 complex<double> c, z;
 cout << "Center: (" << center_x << "," << center_y << "); ";
 cout << "Dimensions: (" << width << ")x(" << height << ")" << endl;
 for ( int j = 0; j < wy; j++ )
 {
y = ( j / double( wy - 1 ) - 0.5 ) * height + center_y;
for ( int i = 0; i < wx; i++ )
{
 x = ( i / double( wx - 1 ) - 0.5 ) * width + center_x;
 c = complex<double>( x, y );
 z = complex<double>( 0.0, 0.0 );
 int k;
 for ( k = 0; abs(z) < 2.0 && k < max_iterations; k++ )
 {
z = z * z + c;
 }
 if ( k < max_iterations )
 image[j][i] = (GLubyte) ( 255.0 * k / max_iterations );
 else
 image[j][i] = 0;
}
 }
}
//----------------------------------------------------------------------------
void cbReshape( int w, int h )
{
 wx = w;
 wy = h;
 glMatrixMode( GL_PROJECTION );
 glLoadIdentity();
 if ( w <= h )
 {
gluOrtho2D( 0.0, (float) wx, 0.0, (float) wy * (float) h / (float) w );
 }
 else
 {
gluOrtho2D( 0.0, (float) wx * (float) w / (float) h, 0.0, (float) wy );
 }
 glMatrixMode(GL_MODELVIEW);
 glViewport( 0, 0, w, h );
}
//----------------------------------------------------------------------------
void cbKeyboard( unsigned char key, int x, int y )
{
 switch ( key ) {
 case '+':
 case '=':
max_iterations += 50;
cout << "maximum number of iterations: " << max_iterations << endl;
buildMandelbrotSet( width, height, center_x, center_y, max_iterations );
break;
 case '-':
 case '_':
if ( max_iterations > 50 ) max_iterations -= 50;
cout << "maximum number of iterations: " << max_iterations << endl;
buildMandelbrotSet( width, height, center_x, center_y, max_iterations );
break;
 case 'q':
 case 'Q':
 case 27:
 	glutDestroyWindow( glutGetWindow() );
 exit( 0 );
break;
 }
 glutPostRedisplay();
}
//----------------------------------------------------------------------------
void cbDrawImage( void )
{
 glClear( GL_COLOR_BUFFER_BIT );
 glDrawPixels( WX, WY, GL_COLOR_INDEX, GL_UNSIGNED_BYTE, image );
 if ( rubberOn )
 {
glBegin( GL_LINE_LOOP );
glColor3f( 1.0, 1.0, 1.0 );
glVertex2i( dx0, dy0 );
glVertex2i( dx1, dy0 );
glVertex2i( dx1, dy1 );
glVertex2i( dx0, dy1 );
glEnd();
 }
 glFlush();
 glutSwapBuffers();
}
//----------------------------------------------------------------------------
void cbMouseClick( int button, int state, int x, int y )
{
 static double wx0, wy0;
 double wx1, wy1;
 if ( button == GLUT_LEFT_BUTTON )
 {
if ( state == GLUT_DOWN )
{
 rubberOn = 1;
 dx0 = x;
 dy0 = wy - 1 - y;
 wx0 = ( x / double( wx - 1 ) - 0.5 ) * width + center_x;
 wy0 = ( 0.5 - y / double( wy - 1 ) ) * height + center_y;
}
else if ( state == GLUT_UP )
{
 rubberOn = 0;
 wx1 = ( x / double( wx - 1 ) - 0.5 ) * width + center_x;
 wy1 = ( 0.5 - y / double( wy - 1 ) ) * height + center_y;
 center_x = 0.5 * ( wx0 + wx1 );
 center_y = 0.5 * ( wy0 + wy1 );
 width = ( wx0 < wx1 ? wx1 - wx0 : wx0 - wx1 );
 height = ( wy0 < wy1 ? wy1 - wy0 : wy0 - wy1 );
 buildMandelbrotSet( width, height, center_x, center_y,
 max_iterations );
 glutPostRedisplay();
}
 }
}
//----------------------------------------------------------------------------
void cbMouseMotion( int x, int y )
{
 dx1 = x;
 dy1 = wy - 1 - y;
 glutPostRedisplay();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
 glutInit( &argc, argv );
 glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
 glutInitWindowSize( wx, wy );
 glutCreateWindow( argv[0] );
 glutReshapeFunc( cbReshape );
 glutKeyboardFunc( cbKeyboard );
 glutDisplayFunc( cbDrawImage );
 glutMouseFunc( cbMouseClick );
 glutMotionFunc( cbMouseMotion );
 buildMandelbrotSet( width, height, center_x, center_y, max_iterations );
 graphicsInit();
 installColorMap();

 glutMainLoop();
 return 0;
}
/*
En la linea 42 se cambia de color pero solo pude rosado un color mas claro
redmap[i] = i / 100.0;
 greenmap[i] = 0.0;
 bluemap[i] = 1.0 - i / 255.0; 	
*/	
