// ------------------------------------------------------------
// Computer Graphics Lab 3 (SAVE THE RED BALL)
// ------------------------------------------------------------
// What this program does (as the manual requires):
//  1) Two balls:
//      - BLUE ball radius = 5
//      - RED  ball radius = 25 (5x bigger)
//  2) Window/world size is >= 10 * red radius  => >= 250
//  3) BLUE starts at random position with random velocity.
//      - Min speed to cross screen in 4 seconds
//      - Max speed to cross screen in 2 seconds
//      - BLUE bounces (rebounds) from all walls automatically.
//  4) RED moves with arrow keys.
//      - RED does NOT bounce. It cannot go outside the wall.
//  5) Transformations:
//      - DO NOT use OpenGL built-in transforms (NO glTranslatef/glScalef/etc.)
//      - We make our own 3x3 matrix functions and apply them.
//  6) Circle drawing:
//      - Built using sin() and cos().
// ------------------------------------------------------------

#include <windows.h>
#include <GL/freeglut.h>

#include <cmath>
#include <ctime>
#include <cstdlib>

// ------------------------------
// WORLD SETTINGS
// ------------------------------
// >= 250 because red radius=25 and requirement is at least 10x.
float WORLD_W = 600.0f;
float WORLD_H = 600.0f;

float R_BLUE = 5.0f;
float R_RED  = 25.0f;

// ------------------------------
// BALL STATES (no structs, just simple variables)
// ------------------------------
float blueX, blueY;
float redX, redY;
float blueVx, blueVy;     // units per second

int gameOver = 0;

// ------------------------------
// SIMPLE 3x3 MATRIX FUNCTIONS
// ------------------------------
void Identity(float M[3][3])
{
    M[0][0] = 1; M[0][1] = 0; M[0][2] = 0;
    M[1][0] = 0; M[1][1] = 1; M[1][2] = 0;
    M[2][0] = 0; M[2][1] = 0; M[2][2] = 1;
}

void Multiply(float A[3][3], float B[3][3], float C[3][3])
{
    // C = A * B
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < 3; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void MakeTranslate(float tx, float ty, float T[3][3])
{
    Identity(T);
    T[0][2] = tx;
    T[1][2] = ty;
}

void MakeScale(float sx, float sy, float S[3][3])
{
    Identity(S);
    S[0][0] = sx;
    S[1][1] = sy;
}

void ApplyToPoint(float M[3][3], float x, float y, float &outX, float &outY)
{
    // Multiply M * [x, y, 1]^T
    outX = M[0][0] * x + M[0][1] * y + M[0][2];
    outY = M[1][0] * x + M[1][1] * y + M[1][2];
}

// ------------------------------
// RANDOM HELPERS
// ------------------------------
float Rand01()
{
    return (float)rand() / (float)RAND_MAX;
}

float RandRange(float a, float b)
{
    return a + (b - a) * Rand01();
}

float RandSignedRange(float minVal, float maxVal)
{
    // returns a random value in [-maxVal,-minVal] or [minVal,maxVal]
    float v = RandRange(minVal, maxVal);
    if (rand() % 2 == 0) v = -v;
    return v;
}

// ------------------------------
// GAME SETUP
// ------------------------------
void ResetGame()
{
    gameOver = 0;

    // Red starts at center
    redX = WORLD_W / 2.0f;
    redY = WORLD_H / 2.0f;

    // Blue random start (inside walls)
    // Also keep it away from red at start (so instant game over doesn't happen)
    while (true)
    {
        blueX = RandRange(R_BLUE, WORLD_W - R_BLUE);
        blueY = RandRange(R_BLUE, WORLD_H - R_BLUE);

        float dx = blueX - redX;
        float dy = blueY - redY;
        float r = R_BLUE + R_RED + 20.0f;
        if (dx * dx + dy * dy > r * r) break;
    }

    // Velocity range:
    //  - min crosses screen in 4 seconds
    //  - max crosses screen in 2 seconds
    // We'll do it separately for x and y, using world width/height.
    float vminX = WORLD_W / 4.0f;
    float vmaxX = WORLD_W / 2.0f;
    float vminY = WORLD_H / 4.0f;
    float vmaxY = WORLD_H / 2.0f;

    blueVx = RandSignedRange(vminX, vmaxX);
    blueVy = RandSignedRange(vminY, vmaxY);
}

// ------------------------------
// COLLISION
// ------------------------------
void CheckCollision()
{
    float dx = blueX - redX;
    float dy = blueY - redY;
    float r = R_BLUE + R_RED;

    if (dx * dx + dy * dy <= r * r)
        gameOver = 1;
}

// ------------------------------
// UPDATE BLUE (automatic movement + bounce)
// ------------------------------
void UpdateBlue(float dt)
{
    // Move using our own TRANSLATE matrix
    float T[3][3];
    MakeTranslate(blueVx * dt, blueVy * dt, T);

    float newX, newY;
    ApplyToPoint(T, blueX, blueY, newX, newY);
    blueX = newX;
    blueY = newY;

    // Bounce on walls
    if (blueX - R_BLUE < 0)
    {
        blueX = R_BLUE;
        blueVx = -blueVx;
    }
    if (blueX + R_BLUE > WORLD_W)
    {
        blueX = WORLD_W - R_BLUE;
        blueVx = -blueVx;
    }

    if (blueY - R_BLUE < 0)
    {
        blueY = R_BLUE;
        blueVy = -blueVy;
    }
    if (blueY + R_BLUE > WORLD_H)
    {
        blueY = WORLD_H - R_BLUE;
        blueVy = -blueVy;
    }
}

// ------------------------------
// DRAW CIRCLE USING sin/cos + OUR MATRIX (T * S)
// ------------------------------
void DrawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    // Build matrix: M = T(cx,cy) * S(radius,radius)
    float T[3][3], S[3][3], M[3][3];
    MakeTranslate(cx, cy, T);
    MakeScale(radius, radius, S);
    Multiply(T, S, M);

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);

    int segments = 60; // more segments => smoother circle
    for (int i = 0; i < segments; i++)
    {
        float theta = (2.0f * 3.14159265f * i) / (float)segments;
        float ux = cos(theta);  // unit circle point
        float uy = sin(theta);

        float wx, wy;
        ApplyToPoint(M, ux, uy, wx, wy);
        glVertex2f(wx, wy);
    }

    glEnd();
}

