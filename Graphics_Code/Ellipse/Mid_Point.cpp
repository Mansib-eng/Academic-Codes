/**
There is a  Center(0,0) and a= 10, b = 6
There are 4 points => (x,y) , (-x,y), (-x,-y), (x,-y)
*/


#include <GL/freeglut.h>
void display(void)
{
/* clear all pixels */
    glClear (GL_COLOR_BUFFER_BIT);
/* draw white polygon (rectangle) with corners at
* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
*/
    glColor3f (0.75, 0.75, 0.0);




        glBegin(GL_TRIANGLES); //Begin quadrilateral coordinates


        //Trapezoid
        glVertex3f(0.9f, 0.7f, 0.0f);
        glVertex3f(0.40f, 0.30f, 0.0f);
        glVertex3f(0.50f, 0.35f, 0.0f);




        glEnd(); //End quadrilateral coordinates


        glBegin(GL_TRIANGLES); //Begin triangle coordinates


        //Pentagon
        glColor3f (0.0, 1.0, 0.0);
        glVertex3f(0.1f, 0.1f, 0.0f);
        glVertex3f(0.5f, 0.25f, 0.0f);
        glVertex3f(0.3f, 0.35f, 0.0f);


        /*glVertex3f(0.5f, 0.35f, 0.0f);
        glVertex3f(0.75f, 0.05f, 0.0f);
        glVertex3f(0.75f, 0.35f, 0.0f);*/
    glColor3f (0.0, 0.0, 1.0);
        glVertex3f(0.2f, 0.7f, 0.0f);
        glVertex3f(0.5f, 0.35f, 0.0f);
        glVertex3f(0.6f, 0.50f, 0.0f);


        //Triangle
        /*glVertex3f(0.30f, 0.65f, 0.0f);
        glVertex3f(0.60f, 0.65f, 0.0f);
        glVertex3f(0.45, 0.85f, 0.0f);*/


        glEnd();//End triangle coordinates
/* don't wait!
* start processing buffered OpenGL routines
*/
glFlush ();
}

void plotCirclePoints(int x, int y) {
    glVertex2i( x,  y);
    glVertex2i(-x,  y);
    glVertex2i(-x, -y);
    glVertex2i( x, -y);
}

void midpoint(int a, int b) {
    int x,y,aa,bb,aa2,bb2,fx,fy,p ;
    x = 0 ;
    y = b ;
    aa = a*a ;
    bb = b*b ;
    aa2 = aa*2 ;
    bb2 = bb*2 ;
    fx = 0 ;
    fy = aa2*b ;
    p = bb-aa*b+0.25*aa ;
    while(fx<fy)
    {
        plotCirclePoints(x,y);
        x++ ;
        fx = fx+bb2 ;
        if(p<0)
        {
            p = p+fx+bb ;
        }
        else
        {
            y-- ;
            fy = fy - aa2 ;
            p = p+fx+bb-fy ;
        }
    }
    plotCirclePoints(x,y) ;
    p = bb*(x+0.5)*(x+0.5) + aa*(y-1)*(y-1) - aa*bb ;
    while(y>0)
    {
        y-- ;
        fy = fy-aa2 ;
        if(p>=0)
        {
            p = p-fy+aa ;
        }
        else
        {
            x++ ;
            fx = fx+bb2 ;
            p = p+fx-fy+aa ;
        }
        plotCirclePoints(x,y) ;
    }
}



void circle ()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPointSize(1.0f);
    glBegin(GL_POINTS);
    midpoint(10,6) ;

    glEnd();
    glFlush ();

}

void init (void)
{
/* select clearing (background) color */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);   // 1 unit = 1 pixel
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
}
/*
* Declare initial window size, position, and display mode
* (single buffer and RGBA). Open window with "hello"
* in its title bar. Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Demo");
    init ();
    //glutDisplayFunc(display);
    glutDisplayFunc(circle);
    glutMainLoop();
    return 0;
}
