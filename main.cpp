#include <GL/glut.h>
#include <cmath>
#include <iostream>

enum AppState { FLAG, TIKTOK };
AppState currentState = FLAG;
// --- Global Variables (Flag) ---
float flagTime = 0.0f;
const float WAVE_SPEED = 0.015f;
const float WAVE_FREQ = 0.012f;
const float WAVE_AMP = 10.0f;

// --- Global Variables (TikTok) ---
float scaleFactor = 1.0f;
bool growing = true;

// --- Color Palette Helpers ---
void setKBlack() { glColor3f(0.0f, 0.0f, 0.0f); }
void setKRed()   { glColor3f(0.737f, 0.0f, 0.0f); }
void setKGreen() { glColor3f(0.0f, 0.4f, 0.0f); }
void setKWhite() { glColor3f(1.0f, 1.0f, 1.0f); }
void setTikTokMagenta() { glColor3f(0.996f, 0.173f, 0.333f); }
void setTikTokCyan()    { glColor3f(0.145f, 0.957f, 0.933f); }
void setTTBlack()       { glColor3f(0.0f, 0.0f, 0.0f); }
// ==========================================
// SECTION 1: KENYA FLAG FUNCTIONS
// ==========================================
void drawVertexWaved(float x, float y) {
    float multiplier = (x + 200.0f) / 400.0f;
    if (multiplier < 0.0f) multiplier = 0.0f;
    if (multiplier > 1.0f) multiplier = 1.0f;

    float yOffset = multiplier * WAVE_AMP * sin(WAVE_FREQ * x + flagTime);
    glVertex2f(x, y + yOffset);
}

void drawFlagPole() {
    // ----- MAIN POLE
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.1f, 0.4f); glVertex2f(-215, -180);
        glColor3f(0.1f, 0.4f, 0.9f); glVertex2f(-205, -180);
        glVertex2f(-205, 140);
        glColor3f(0.0f, 0.1f, 0.4f); glVertex2f(-215, 140);
    glEnd();
    
    glColor3f(1.0f, 0.84f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        
        glVertex2f(-215, -100); glVertex2f(-205, -100);
        glVertex2f(-215, -50);  glVertex2f(-205, -50);
        glVertex2f(-215, 0);    glVertex2f(-205, 0);
        glVertex2f(-215, 50);   glVertex2f(-205, 50);
        glVertex2f(-215, 100);  glVertex2f(-205, 100);
    glEnd();

    glPointSize(4.0f);
    glColor3f(1.0f, 1.0f, 1.0f);  // White
    glBegin(GL_POINTS);
        
        glVertex2f(-210, -170);
        glVertex2f(-210, -130);
        glVertex2f(-210, -90);
        glVertex2f(-210, -50);
        glVertex2f(-210, -10);
        glVertex2f(-210, 30);
        glVertex2f(-210, 70);
        glVertex2f(-210, 110);
    glEnd();

    glColor3f(1.0f, 0.84f, 0.0f);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 10) {
        float rad = i * 3.14159f / 180.0f;
        glVertex2f(-210 + cos(rad) * 12, 145 + sin(rad) * 12);
    }
    glEnd();
}

void drawMaasaiShapeRaw(float maxWidth, float height, float P) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++) {
        float t = -1.0f + 2.0f * i / 100.0f;
        float width = maxWidth * pow(1.0f - pow(fabs(t), P), 1.0f / P);
        drawVertexWaved(width, t * height);
    }
    for (int i = 100; i >= 0; i--) {
        float t = -1.0f + 2.0f * i / 100.0f;
        float width = -maxWidth * pow(1.0f - pow(fabs(t), P), 1.0f / P);
        drawVertexWaved(width, t * height);
    }
    glEnd();
}

