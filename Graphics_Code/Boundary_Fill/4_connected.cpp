/**s
This is 4 connected Boundary fill Algorithm
*/


#include <GL/freeglut.h>

#include <bits/stdc++.h>
using namespace std;

int winWidth = 500, winHeight = 500;

// Fill and boundary colors (RGB) in unsigned char (0-255)
unsigned char fillColor[3]     = {255, 0, 0};     // Red fill
unsigned char boundaryColor[3] = {255, 255, 255}; // White boundary

// -------------------- Utility Functions --------------------

// Read pixel color from framebuffer at (x,y)
void getPixelColor(int x, int y, unsigned char color[3])
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, color);
}

bool sameColor(unsigned char c1[3], unsigned char c2[3])
{
    return (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]);
}

// Plot pixel with given color
void setPixel(int x, int y, unsigned char color[3])
{
    glColor3ub(color[0], color[1], color[2]);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// -------------------- Boundary Fill (4-connected) --------------------
void boundaryFill4(int x, int y, unsigned char fillCol[3], unsigned char boundaryCol[3])
{
    unsigned char current[3];
    getPixelColor(x, y, current);

    // if current pixel is NOT boundary color and NOT already filled
    if (!sameColor(current, boundaryCol) && !sameColor(current, fillCol))
    {
        setPixel(x, y, fillCol);

        boundaryFill4(x + 1, y, fillCol, boundaryCol);
        boundaryFill4(x - 1, y, fillCol, boundaryCol);
        boundaryFill4(x, y + 1, fillCol, boundaryCol);
        boundaryFill4(x, y - 1, fillCol, boundaryCol);
    }
}

// -------------------- Drawing boundary shape --------------------
void drawBoundaryRectangle(int x1, int y1, int x2, int y2)
{
    glColor3ub(boundaryColor[0], boundaryColor[1], boundaryColor[2]);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
}

// -------------------- Display --------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw a rectangle boundary
    drawBoundaryRectangle(150, 150, 350, 350);
    boundaryFill4(250, 250, fillColor, boundaryColor);

    glFlush();
}

// -------------------- Mouse click fill --------------------
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert mouse y (top-left origin) to OpenGL y (bottom-left origin)
        int newY = winHeight - y;

        boundaryFill4(x, newY, fillColor, boundaryColor);
    }
}

// -------------------- Init --------------------
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // background black
    glPointSize(1.0);
}

// -------------------- Reshape --------------------
void reshape(int w, int h)
{
    winWidth = w;
    winHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h); // pixel-like coordinate system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// -------------------- Main --------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Boundary Fill Algorithm");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
