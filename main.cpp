#include <GL/glut.h>
#include <cmath>

// --- Utility Functions ---

void drawCircle(float cx, float cy, float r, int segs = 32) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < segs; i++) {
        float a = 2.0f * 3.14159f * i / segs;
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

// --- Background Components ---

void drawSky() {
    glBegin(GL_QUADS);
    glColor3f(0.45f, 0.75f, 0.95f); // Deep sky blue
    glVertex2f(0, 580);
    glVertex2f(1130, 580);
    glColor3f(0.70f, 0.85f, 1.0f);  // Light sky blue near horizon
    glVertex2f(1130, 300);
    glVertex2f(0, 300);
    glEnd();
}

// Updated Sun with Orange Color
void drawSun() {
    // Outer Glow (Light Orange/Peach)
    glColor3f(1.0f, 0.5f, 0.0f); 
    drawCircle(150, 480, 55); 
    
    // Main Sun Body (Deep Orange)
    glColor3f(1.0f, 0.4f, 0.0f); 
    drawCircle(150, 480, 45); 
}

void drawHills() {
    glColor3f(0.1f, 0.4f, 0.1f); // Dark green hills
    glBegin(GL_POLYGON);
    glVertex2f(0, 300);
    glVertex2f(200, 420);
    glVertex2f(450, 300);
    glVertex2f(700, 450);
    glVertex2f(1000, 300);
    glVertex2f(1130, 380);
    glVertex2f(1130, 300);
    glEnd();
}

// --- The Green Field ---

void drawGreenField() {
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.7f, 0.2f); // Bright Green
    glVertex2f(0, 300);
    glVertex2f(1130, 300);
    glColor3f(0.1f, 0.5f, 0.1f); // Forest Green
    glVertex2f(1130, 150);
    glVertex2f(0, 150);
    glEnd();

    glColor3f(0.05f, 0.35f, 0.05f);
    glLineWidth(2.0f);
    for (int x = 50; x < 1100; x += 150) {
        glBegin(GL_LINES);
        glVertex2f(x, 220); glVertex2f(x - 5, 235);
        glVertex2f(x, 220); glVertex2f(x + 5, 235);
        glVertex2f(x, 220); glVertex2f(x, 240);
        glEnd();
    }
}

// --- The Blue River ---

void drawBlueRiver() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.4f, 0.8f); // Deep River Blue
    glVertex2f(0, 150);
    glVertex2f(1130, 150);
    glColor3f(0.2f, 0.6f, 1.0f); // Lighter Blue near bottom
    glVertex2f(1130, 0);
    glVertex2f(0, 0);
    glEnd();

    glLineWidth(3.0f);
    glColor3f(0.4f, 0.7f, 1.0f);
    for (int y = 30; y < 140; y += 40) {
        for (int x = 20; x < 1130; x += 100) {
            glBegin(GL_LINE_STRIP);
            glVertex2f(x, y);
            glVertex2f(x + 30, y + 5);
            glVertex2f(x + 60, y);
            glEnd();
        }
    }
}

void drawBird(float x, float y) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - 10, y + 5);
    glVertex2f(x, y);
    glVertex2f(x + 10, y + 5);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawSun(); // Now Orange
    drawBird(400, 500);
    drawBird(430, 520);
    drawHills();
    drawGreenField();
    drawBlueRiver();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1130, 580);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("Green Field and Blue River Scene - Orange Sun");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1130, 0, 580, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}