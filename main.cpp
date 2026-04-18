#include <GL/glut.h>
#include <cmath>

// Array to store individual X positions of 3 clouds
float cloudX[3] = {100.0f, 500.0f, 850.0f};

// Variables for sun animation
float sunAngle = 0.0f; 
float sunX = 0.0f;
float sunY = 0.0f;

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
    glColor3f(0.45f, 0.75f, 0.95f); 
    glVertex2f(0, 580);
    glVertex2f(1130, 580);
    glColor3f(0.70f, 0.85f, 1.0f);  
    glVertex2f(1130, 300);
    glVertex2f(0, 300);
    glEnd();
}

void drawSun(float x, float y) {
    // Outer circle (light yellow)
    glColor3f(1.0f, 0.9f, 0.4f);  
    drawCircle(x, y, 40); 
    
    // Inner circle (lighter yellow)
    glColor3f(1.0f, 1.0f, 0.6f);  
    drawCircle(x, y, 30); 
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawCircle(x, y, 20);
    drawCircle(x + 20, y + 15, 30);
    drawCircle(x + 45, y + 5, 25);
    drawCircle(x + 60, y - 5, 20);
    drawCircle(x + 20, y - 5, 20);
}

void drawHills() {
    glColor3f(0.1f, 0.4f, 0.1f); 
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

// --- The Updated Field (Yellowish Green instead of Pure Gold) ---

void drawGreenField() {
    glBegin(GL_POLYGON);
        // Upore Deep Green
        glColor3ub(0, 100, 0); 
        glVertex2i(0, 300);
        glVertex2i(1130, 300);

        // Niche Yellowish-Green
        glColor3ub(154, 205, 50); 
        glVertex2i(1130, 150);
        glVertex2i(0, 150);
    glEnd();

    // Grass lines detail
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
    glColor3f(0.0f, 0.4f, 0.8f); 
    glVertex2f(0, 150);
    glVertex2f(1130, 150);
    glColor3f(0.2f, 0.6f, 1.0f); 
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    
    // Draw Sun before Hills so it rises from behind them
    drawSun(sunX, sunY); 
    
    drawCloud(cloudX[0], 500); 
    drawCloud(cloudX[1], 460);
    drawCloud(cloudX[2], 520);

    drawHills();
    drawGreenField(); 
    drawBlueRiver();

    glutSwapBuffers(); 
}

void update(int value) {
    // Cloud animation
    for(int i = 0; i < 3; i++) {
        cloudX[i] += 0.5f; 
        if (cloudX[i] > 1200.0f) {
            cloudX[i] = -100.0f; 
        }
    }

    // Sun animation (0.0005f makes it very slow and smooth)
    sunAngle += 0.0005f; 
    if (sunAngle > 3.14159f) {
        sunAngle = 0.0f; // Reset position when it sets
    }

    // Parametric equation for a semi-circle path (left to right)
    sunX = 565.0f - 500.0f * cosf(sunAngle); 
    sunY = 150.0f + 400.0f * sinf(sunAngle); 
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(1130, 580);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("Slow Sunrise Animation");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1130, 0, 580, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Initial position of the sun
    sunX = 565.0f - 500.0f * cosf(0.0f);
    sunY = 150.0f + 400.0f * sinf(0.0f);

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0); 
    
    glutMainLoop();
    return 0;
}
