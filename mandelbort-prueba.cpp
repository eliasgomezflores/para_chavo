#include <GL/glut.h>

#include <complex>
using std::complex;

// Render the Mandelbrot set into the image array.
// The parameters specify the region on the complex plane to plot.
void compute_mandelbrot( double left, double right, double top, double bottom )
{
    // The number of times to iterate before we assume that a point isn't in the
    // Mandelbrot set.
    // (You may need to turn this up if you zoom further into the set.)
    const int MAX_ITERATIONS = 500;

    const int width = glutGet( GLUT_WINDOW_WIDTH );
    const int height = glutGet( GLUT_WINDOW_HEIGHT );

    glBegin( GL_POINTS ); // start drawing in single pixel mode
    for( int y = 0; y < height; ++y )
    {
        for( int x = 0; x < width; ++x )
        {
            // Work out the point in the complex plane that
            // corresponds to this pixel in the output image.
            complex<double> c( left + ( x * ( right - left ) / width ),
                top + ( y * ( bottom - top ) / height ) );

            // Start off z at (0, 0).
            complex<double> z( 0.0, 0.0 );

            // Iterate z = z^2 + c until z moves more than 2 units
            // away from (0, 0), or we've iterated too many times.
            int iterations = 0;
            while( abs( z ) < 2.0 && iterations < MAX_ITERATIONS )
            {
                z = ( z * z ) + c;

                ++iterations;
            }

            if( iterations == MAX_ITERATIONS )
            {
                glColor3f( 1.0, 0.0, 0.0 ); // Set color to draw mandelbrot
                // z didn't escape from the circle.
                // This point is in the Mandelbrot set.
                glVertex2i( x, y );
            }
            else
            {
                glColor3f( 0.0, 0.0, 0.0 ); //Set pixel to black
                // z escaped within less than MAX_ITERATIONS
                // iterations. This point isn't in the set.
                glVertex2i( x, y );
            }
        }
    }
    glEnd();
}

void display()
{
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    const int width = glutGet( GLUT_WINDOW_WIDTH );
    const int height = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, width, 0, height, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    compute_mandelbrot( -2.0, 1.0, 1.125, -1.125 );
    glutSwapBuffers();
}

int main( int argc, char** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA );
    glutInitWindowSize( 300, 300 );
    glutCreateWindow( "Mandelbrot" );
    glutDisplayFunc( display );
    glutMainLoop();
    return 0;
}
