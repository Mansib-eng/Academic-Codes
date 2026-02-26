// 3D Brick Breaker - Single File FreeGLUT C++ (portable PI, no structured bindings needed)
// Compile (Linux):   g++ -std=c++17 -O2 -o brickbreaker main.cpp -lGL -lGLU -lglut -lm
// Compile (Windows MinGW example): g++ -std=c++17 -O2 -o brickbreaker.exe main.cpp -lfreeglut -lopengl32 -lglu32

#include <GL/freeglut.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <utility>

// ─── Constants ───────────────────────────────────────────────────────────────

static constexpr float BOX_W = 10.0f;   // x extent: -BOX_W/2 .. +BOX_W/2
static constexpr float BOX_H = 8.0f;    // y extent:  0 .. BOX_H
static constexpr float BOX_D = 14.0f;   // z extent:  0 .. BOX_D

static constexpr float BALL_R = 0.22f;
static constexpr float BALL_START_SPEED = 6.0f;
static constexpr float BALL_MAX_SPEED   = 18.0f;
static constexpr float SPEED_RAMP_START = 5.0f;   // seconds before ramp begins
static constexpr float SPEED_RAMP_RATE  = 0.35f;  // speed units per second
static constexpr float BRICK_HIT_BOOST  = 0.15f;

static constexpr float PADDLE_W = 2.4f;
static constexpr float PADDLE_H = 1.8f;
static constexpr float PADDLE_Z = 0.6f;  // paddle z position (near back wall)
static constexpr float PADDLE_SPEED = 12.0f;

static constexpr int   BRICK_ROWS = 5;
static constexpr int   BRICK_COLS = 7;
static constexpr float BRICK_MARGIN = 0.35f;
static constexpr float BRICK_GAP   = 0.18f;

static constexpr float DT_FIXED = 1.0f / 60.0f;
static constexpr float DT_SUB   = 1.0f / 300.0f; // substep cap
static constexpr int   TIMER_MS = 16;

static constexpr float SHADOW_EPS = 0.02f;

// Portable PI (fixes M_PI not declared on some compilers)
static constexpr float PI = 3.14159265358979323846f;

// ─── Structures ──────────────────────────────────────────────────────────────

struct Vec3 { float x, y, z; };