void drawSpear(float angle) {
    glPushMatrix();
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // --- 1. THE BLACK BORDER LAYER (Draw First) ---
    setKBlack();
    glBegin(GL_QUADS);
        drawVertexWaved(-3.0f, -96.0f);
        drawVertexWaved(3.0f, -96.0f);
        drawVertexWaved(3.0f, 85.0f);
        drawVertexWaved(-3.0f, 85.0f);
    glEnd();

    glPushMatrix();
        glTranslatef(0, 85, 0);
        drawMaasaiShapeRaw(7.0f, 28.0f, 1.6f);
    glPopMatrix();

    // --- 2. THE WHITE FILL LAYER (Draw Second) ---
    setKWhite();
    glBegin(GL_QUADS);
        drawVertexWaved(-2.0f, -95.0f);
        drawVertexWaved(2.0f, -95.0f);
        drawVertexWaved(2.0f, 84.0f);
        drawVertexWaved(-2.0f, 84.0f);
    glEnd();

    glPushMatrix();
        glTranslatef(0, 85, 0);
        drawMaasaiShapeRaw(6.0f, 26.0f, 1.6f);
    glPopMatrix();

    glPopMatrix();
}
void drawShieldEmblem() {
    setKBlack();
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++) {
        float t = -1.0f + 2.0f * i / 100.0f;
        float width = 43.0f * pow(1.0f - pow(fabs(t), 1.6f), 1.0f / 1.6f);
        float yBase = (t > 0.3f) ? t * 83.0f : 0.3f * 83.0f;
        drawVertexWaved(width, yBase);
    }
    for (int i = 100; i >= 0; i--) {
        float t = -1.0f + 2.0f * i / 100.0f;
        float width = -43.0f * pow(1.0f - pow(fabs(t), 1.6f), 1.0f / 1.6f);
        float yBase = (t > 0.3f) ? t * 83.0f : 0.3f * 83.0f;
        drawVertexWaved(width, yBase);
    }
    glEnd();

    setKRed(); drawMaasaiShapeRaw(43.0f, 83.0f, 1.6f);

    setKBlack();
    glPushMatrix(); glTranslatef(-36.0f, 0.0f, 0.0f); drawMaasaiShapeRaw(7.0f, 32.5f, 1.6f); glPopMatrix();
    glPushMatrix(); glTranslatef(36.0f, 0.0f, 0.0f);  drawMaasaiShapeRaw(7.0f, 32.5f, 1.6f); glPopMatrix();

    setKWhite();
    glPushMatrix(); glTranslatef(0.0f, 42.0f, 0.0f);  drawMaasaiShapeRaw(7.0f, 38.0f, 1.6f);  glPopMatrix();
    glPushMatrix(); glTranslatef(0.0f, -42.0f, 0.0f); drawMaasaiShapeRaw(7.0f, 38.0f, 1.6f);  glPopMatrix();

    setKRed();
    glBegin(GL_QUADS);
        drawVertexWaved(-1.5f, -80.0f);
        drawVertexWaved(1.5f, -80.0f);
        drawVertexWaved(1.5f, 80.0f);
        drawVertexWaved(-1.5f, 80.0f);
    glEnd();

    setKWhite();
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++) {
        float rad = i * 3.14159f / 180.0f;
        drawVertexWaved(cos(rad) * 4.5f, sin(rad) * 7.0f);
    }
    glEnd();
}
void renderKenyaFlag() {
    flagTime += WAVE_SPEED;
    if (flagTime > 6.28f * 2.0f) flagTime -= 6.28f * 2.0f;

    drawFlagPole();

    // Black Stripe
    setKBlack(); glBegin(GL_QUADS);
        drawVertexWaved(-200, 44); drawVertexWaved(200, 44);
        drawVertexWaved(200, 100); drawVertexWaved(-200, 100);
    glEnd();

    // White Stripe
    setKWhite(); glBegin(GL_QUADS);
        drawVertexWaved(-200, 32); drawVertexWaved(200, 32);
        drawVertexWaved(200, 44); drawVertexWaved(-200, 44);
    glEnd();

    // Red Stripe
    setKRed();   glBegin(GL_QUADS);
        drawVertexWaved(-200, -32); drawVertexWaved(200, -32);
        drawVertexWaved(200, 32); drawVertexWaved(-200, 32);
    glEnd();

    // White Stripe
    setKWhite(); glBegin(GL_QUADS);
        drawVertexWaved(-200, -44); drawVertexWaved(200, -44);
        drawVertexWaved(200, -32); drawVertexWaved(-200, -32);
    glEnd();

    // Green Stripe
    setKGreen(); glBegin(GL_QUADS);
        drawVertexWaved(-200, -100); drawVertexWaved(200, -100);
        drawVertexWaved(200, -44); drawVertexWaved(-200, -44);
    glEnd();

    drawSpear(42.0f);
    drawSpear(-42.0f);
    drawShieldEmblem();
}

