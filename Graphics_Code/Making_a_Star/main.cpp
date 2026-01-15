/*
There is 5 points -> (0,5), (-3,3) , (3,3) , (-3,0) and (3,0)
With those points make a Star
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

void line ()
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPointSize(2.0f);
    glBegin(GL_POINTS);

    /*glVertex2f(-3, 3);
    glVertex2f(3, 3);
    glVertex2f(0, 5);
    glVertex2f(-3, 0);
    glVertex2f(3, 0);*/

    float x1,y1,x2,y2,d,dx,dy,x,y,dT,dS,t ;
    //int x1,y1,x2,y2,d,dx,dy,x,y,dT,dS,t ;
    bool steep, flip ;

    x1 = -3, y1 = 3 , x2 = 3, y2 = 3 ;

    steep = false ;
    flip = false ;

    dx = x2-x1 ;
    dy = y2-y1 ;

    if(abs(dy)>abs(dx))
    {
        t = x1;
        x1 = y1 ;
        y1 = t ;
        t = x2 ;
        x2 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
        flip = true ;

    }

    if(x1>x2)
    {
        t = x1;
        x1 = x2 ;
        x2 = t ;
        t = y1 ;
        y1 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
    }

    if(dy<0)
    {
        y1 = -y1 ;
        y2 = -y2 ;
        dy = y2-y1 ;
        steep = true ;
    }

    x = x1;
    y = y1 ;
    dT = 2*(dy-dx) ;
    dS = 2*dy ;
    d = 2*dy-dx ;

    //glVertex2i(x,y);

    while(x <= x2)
    {
        //int px,py ;
        float px,py ;
        px = x ;
        py = y ;
        if(steep == true)
        {
            py = -py ;
        }
        if(flip == true)
        {
            t = px ;
            px = py ;
            py = t ;
        }

        //glVertex2i(px,py);
        glVertex2f(px,py);

        x+=0.01 ;
        //x++ ;

        if(d<0)
        {
            d = d+dS ;
        }
        else
        {
            y+=0.01 ;
            //y++ ;
            d = d+dT ;
        }

    }

    glPointSize(2.0f);
    //glBegin(GL_POINTS);

    x1 = -3, y1 = 3 , x2 = 3, y2 = 0 ;

    steep = false ;
    flip = false ;

    dx = x2-x1 ;
    dy = y2-y1 ;

    if(abs(dy)>abs(dx))
    {
        t = x1;
        x1 = y1 ;
        y1 = t ;
        t = x2 ;
        x2 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
        flip = true ;

    }

    if(x1>x2)
    {
        t = x1;
        x1 = x2 ;
        x2 = t ;
        t = y1 ;
        y1 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
    }

    if(dy<0)
    {
        y1 = -y1 ;
        y2 = -y2 ;
        dy = y2-y1 ;
        steep = true ;
    }

    x = x1;
    y = y1 ;
    dT = 2*(dy-dx) ;
    dS = 2*dy ;
    d = 2*dy-dx ;

    //glVertex2i(x,y);

    while(x <= x2)
    {
        float px,py ;
        px = x ;
        py = y ;
        if(steep == true)
        {
            py = -py ;
        }
        if(flip == true)
        {
            t = px ;
            px = py ;
            py = t ;
        }

        glVertex2f(px,py);

        x+=0.01 ;
        //x++ ;

        if(d<0)
        {
            d = d+dS ;
        }
        else
        {
            y+=0.01 ;
            //y++ ;
            d = d+dT ;
        }

    }

    glPointSize(2.0f);
    //glBegin(GL_POINTS);

    x1 = 0, y1 = 5 , x2 = 3, y2 = 0 ;

    steep = false ;
    flip = false ;

    dx = x2-x1 ;
    dy = y2-y1 ;

    if(abs(dy)>abs(dx))
    {
        t = x1;
        x1 = y1 ;
        y1 = t ;
        t = x2 ;
        x2 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
        flip = true ;

    }

    if(x1>x2)
    {
        t = x1;
        x1 = x2 ;
        x2 = t ;
        t = y1 ;
        y1 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
    }

    if(dy<0)
    {
        y1 = -y1 ;
        y2 = -y2 ;
        dy = y2-y1 ;
        steep = true ;
    }

    x = x1;
    y = y1 ;
    dT = 2*(dy-dx) ;
    dS = 2*dy ;
    d = 2*dy-dx ;

    //glVertex2i(x,y);

    while(x <= x2)
    {
        //int px,py ;
        float px,py ;
        px = x ;
        py = y ;
        if(steep == true)
        {
            py = -py ;
        }
        if(flip == true)
        {
            t = px ;
            px = py ;
            py = t ;
        }

        //glVertex2i(px,py);
        glVertex2f(px,py);

        x+=0.01 ;
        //x++ ;

        if(d<0)
        {
            d = d+dS ;
        }
        else
        {
            y+=0.01 ;
            //y++ ;
            d = d+dT ;
        }

    }


    glPointSize(2.0f);
    //glBegin(GL_POINTS);

    x1 = -3, y1 = 0 , x2 = 0, y2 = 5 ;

    steep = false ;
    flip = false ;

    dx = x2-x1 ;
    dy = y2-y1 ;

    if(abs(dy)>abs(dx))
    {
        t = x1;
        x1 = y1 ;
        y1 = t ;
        t = x2 ;
        x2 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
        flip = true ;

    }

    if(x1>x2)
    {
        t = x1;
        x1 = x2 ;
        x2 = t ;
        t = y1 ;
        y1 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
    }

    if(dy<0)
    {
        y1 = -y1 ;
        y2 = -y2 ;
        dy = y2-y1 ;
        steep = true ;
    }

    x = x1;
    y = y1 ;
    dT = 2*(dy-dx) ;
    dS = 2*dy ;
    d = 2*dy-dx ;

    //glVertex2i(x,y);

    while(x <= x2)
    {
        //int px,py ;
        float px,py ;
        px = x ;
        py = y ;
        if(steep == true)
        {
            py = -py ;
        }
        if(flip == true)
        {
            t = px ;
            px = py ;
            py = t ;
        }

        //glVertex2i(px,py);
        glVertex2f(px,py);

        x+=0.01 ;
        //x++ ;

        if(d<0)
        {
            d = d+dS ;
        }
        else
        {
            y+=0.01 ;
            //y++ ;
            d = d+dT ;
        }

    }

    glPointSize(2.0f);
    //glBegin(GL_POINTS);

    x1 = -3, y1 = 0 , x2 = 3, y2 = 3 ;

    steep = false ;
    flip = false ;

    dx = x2-x1 ;
    dy = y2-y1 ;

    if(abs(dy)>abs(dx))
    {
        t = x1;
        x1 = y1 ;
        y1 = t ;
        t = x2 ;
        x2 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
        flip = true ;

    }

    if(x1>x2)
    {
        t = x1;
        x1 = x2 ;
        x2 = t ;
        t = y1 ;
        y1 = y2 ;
        y2 = t ;
        dx = x2-x1 ;
        dy = y2-y1 ;
    }

    if(dy<0)
    {
        y1 = -y1 ;
        y2 = -y2 ;
        dy = y2-y1 ;
        steep = true ;
    }

    x = x1;
    y = y1 ;
    dT = 2*(dy-dx) ;
    dS = 2*dy ;
    d = 2*dy-dx ;

    //glVertex2i(x,y);

    while(x <= x2)
    {
        //int px,py ;
        float px,py ;
        px = x ;
        py = y ;
        if(steep == true)
        {
            py = -py ;
        }
        if(flip == true)
        {
            t = px ;
            px = py ;
            py = t ;
        }

        //glVertex2i(px,py);
        glVertex2f(px,py);

        x+=0.01 ;
        //x++ ;

        if(d<0)
        {
            d = d+dS ;
        }
        else
        {
            y+=0.01 ;
            //y++ ;
            d = d+dT ;
        }

    }


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
    glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
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
    glutDisplayFunc(line);
    glutMainLoop();
    return 0;
}
