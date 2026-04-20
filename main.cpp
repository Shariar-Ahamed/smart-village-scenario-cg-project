#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

double r=.2;
int i;
float tx=10;

//---------------- INIT ----------------
void init()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glOrtho(-210,210,-220,310,-210,310);
}

//---------------- CLOUD ----------------
void cloud(double x, double y)
{
    glBegin(GL_TRIANGLE_FAN);
    for(i=0;i<360;i++)
    {
        double dx = x + cos((i*3.14)/180)*20; // size fix
        double dy = y + sin((i*3.14)/180)*10;
        glVertex2d(dx,dy);
    }
    glEnd();
}

//---------------- DISPLAY ----------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

//---------------- SKY ----------------
    glColor3ub(135,206,250);
    glRecti(-200,300,200,100);

//---------------- FIELD ----------------
    glBegin(GL_POLYGON);
        glColor3ub(0,100,0);

        glVertex2i(-200,100);
        glVertex2i(-100,160);
        glVertex2i(0,100);
        glVertex2i(50,70);
        glVertex2i(100,180);
        glVertex2i(200,100);

        glColor3ub(255,215,0);
        glVertex2i(200,-200);
        glVertex2i(-200,-200);
        glVertex2i(-200,100);
    glEnd();

//---------------- RIVER ----------------
    glBegin(GL_POLYGON);
        glColor3ub(30,144,255);
        glVertex2i(-200,-50);
        glVertex2i(200,-30);

        glColor3ub(0,0,128);
        glVertex2i(200,-200);
        glVertex2i(-200,-200);
        glVertex2i(-200,-50);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3ub(128,128,0);
        glVertex2i(-200,-45);
        glVertex2i(200,-25);
        glVertex2i(200,-30);
        glVertex2i(-200,-50);
    glEnd();

//---------------- CLOUD DRAW ----------------
    glPushMatrix();
    glColor3ub(255,255,255);
    glTranslatef(tx,0,0);

    cloud(0,250);
    cloud(15,245);
    cloud(10,240);
    cloud(-2,243);

    cloud(-80,250);
    cloud(-95,245);
    cloud(-90,240);
    cloud(-90,243);
    cloud(-75,243);

    glPopMatrix();

    tx+=.05;
    if(tx>200) tx=-200;

    glutPostRedisplay();
    glFlush();
}

//---------------- MAIN ----------------
int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(1200,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Village Scene");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