// ==========================================
// SECTION 2: TIKTOK LOGO FUNCTIONS
// ==========================================

void drawNoteShape() {
    const float pi = 3.14159f;
    float w = 30.0f; // Scaled up to match flag coordinates
    float cx1 = -w, cy1 = -35.0f;
    float rIn1 = w, rOut1 = w * 2.0f;

    glBegin(GL_QUAD_STRIP);
    for (int i = 90; i <= 370; i += 5) {
        float rad = i * pi / 180.0f;
        glVertex2f(cx1 + rIn1 * cos(rad), cy1 + rIn1 * sin(rad));
        glVertex2f(cx1 + rOut1 * cos(rad), cy1 + rOut1 * sin(rad));
    }
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(0.0f, -35.0f); glVertex2f(w, -35.0f);
        glVertex2f(w, 120.0f);    glVertex2f(0.0f, 120.0f);
    glEnd();

    float hookRadius = w * 2.2f;
    float cx2 = w + hookRadius - 30.0f;
    float cy2 = 120.0f;
    glBegin(GL_QUAD_STRIP);
    for (int i = 180; i <= 270; i += 5) {
        float rad = i * pi / 180.0f;
        glVertex2f(cx2 + (hookRadius - w) * cos(rad), cy2 + (hookRadius - w) * sin(rad));
        glVertex2f(cx2 + hookRadius * cos(rad), cy2 + hookRadius * sin(rad));
    }
    glEnd();
}

void renderTikTokLogo() {
    glScalef(scaleFactor, scaleFactor, 1.0f);
    glRotatef(-2.0f, 0.0f, 0.0f, 1.0f);

    glPushMatrix(); glTranslatef(-8.0f, 6.0f, 0.0f); setTikTokCyan(); drawNoteShape(); glPopMatrix();
    glPushMatrix(); glTranslatef(8.0f, -6.0f, 0.0f); setTikTokMagenta(); drawNoteShape(); glPopMatrix();
    glPushMatrix(); setTTBlack(); drawNoteShape(); glPopMatrix();
}

// ==========================================
// SECTION 3: SYSTEM FUNCTIONS (Keyboard, Display, Reshape)
// ==========================================

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if (currentState == FLAG) {
        renderKenyaFlag();
    } else {
        renderTikTokLogo();
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 8) { // Backspace Key
        if (currentState == FLAG) currentState = TIKTOK;
        else currentState = FLAG;
    }
    glutPostRedisplay();
}

void idle() {
    // Pulse animation logic for TikTok
    if (growing) {
        scaleFactor += 0.001f;
        if (scaleFactor >= 1.1f) growing = false;
    } else {
        scaleFactor -= 0.001f;
        if (scaleFactor <= 0.9f) growing = true;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / (float)h;
    if (w >= h) {
        gluOrtho2D(-220.0 * aspect, 220.0 * aspect, -220.0, 220.0);
    }
    else {
        gluOrtho2D(-220.0, 220.0, -220.0 / aspect, 220.0 / aspect);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_MULTISAMPLE);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("OpenGL Project: Kenya Flag & TikTok (Backspace to Switch)");

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); // Keyboard registration
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