inline Vec3 operator+(Vec3 a, Vec3 b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
inline Vec3 operator-(Vec3 a, Vec3 b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }
inline Vec3 operator*(Vec3 a, float s){ return {a.x*s, a.y*s, a.z*s}; }
inline float dot(Vec3 a, Vec3 b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline float length(Vec3 v){ return std::sqrt(dot(v,v)); }
inline Vec3 normalize(Vec3 v){
    float l = length(v);
    return l > 1e-8f ? Vec3{v.x/l, v.y/l, v.z/l} : Vec3{0,0,1};
}

struct Brick {
    float cx, cy;        // center x,y on the front wall (z = BOX_D)
    float hw, hh, hd;    // half-widths
    bool alive;
    float r, g, b;
};

// ─── Game State ──────────────────────────────────────────────────────────────

enum GameState { STATE_IDLE, STATE_PLAYING, STATE_GAMEOVER, STATE_WIN };

static GameState gState = STATE_IDLE;
static int   gScore = 0;
static int   gLives = 3;
static float gTimeSinceLaunch = 0.0f;
static float gCurrentSpeed = BALL_START_SPEED;

// Ball
static Vec3  ballPos = {0, BOX_H*0.5f, 1.5f};
static Vec3  ballVel = {0, 0, 0};

// Paddle
static float paddleX = 0.0f;
static float paddleY = BOX_H * 0.5f;
static bool  keyLeft = false, keyRight = false, keyUp = false, keyDown = false;

// Bricks
static std::vector<Brick> bricks;
static int bricksAlive = 0;

// Window
static int winW = 1200, winH = 800;

// ─── Helpers ─────────────────────────────────────────────────────────────────

static void initBricks() {
    bricks.clear();
    float wallMinX = -BOX_W/2 + BRICK_MARGIN;
    float wallMaxX =  BOX_W/2 - BRICK_MARGIN;
    float wallMinY =  BRICK_MARGIN;
    float wallMaxY =  BOX_H - BRICK_MARGIN;

    float totalW = wallMaxX - wallMinX - (BRICK_COLS-1)*BRICK_GAP;
    float totalH = wallMaxY - wallMinY - (BRICK_ROWS-1)*BRICK_GAP;
    float bw = totalW / BRICK_COLS;
    float bh = totalH / BRICK_ROWS;
    float bd = 0.3f; // depth into the box

    float colors[5][3] = {
        {0.95f,0.25f,0.25f}, {0.95f,0.6f,0.15f}, {0.2f,0.85f,0.3f},
        {0.2f,0.6f,0.95f}, {0.75f,0.3f,0.9f}
    };

    for (int r = 0; r < BRICK_ROWS; r++) {
        for (int c = 0; c < BRICK_COLS; c++) {
            Brick br;
            br.cx = wallMinX + c*(bw+BRICK_GAP) + bw*0.5f;
            br.cy = wallMaxY - r*(bh+BRICK_GAP) - bh*0.5f;
            br.hw = bw*0.5f - 0.02f;
            br.hh = bh*0.5f - 0.02f;
            br.hd = bd*0.5f;
            br.alive = true;
            int ci = r % 5;
            br.r = colors[ci][0]; br.g = colors[ci][1]; br.b = colors[ci][2];
            bricks.push_back(br);
        }
    }
    bricksAlive = BRICK_ROWS * BRICK_COLS;
}

static void resetGame() {
    gScore = 0;
    gLives = 3;
    gTimeSinceLaunch = 0;
    gCurrentSpeed = BALL_START_SPEED;
    ballPos = {0, BOX_H*0.5f, 1.5f};
    ballVel = {0, 0, 0};
    paddleX = 0; paddleY = BOX_H*0.5f;
    gState = STATE_IDLE;
    initBricks();
}

static void launchBall() {
    gState = STATE_PLAYING;
    gTimeSinceLaunch = 0;
    gCurrentSpeed = BALL_START_SPEED;
    float ax = ((rand()%100)-50)*0.006f;
    float ay = ((rand()%100)-50)*0.004f;
    ballVel = normalize(Vec3{ax, ay, 1.0f}) * gCurrentSpeed;
    ballPos = {paddleX, paddleY, PADDLE_Z + BALL_R + 0.05f};
}

static void respawnBall() {
    ballPos = {paddleX, paddleY, PADDLE_Z + BALL_R + 0.05f};
    ballVel = {0,0,0};
    gCurrentSpeed = BALL_START_SPEED;
    gTimeSinceLaunch = 0;
    gState = STATE_IDLE;
}

// ─── Physics ─────────────────────────────────────────────────────────────────

static void clampSpeed() {
    if (gCurrentSpeed > BALL_MAX_SPEED) gCurrentSpeed = BALL_MAX_SPEED;
    float spd = length(ballVel);
    if (spd > 1e-6f) ballVel = normalize(ballVel) * gCurrentSpeed;
}

static bool sphereAABBCollision(Vec3 sp, float sr,
    float bx, float by, float bz, float bhx, float bhy, float bhz,
    Vec3 &normal, float &pen)
{
    float cx = std::max(bx-bhx, std::min(sp.x, bx+bhx));
    float cy = std::max(by-bhy, std::min(sp.y, by+bhy));
    float cz = std::max(bz-bhz, std::min(sp.z, bz+bhz));
    float dx = sp.x-cx, dy = sp.y-cy, dz = sp.z-cz;
    float dist2 = dx*dx + dy*dy + dz*dz;
    if (dist2 < sr*sr) {
        float dist = std::sqrt(dist2);
        if (dist > 1e-8f) {
            normal = {dx/dist, dy/dist, dz/dist};
        } else {
            float px = bhx - std::fabs(sp.x - bx);
            float py = bhy - std::fabs(sp.y - by);
            float pz = bhz - std::fabs(sp.z - bz);
            if (px < py && px < pz) normal = {sp.x < bx ? -1.f : 1.f, 0, 0};
            else if (py < pz)       normal = {0, sp.y < by ? -1.f : 1.f, 0};
            else                    normal = {0, 0, sp.z < bz ? -1.f : 1.f};
        }
        pen = sr - dist;
        return true;
    }
    return false;
}

static void physicsStep(float dt) {
    if (gState != STATE_PLAYING) return;

    gTimeSinceLaunch += dt;
    if (gTimeSinceLaunch > SPEED_RAMP_START) {
        gCurrentSpeed += SPEED_RAMP_RATE * dt;
    }
    clampSpeed();

    ballPos = ballPos + ballVel * dt;

    float halfW = BOX_W / 2.0f;

    if (ballPos.x - BALL_R < -halfW) {
        ballPos.x = -halfW + BALL_R;
        if (ballVel.x < 0) ballVel.x = -ballVel.x;
    }
    if (ballPos.x + BALL_R > halfW) {
        ballPos.x = halfW - BALL_R;
        if (ballVel.x > 0) ballVel.x = -ballVel.x;
    }
    if (ballPos.y - BALL_R < 0) {
        ballPos.y = BALL_R;
        if (ballVel.y < 0) ballVel.y = -ballVel.y;
    }
    if (ballPos.y + BALL_R > BOX_H) {
        ballPos.y = BOX_H - BALL_R;
        if (ballVel.y > 0) ballVel.y = -ballVel.y;
    }
    if (ballPos.z + BALL_R > BOX_D) {
        ballPos.z = BOX_D - BALL_R;
        if (ballVel.z > 0) ballVel.z = -ballVel.z;
    }
    if (ballPos.z - BALL_R < 0) {
        gLives--;
        if (gLives <= 0) gState = STATE_GAMEOVER;
        else respawnBall();
        return;
    }

    // Paddle collision
    {
        float phw = PADDLE_W * 0.5f;
        float phh = PADDLE_H * 0.5f;
        float phd = 0.15f;
        Vec3 norm; float pen;
        if (sphereAABBCollision(ballPos, BALL_R,
            paddleX, paddleY, PADDLE_Z, phw, phh, phd, norm, pen))
        {
            ballPos = ballPos + norm * pen;
            float vn = dot(ballVel, norm);
            if (vn < 0) {
                ballVel = ballVel - norm * (2.0f * vn);
                float offX = (ballPos.x - paddleX) / phw;
                float offY = (ballPos.y - paddleY) / phh;
                ballVel.x += offX * 1.5f;
                ballVel.y += offY * 1.0f;
            }
            clampSpeed();
        }
    }

    // Brick collisions
    for (auto &br : bricks) {
        if (!br.alive) continue;
        float bz = BOX_D - br.hd;
        Vec3 norm; float pen;
        if (sphereAABBCollision(ballPos, BALL_R,
            br.cx, br.cy, bz, br.hw, br.hh, br.hd, norm, pen))
        {
            br.alive = false;
            bricksAlive--;
            gScore += 10;
            gCurrentSpeed += BRICK_HIT_BOOST;

            ballPos = ballPos + norm * pen;
            float vn = dot(ballVel, norm);
            if (vn < 0) ballVel = ballVel - norm * (2.0f * vn);
            clampSpeed();

            if (bricksAlive <= 0) { gState = STATE_WIN; return; }
            break;
        }
    }
}

// ─── Drawing Helpers ─────────────────────────────────────────────────────────

static void drawBox(float hx, float hy, float hz, float cx, float cy, float cz)
{
    float x0=cx-hx, x1=cx+hx;
    float y0=cy-hy, y1=cy+hy;
    float z0=cz-hz, z1=cz+hz;

    glBegin(GL_QUADS);
    glVertex3f(x0,y0,z1); glVertex3f(x1,y0,z1); glVertex3f(x1,y1,z1); glVertex3f(x0,y1,z1); // front
    glVertex3f(x0,y0,z0); glVertex3f(x0,y1,z0); glVertex3f(x1,y1,z0); glVertex3f(x1,y0,z0); // back
    glVertex3f(x0,y0,z0); glVertex3f(x0,y0,z1); glVertex3f(x0,y1,z1); glVertex3f(x0,y1,z0); // left
    glVertex3f(x1,y0,z0); glVertex3f(x1,y1,z0); glVertex3f(x1,y1,z1); glVertex3f(x1,y0,z1); // right
    glVertex3f(x0,y0,z0); glVertex3f(x1,y0,z0); glVertex3f(x1,y0,z1); glVertex3f(x0,y0,z1); // bottom
    glVertex3f(x0,y1,z0); glVertex3f(x0,y1,z1); glVertex3f(x1,y1,z1); glVertex3f(x1,y1,z0); // top
    glEnd();
}

static void drawWireBox(float x0, float y0, float z0, float x1, float y1, float z1)
{
    glBegin(GL_LINES);
    glVertex3f(x0,y0,z0); glVertex3f(x1,y0,z0);
    glVertex3f(x1,y0,z0); glVertex3f(x1,y0,z1);
    glVertex3f(x1,y0,z1); glVertex3f(x0,y0,z1);
    glVertex3f(x0,y0,z1); glVertex3f(x0,y0,z0);

    glVertex3f(x0,y1,z0); glVertex3f(x1,y1,z0);
    glVertex3f(x1,y1,z0); glVertex3f(x1,y1,z1);
    glVertex3f(x1,y1,z1); glVertex3f(x0,y1,z1);
    glVertex3f(x0,y1,z1); glVertex3f(x0,y1,z0);

    glVertex3f(x0,y0,z0); glVertex3f(x0,y1,z0);
    glVertex3f(x1,y0,z0); glVertex3f(x1,y1,z0);
    glVertex3f(x1,y0,z1); glVertex3f(x1,y1,z1);
    glVertex3f(x0,y0,z1); glVertex3f(x0,y1,z1);
    glEnd();
}

static void drawShadowDisk(float wx, float wy, float wz,
                           float nx, float ny, float nz,
                           float radius, float alpha)
{
    if (alpha < 0.01f) return;
    glColor4f(0.0f, 0.0f, 0.0f, alpha * 0.45f);

    Vec3 n = {nx, ny, nz};
    Vec3 up = (std::fabs(ny) < 0.9f) ? Vec3{0,1,0} : Vec3{1,0,0};

    Vec3 t1 = normalize(Vec3{
        up.y*n.z - up.z*n.y,
        up.z*n.x - up.x*n.z,
        up.x*n.y - up.y*n.x
    });

    Vec3 t2 = {
        t1.y*n.z - t1.z*n.y,
        t1.z*n.x - t1.x*n.z,
        t1.x*n.y - t1.y*n.x
    };

    const int segs = 20;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(wx, wy, wz);
    for (int i = 0; i <= segs; i++) {
        float a = 2.0f * PI * (float)i / (float)segs;
        float cs = std::cos(a) * radius, sn = std::sin(a) * radius;
        glVertex3f(wx + t1.x*cs + t2.x*sn,
                   wy + t1.y*cs + t2.y*sn,
                   wz + t1.z*cs + t2.z*sn);
    }
    glEnd();
}

static void drawBallShadows() {
    float halfW = BOX_W / 2.0f;
    float bx = ballPos.x, by = ballPos.y, bz = ballPos.z;
    float baseR = BALL_R * 1.8f;

    auto calcShadow = [&](float dist, float maxDist) -> std::pair<float,float> {
        float t = 1.0f - std::min(dist / maxDist, 1.0f);
        return {baseR * (0.5f + 0.8f * t), t};
    };

    { auto ra = calcShadow(by, BOX_H);
      drawShadowDisk(bx, SHADOW_EPS, bz, 0,1,0, ra.first, ra.second); }

    { auto ra = calcShadow(BOX_H - by, BOX_H);
      drawShadowDisk(bx, BOX_H - SHADOW_EPS, bz, 0,-1,0, ra.first, ra.second); }

    { auto ra = calcShadow(bx + halfW, BOX_W);
      drawShadowDisk(-halfW + SHADOW_EPS, by, bz, 1,0,0, ra.first, ra.second); }

    { auto ra = calcShadow(halfW - bx, BOX_W);
      drawShadowDisk(halfW - SHADOW_EPS, by, bz, -1,0,0, ra.first, ra.second); }

    { auto ra = calcShadow(bz, BOX_D);
      drawShadowDisk(bx, by, SHADOW_EPS, 0,0,1, ra.first, ra.second); }

    { auto ra = calcShadow(BOX_D - bz, BOX_D);
      drawShadowDisk(bx, by, BOX_D - SHADOW_EPS, 0,0,-1, ra.first, ra.second); }
}

static void drawText2D(float x, float y, const char* str, void* font = GLUT_BITMAP_HELVETICA_18) {
    glRasterPos2f(x, y);
    for (const char* c = str; *c; c++) glutBitmapCharacter(font, *c);
}

static void drawCenteredText(float yNorm, const char* str, void* font = GLUT_BITMAP_HELVETICA_18) {
    int tw = 0;
    for (const char* c = str; *c; c++) tw += glutBitmapWidth(font, *c);
    float x = (winW - tw) * 0.5f;
    float y = winH * yNorm;
    glRasterPos2f(x, y);
    for (const char* c = str; *c; c++) glutBitmapCharacter(font, *c);
}

// ─── Display ─────────────────────────────────────────────────────────────────

static void display() {
    glClearColor(0.12f, 0.12f, 0.18f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (double)winW / winH, 0.5, 60.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-8.0, 12.0, -6.0,
               0.0, BOX_H*0.4, BOX_D*0.45,
               0.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);

    float halfW = BOX_W / 2.0f;

    for (auto &br : bricks) {
        if (!br.alive) continue;
        glColor4f(br.r, br.g, br.b, 0.92f);
        float bz = BOX_D - br.hd;
        drawBox(br.hw, br.hh, br.hd, br.cx, br.cy, bz);

        glColor4f(0,0,0, 0.35f);
        glLineWidth(1.0f);
        drawWireBox(br.cx-br.hw, br.cy-br.hh, bz-br.hd,
                    br.cx+br.hw, br.cy+br.hh, bz+br.hd);
    }

    glColor4f(1,1,1,1);
    glPushMatrix();
    glTranslatef(ballPos.x, ballPos.y, ballPos.z);
    glutSolidSphere(BALL_R, 20, 20);
    glPopMatrix();

    drawBallShadows();

    glColor4f(0.3f, 0.85f, 1.0f, 0.55f);
    {
        float phw = PADDLE_W*0.5f, phh = PADDLE_H*0.5f;
        glBegin(GL_QUADS);
        glVertex3f(paddleX-phw, paddleY-phh, PADDLE_Z);
        glVertex3f(paddleX+phw, paddleY-phh, PADDLE_Z);
        glVertex3f(paddleX+phw, paddleY+phh, PADDLE_Z);
        glVertex3f(paddleX-phw, paddleY+phh, PADDLE_Z);
        glEnd();

        glColor4f(0.4f, 0.95f, 1.0f, 0.85f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(paddleX-phw, paddleY-phh, PADDLE_Z);
        glVertex3f(paddleX+phw, paddleY-phh, PADDLE_Z);
        glVertex3f(paddleX+phw, paddleY+phh, PADDLE_Z);
        glVertex3f(paddleX-phw, paddleY+phh, PADDLE_Z);
        glEnd();
    }

    glDepthMask(GL_FALSE);

    glColor4f(0.35f, 0.55f, 0.75f, 0.10f);
    glBegin(GL_QUADS); glVertex3f(-halfW,0,0); glVertex3f(halfW,0,0); glVertex3f(halfW,0,BOX_D); glVertex3f(-halfW,0,BOX_D); glEnd(); // bottom
    glBegin(GL_QUADS); glVertex3f(-halfW,BOX_H,0); glVertex3f(-halfW,BOX_H,BOX_D); glVertex3f(halfW,BOX_H,BOX_D); glVertex3f(halfW,BOX_H,0); glEnd(); // top
    glBegin(GL_QUADS); glVertex3f(-halfW,0,0); glVertex3f(-halfW,0,BOX_D); glVertex3f(-halfW,BOX_H,BOX_D); glVertex3f(-halfW,BOX_H,0); glEnd(); // left
    glBegin(GL_QUADS); glVertex3f(halfW,0,0); glVertex3f(halfW,BOX_H,0); glVertex3f(halfW,BOX_H,BOX_D); glVertex3f(halfW,0,BOX_D); glEnd(); // right

    glColor4f(0.35f, 0.55f, 0.75f, 0.06f);
    glBegin(GL_QUADS); glVertex3f(-halfW,0,BOX_D); glVertex3f(halfW,0,BOX_D); glVertex3f(halfW,BOX_H,BOX_D); glVertex3f(-halfW,BOX_H,BOX_D); glEnd(); // front

    glColor4f(0.35f, 0.55f, 0.75f, 0.08f);
    glBegin(GL_QUADS); glVertex3f(-halfW,0,0); glVertex3f(-halfW,BOX_H,0); glVertex3f(halfW,BOX_H,0); glVertex3f(halfW,0,0); glEnd(); // back

    glDepthMask(GL_TRUE);

    glLineWidth(1.5f);
    glColor4f(0.6f, 0.75f, 0.9f, 0.55f);
    drawWireBox(-halfW, 0, 0, halfW, BOX_H, BOX_D);

    // HUD
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); glLoadIdentity();
    gluOrtho2D(0, winW, 0, winH);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix(); glLoadIdentity();

    char buf[128];
    glColor4f(1,1,1,1);
    std::snprintf(buf, sizeof(buf), "Score: %d", gScore);
    drawText2D(15, winH - 28, buf);

    std::snprintf(buf, sizeof(buf), "Speed: %.1f", gCurrentSpeed);
    drawText2D(15, winH - 50, buf);

    std::snprintf(buf, sizeof(buf), "Lives: %d", gLives);
    int lw = 0; for (const char* c = buf; *c; c++) lw += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
    drawText2D(winW - lw - 15, winH - 28, buf);

    if (gState == STATE_IDLE) {
        glColor4f(1,1,0.6f,1);
        drawCenteredText(0.55f, "Left Click to Start");
        glColor4f(0.8f,0.8f,0.8f,1);
        drawCenteredText(0.48f, "Arrow Keys: Move Paddle (Left/Right/Up/Down)");
    } else if (gState == STATE_GAMEOVER) {
        glColor4f(1,0.2f,0.2f,1);
        drawCenteredText(0.55f, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
        glColor4f(1,1,0.6f,1);
        drawCenteredText(0.48f, "Left Click to Restart");
    } else if (gState == STATE_WIN) {
        glColor4f(0.2f,1,0.3f,1);
        drawCenteredText(0.55f, "YOU WIN!", GLUT_BITMAP_TIMES_ROMAN_24);
        glColor4f(1,1,0.6f,1);
        drawCenteredText(0.48f, "Left Click to Play Again");
    }

    glMatrixMode(GL_PROJECTION); glPopMatrix();
    glMatrixMode(GL_MODELVIEW); glPopMatrix();
    glEnable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

// ─── Callbacks ───────────────────────────────────────────────────────────────

static void reshape(int w, int h) {
    winW = w; winH = h;
    glViewport(0, 0, w, h);
}

static void timerFunc(int) {
    float dt = DT_FIXED;
    float halfW = BOX_W / 2.0f;

    float pdx = 0, pdy = 0;

    // ✅ FIX (your exact complaint):
    // With this camera angle, world -X can look like screen-right.
    // So we flip X input so: LEFT arrow moves paddle LEFT on screen, RIGHT arrow moves paddle RIGHT on screen.
    if (keyLeft)  pdx += PADDLE_SPEED * dt;   // (flipped)
    if (keyRight) pdx -= PADDLE_SPEED * dt;   // (flipped)

    if (keyUp)    pdy += PADDLE_SPEED * dt;
    if (keyDown)  pdy -= PADDLE_SPEED * dt;

    paddleX += pdx; paddleY += pdy;
    paddleX = std::max(-halfW + PADDLE_W*0.5f, std::min(paddleX, halfW - PADDLE_W*0.5f));
    paddleY = std::max(PADDLE_H*0.5f, std::min(paddleY, BOX_H - PADDLE_H*0.5f));

    if (gState == STATE_IDLE) {
        ballPos.x = paddleX;
        ballPos.y = paddleY;
        ballPos.z = PADDLE_Z + BALL_R + 0.05f;
    }

    if (gState == STATE_PLAYING) {
        float rem = dt;
        while (rem > 1e-6f) {
            float step = std::min(rem, DT_SUB);
            physicsStep(step);
            rem -= step;
            if (gState != STATE_PLAYING) break;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(TIMER_MS, timerFunc, 0);
}

static void mouseFunc(int button, int state, int, int) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (gState == STATE_IDLE) launchBall();
        else if (gState == STATE_GAMEOVER || gState == STATE_WIN) resetGame();
    }
}

static void keyboardFunc(unsigned char key, int, int) {
    if (key == 27) std::exit(0);
}

// Correct mapping (this part is NOT reversed)
static void specialDownFunc(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT:  keyLeft  = true;  break;
        case GLUT_KEY_RIGHT: keyRight = true;  break;
        case GLUT_KEY_UP:    keyUp    = true;  break;
        case GLUT_KEY_DOWN:  keyDown  = true;  break;
    }
}

static void specialUpFunc(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT:  keyLeft  = false; break;
        case GLUT_KEY_RIGHT: keyRight = false; break;
        case GLUT_KEY_UP:    keyUp    = false; break;
        case GLUT_KEY_DOWN:  keyDown  = false; break;
    }
}

// ─── Main ────────────────────────────────────────────────────────────────────

int main(int argc, char** argv) {
    std::srand((unsigned)std::time(nullptr));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("3D Brick Breaker");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initBricks();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseFunc);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialDownFunc);
    glutSpecialUpFunc(specialUpFunc);
    glutTimerFunc(TIMER_MS, timerFunc, 0);

    glutMainLoop();
    return 0;
}
