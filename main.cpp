#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

void init()
{
    // Background color (set to white or sky blue)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-210, 210, -220, 310, -210, 310);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //-----------------------------------FIELD ONLY------------------------------
    glBegin(GL_POLYGON);
        glColor3ub(0, 100, 0); // Green grass color

        glVertex2i(-200, 100);
        glVertex2i(-100, 160);
        glVertex2i(0, 100);
        glVertex2i(50, 70);
        glVertex2i(100, 180);
        glVertex2i(200, 100);

        glColor3ub(255, 215, 0); // Fading into a Gold color at the bottom
        glVertex2i(200, -200);
        glVertex2i(-200, -200);

        glColor3ub(255, 215, 0); // Closing the polygon
        glVertex2i(-200, 100);
    glEnd();
    //---------------------------------------------------------------------------

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1200, 800);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Field Only Output");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}