void DrawText(float x, float y, const char* text)
{
    glRasterPos2f(x, y);
    for (int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

// ------------------------------
// GLUT CALLBACKS
// ------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw BLUE and RED
    DrawCircle(blueX, blueY, R_BLUE, 0, 0, 1);
    DrawCircle(redX,  redY,  R_RED,  1, 0, 0);

    if (gameOver)
    {
        glColor3f(1, 1, 1);
        DrawText(WORLD_W * 0.35f, WORLD_H * 0.52f, "GAME OVER");
        DrawText(WORLD_W * 0.25f, WORLD_H * 0.47f, "Press R to Restart");
    }

    glutSwapBuffers();
}

void timer(int)
{
    float dt = 1.0f / 60.0f; // 60 FPS

    if (!gameOver)
    {
        UpdateBlue(dt);
        CheckCollision();
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

void spe_key(int key, int, int)
{
    // RED movement (no rebound, cannot go outside)
    float step = 10.0f;
    float nextX = redX;
    float nextY = redY;

    if (key == GLUT_KEY_LEFT)  nextX -= step;
    if (key == GLUT_KEY_RIGHT) nextX += step;
    if (key == GLUT_KEY_UP)    nextY += step;
    if (key == GLUT_KEY_DOWN)  nextY -= step;

    // If it stays inside, update. Otherwise ignore ("stuck")
    if (nextX - R_RED >= 0 && nextX + R_RED <= WORLD_W) redX = nextX;
    if (nextY - R_RED >= 0 && nextY + R_RED <= WORLD_H) redY = nextY;

    if (!gameOver) CheckCollision();

    glutPostRedisplay();
}

void keyboard(unsigned char key, int, int)
{
    if (key == 'r' || key == 'R') ResetGame();
    if (key == 27) exit(0); // ESC
}

void init()
{
    glClearColor(0, 0, 0, 0);

    // Simple 2D orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WORLD_W, 0, WORLD_H, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize((int)WORLD_W, (int)WORLD_H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 3 - Save the Red Ball");

    init();
    ResetGame();

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, timer, 0);

    glutMainLoop();
    return 0;
}
