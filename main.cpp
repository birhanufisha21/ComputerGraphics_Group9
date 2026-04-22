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
void drawVertexWaved(float x, float y) {
    float multiplier = (x + 200.0f) / 400.0f;
    if (multiplier < 0.0f) multiplier = 0.0f;
    if (multiplier > 1.0f) multiplier = 1.0f;

    float yOffset = multiplier * WAVE_AMP * sin(WAVE_FREQ * x + flagTime);
    glVertex2f(x, y + yOffset);
}


void drawFlagPole() {
    glBegin(GL_QUADS);
        glColor3f(0.0f, 0.1f, 0.4f); glVertex2f(-215, -180);
        glColor3f(0.1f, 0.4f, 0.9f); glVertex2f(-205, -180);
        glVertex2f(-205, 140);
        glColor3f(0.0f, 0.1f, 0.4f); glVertex2f(-215, 140);
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
