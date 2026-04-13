#include <GL/glut.h>
#include <cmath>

// Array to store individual X positions of 3 clouds
float cloudX[3] = {100.0f, 500.0f, 850.0f};

// Variables for sun animation
float sunAngle = 0.0f; // Angle to calculate the arc (U-shape) path
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
    glColor3f(0.45f, 0.75f, 0.95f); // Deep sky blue
    glVertex2f(0, 580);
    glVertex2f(1130, 580);
    glColor3f(0.70f, 0.85f, 1.0f);  // Light sky blue near horizon
    glVertex2f(1130, 300);
    glVertex2f(0, 300);
    glEnd();
}

// Updated drawSun to take dynamic coordinates and reduced size
void drawSun(float x, float y) {
    // Outer Glow (Light Orange/Peach) - Slightly smaller
    glColor3f(1.0f, 0.5f, 0.0f); 
    drawCircle(x, y, 40); // Was 55
    
    // Main Sun Body (Deep Orange) - Slightly smaller
    glColor3f(1.0f, 0.4f, 0.0f); 
    drawCircle(x, y, 30); // Was 45
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // White color for cloud
    drawCircle(x, y, 20);
    drawCircle(x + 20, y + 15, 30);
    drawCircle(x + 45, y + 5, 25);
    drawCircle(x + 60, y - 5, 20);
    drawCircle(x + 20, y - 5, 20);
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
    // Draw small grass lines
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
    // Draw river waves
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
    
    // Draw animated sun
    drawSun(sunX, sunY); 
    
    // Draw each cloud using its independent X position
    drawCloud(cloudX[0], 500); 
    drawCloud(cloudX[1], 460);
    drawCloud(cloudX[2], 520);

    // Draw hills after the sun so the sun hides behind them
    drawHills();
    drawGreenField();
    drawBlueRiver();

    // Use double buffering
    glutSwapBuffers(); 
}

// Animation logic for clouds and sun
void update(int value) {
    // --- Cloud Animation ---
    for(int i = 0; i < 3; i++) {
        cloudX[i] += 0.5f; // Cloud movement speed
        
        // If a specific cloud goes off the right screen, move ONLY that cloud to the left
        if (cloudX[i] > 1200.0f) {
            cloudX[i] = -100.0f; 
        }
    }

    // --- Sun Animation (Inverted U-Shape Arc) ---
    sunAngle += 0.003f; // Controls the speed of the day/night cycle
    
    // If the sun reaches the right side (angle Pi), reset it to start again
    if (sunAngle > 3.14159f) {
        sunAngle = 0.0f; 
    }

    // Calculate X and Y using Sine and Cosine for a smooth semi-circle path
    // Center X is 565, Radius X is 500
    sunX = 565.0f - 500.0f * cosf(sunAngle); 
    
    // Base Y is 150 (hidden behind hills), max height is 150 + 400 = 550
    sunY = 150.0f + 400.0f * sinf(sunAngle); 
    
    glutPostRedisplay();
    // Call update function again after ~16ms (approx. 60 FPS)
    glutTimerFunc(16, update, 0); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // Enable double buffering for smooth animation
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
    glutInitWindowSize(1130, 580);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("Green Field and Blue River Scene - Animated Sun & Clouds");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1130, 0, 580, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the initial sun position
    sunX = 565.0f - 500.0f * cosf(0.0f);
    sunY = 150.0f + 400.0f * sinf(0.0f);

    glutDisplayFunc(display);
    
    // Start the timer function
    glutTimerFunc(25, update, 0); 
    
    glutMainLoop();
    return 0;
}