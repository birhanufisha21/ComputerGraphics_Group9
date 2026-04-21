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
// Placeholder functions for members to fill
void drawFlagPole() {}
void drawMaasaiShapeRaw(float mw, float h, float p) {}
void drawSpear(float angle) {}
void drawShieldEmblem() {}
void renderKenyaFlag() {}
void drawNoteShape() {}
void renderTikTokLogo() {}
void drawVertexWaved(float x, float y) { glVertex2f(x, y); } // Base version

// System functions (Keyboard, Display, Reshape) go here...
// (Paste the 'display', 'keyboard', 'reshape', and 'main' functions from your original code)
