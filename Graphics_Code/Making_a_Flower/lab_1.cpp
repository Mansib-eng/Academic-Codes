#include <GL/gl.h>
#include <GL/glut.h>



void printAnything(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    y=r;
    double d=3-2*r;
    while(x<=y){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*x+6;
        }
        else {
            d=d+4*(x-y)+10;
            y=y-1;
        }
        x=x+ 1;
    }
}

void printAnything2(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    x=r;
    double d=3-2*r;
    while(x>=y){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*y+6;
        }
        else {
            d=d+4*(y-x)+10;
            x=x-1;
        }
        y=y+1;
    }
}

void printAnything3(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    x=r;
    double d=3-2*r;
    while(x>=abs(y)){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*y*-1.0+6;
        }
        else {
            d=d+4*(y*-1.0-x)+10;
            x=x-1;
        }
        y=y-1;
    }
}

void printAnything4(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    y=-1.0*r;
    double d=3-2*r;
    while(x<=(y*-1.0)){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*x+6;
        }
        else {
            d=d+4*(x-y*-1.0)+10;
            y=y+1;
        }
        x=x+1;
    }
}

void printAnything5(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    y=-1.0*r;
    double d=3-2*r;
    while(x*-1.0<=(y*-1.0)){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*x*-1+6;
        }
        else {
            d=d+4*((x*-1)-y*-1.0)+10;
            y=y+1;
        }
        x=x-1;
    }
}

void printAnything6(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    x=-1*r;
    double d=3-2*r;
    while(abs(x)>=abs(y)){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*y*-1.0+6;
        }
        else {
            d=d+4*(y*-1.0-x*-1)+10;
            x=x+1;
        }
        y=y-1;
    }
}

void printAnything7(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    x=-1.0*r;
    double d=3-2*r;
    while(abs(x)>=y){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*y+6;
        }
        else {
            d=d+4*(y-x*-1.0)+10;
            x=x+1;
        }
        y=y+1;
    }
}

void printAnything8(double h, double k, double x, double y, double r){
//    double x=0.0,r=5.0;
    y=r;
    double d=3-2*r;
    while(abs(x)<=y){
        glVertex3f(h+x,k+y,0.0);
        if(d<0){
            d=d+4*x*-1.0+6;
        }
        else {
            d=d+4*(x*-1.0-y)+10;
            y=y-1;
        }
        x=x-1;
    }
}

void printCircle1(double h, double k){
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything2(h, k, 5.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything3(h, k, 0.0, 0.0, 7.0);

    glEnd();

//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything4(h, k, 0.0, 0.0, 7.0);
//
//    glEnd();
//
//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything5(h, k, 0.0, 0.0, 7.0);

//    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything6(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything7(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything8(h, k, 0.0, 0.0, 7.0);

    glEnd();
}

void printCircle2(double h, double k){
//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything(h, k, 0.0, 0.0, 7.0);
//
//    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything2(h, k, 5.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything3(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything4(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything5(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything6(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything7(h, k, 0.0, 0.0, 7.0);

    glEnd();

//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything8(h, k, 0.0, 0.0, 7.0);
//
//    glEnd();
}

void printCircle3(double h, double k){
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything(h, k, 0.0, 0.0, 7.0);

    glEnd();

//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything2(h, k, 5.0, 0.0, 7.0);
//
//    glEnd();

//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything3(h, k, 0.0, 0.0, 7.0);
//
//    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything4(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything5(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything6(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything7(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything8(h, k, 0.0, 0.0, 7.0);

    glEnd();
}

void printCircle4(double h, double k){
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything2(h, k, 5.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything3(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything4(h, k, 0.0, 0.0, 7.0);

    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything5(h, k, 0.0, 0.0, 7.0);

    glEnd();

//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything6(h, k, 0.0, 0.0, 7.0);
//
//    glEnd();
//
//    glBegin(GL_POINTS);
//    glColor3f(0.0,1.0,0.0);
//    printAnything7(h, k, 0.0, 0.0, 7.0);
//
//    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,0.0);
    printAnything8(h, k, 0.0, 0.0, 7.0);

    glEnd();
}

void display(void)
{
/* clear all pixels */
    glClear (GL_COLOR_BUFFER_BIT);
/* draw white polygon (rectangle) with corners at
* (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)
*/
    glColor3f (1.0, 1.0, 1.0);



//
//        glBegin(GL_TRIANGLES); //Begin quadrilateral coordinates
//
//
//        //Trapezoid
//        glVertex3f(0.05f, 0.05f, 0.0f);
//        glVertex3f(0.35f, 0.05f, 0.0f);
//        glVertex3f(0.40f, 0.35f, 0.0f);
//
//
//
//
//        glEnd(); //End quadrilateral coordinates
//
//
//        glBegin(GL_TRIANGLES); //Begin triangle coordinates
//
//
//        //Pentagon
//        glColor3f (0.0, 1.0, 0.0);
//        glVertex3f(0.5f, 0.05f, 0.0f);
//        glVertex3f(0.75f, 0.05f, 0.0f);
//        glVertex3f(0.5f, 0.35f, 0.0f);
//
//
//
//
//        /*glVertex3f(0.5f, 0.35f, 0.0f);
//        glVertex3f(0.75f, 0.05f, 0.0f);
//        glVertex3f(0.75f, 0.35f, 0.0f);*/
//    glColor3f (0.0, 0.0, 1.0);
//        glVertex3f(0.5f, 0.35f, 0.0f);
//        glVertex3f(0.75f, 0.35f, 0.0f);
//        glVertex3f(0.63f, 0.50f, 0.0f);
//
//
//        //Triangle
//        /*glVertex3f(0.30f, 0.65f, 0.0f);
//        glVertex3f(0.60f, 0.65f, 0.0f);
//        glVertex3f(0.45, 0.85f, 0.0f);*/
//
//
//        glEnd();//End triangle




        printCircle1(0.0, 10.0);
        printCircle2(0.0, -10.0);
        printCircle3(-10.0, 0.0);
        printCircle4(10.0, 0.0);

/* don't wait!
* start processing buffered OpenGL routines
*/
glFlush ();
}
void init (void)
{
/* select clearing (background) color */
    glClearColor (0.0, 0.0, 0.0, 0.0);
    /* initialize viewing values */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -10.0, 10.0);
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
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
