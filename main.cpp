#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

double r=.2,s=15;
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
        double dx = x + cos((i*3.14)/180)*20;
        double dy = y + sin((i*3.14)/180)*10;
        glVertex2d(dx,dy);
    }
    glEnd();
}

//---------------- SUN ----------------
void sun(double x, double y)
{
    glBegin(GL_TRIANGLE_FAN);
    for(i=0;i<360;i++)
    {
        double dx = x + cos((i*3.14)/180)*s;
        double dy = y + sin((i*3.14)/180)*s;
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

//---------------- SUN ----------------
    glColor3ub(255,215,0);
    sun(90,250);

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

//---------------- CLOUD ----------------
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

//---------------- TREE ----------------
    // small tree
    glColor3ub(139,69,19);
    glRecti(-20,200,-13,140);

    glColor3ub(0,100,0);
    sun(-30,190);
    sun(0,190);
    sun(-10,210);
    sun(-30,175);
    sun(0,170);

    // big tree trunk
    glBegin(GL_POLYGON);
        glColor3ub(139,69,19);
        glVertex2i(-170,160);
        glVertex2i(-168,120);
        glVertex2i(-178,40);
        glVertex2i(-145,40);
        glVertex2i(-153,120);
        glVertex2i(-150,160);
    glEnd();

    // branches
    glBegin(GL_POLYGON);
        glVertex2i(-153,100);
        glVertex2i(-100,200);
        glVertex2i(-95,200);
        glVertex2i(-153,80);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2i(-170,160);
        glVertex2i(-185,210);
        glVertex2i(-190,210);
        glVertex2i(-168,90);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2i(-160,160);
        glVertex2i(-150,210);
        glVertex2i(-140,210);
        glVertex2i(-150,160);
    glEnd();

    // leaves
    glColor3ub(0,128,0);

    sun(-95,200);
    sun(-80,180);
    sun(-110,180);
    sun(-120,200);

    sun(-150,200);
    sun(-130,180);
    sun(-125,220);
    sun(-140,230);

    sun(-190,210);
    sun(-180,200);
    sun(-175,225);
    sun(-195,190);

//---------------- END ----------------
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

