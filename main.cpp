#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-210, 210, -220, 310, -210, 310);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //-----------------------------------FIELD (MATH)------------------------------
    glBegin(GL_POLYGON);
        glColor3ub(0, 100, 0); // Green
        glVertex2i(-200, 100);
        glVertex2i(-100, 160);
        glVertex2i(0, 100);
        glVertex2i(50, 70);
        glVertex2i(100, 180);
        glVertex2i(200, 100);

        glColor3ub(255, 215, 0); // Gold
        glVertex2i(200, -200);
        glVertex2i(-200, -200);
        glVertex2i(-200, 100);
    glEnd();

    //------------------------------------------RIVER--------------------------------------------------
    glBegin(GL_POLYGON);
        glColor3ub(30, 144, 255); // Deep Sky Blue
        glVertex2i(-200, -50);
        glVertex2i(200, -30);
        
        glColor3ub(0, 0, 128);    // Navy Blue (Niche dark effect)
        glVertex2i(200, -200);
        glVertex2i(-200, -200);
        glVertex2i(-200, -50);
    glEnd();

    //---------------------------------------RIVER BORDER---------------------------------------------
    glBegin(GL_POLYGON);
        glColor3ub(128, 128, 0); // Olive color border
        glVertex2i(-200, -45);
        glVertex2i(200, -25);
        glVertex2i(200, -30);
        glVertex2i(-200, -50);
        glVertex2i(-200, -45);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Field and River Only");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
