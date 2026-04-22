#include<windows.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
double  r=.2,s=.3;
int i;
float  tx=10,bx=10;
float sx = -150;     // sun x position
float mx = 220;      // moon x position (start outside right)
bool isNight = false;
int starBlink = 0; //star
float solarAngle = 0;
float scaleFactor = 1.0f; //boat
bool scaleUp = true;
float gearAngle = 0.0f;

void drawCircle(int xc, int yc, int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    glBegin(GL_POINTS);

    while(x <= y)
    {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        if(d < 0)
            d += 2*x + 3;
        else
        {
            d += 2*(x - y) + 5;
            y--;
        }
        x++;
    }

    glEnd();
}


void init()
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);
    glOrtho(-210,210,-220,310,-210,310);

}

// _________==================Windmaill===============
void windmill(int x, int y)
{
    // pole
    glColor3ub(139,69,19);
    glBegin(GL_POLYGON);
        glVertex2i(x, y);
        glVertex2i(x+4, y);
        glVertex2i(x+4, y+80);
        glVertex2i(x, y+80);
    glEnd();

    // head (rotating)
    glPushMatrix();
    glTranslatef(x+2, y+80, 0);
    glRotatef(gearAngle, 0, 0, 1);

    glColor3ub(250,0,0);

    glBegin(GL_LINES);
        glVertex2f(0,0);
        glVertex2f(20,0);

        glVertex2f(0,0);
        glVertex2f(-20,0);

        glVertex2f(0,0);
        glVertex2f(0,20);

        glVertex2f(0,0);
        glVertex2f(0,-20);
    glEnd();

    glPopMatrix();
}
//-----------------------sun------------------------------------------------------------------

void sun(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
        for(i=0;i<360;i++)
        {
            x=x+cos((i*3.14)/180)*s;
            y=y+sin((i*3.14)/180)*s;

            glVertex2d(x,y);

        }


    glEnd();



}

//-----------------------moon------------------------------------------------------------------

void moon(double x, double y)
{
    // 🌙 Big moon (base)
    glColor3ub(255,255,255);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(x, y);
        for(int i=0;i<=360;i++)
        {
            double angle = i * 3.1416 / 180;
            glVertex2d(x + cos(angle)*12, y + sin(angle)*12);
        }
    glEnd();

    glColor3ub(10,10,40);   // same as night sky (natural shadow)

    glBegin(GL_TRIANGLE_FAN);
        glVertex2d(x + 5, y + 2);
        for(int i=0;i<=360;i++)
        {
            double angle = i * 3.1416 / 180;
            glVertex2d(x + 5 + cos(angle)*12, y + sin(angle)*12);
        }
    glEnd();
}
//----------------------------------star=========================
void star(float x, float y)
{
    glPointSize(4);
    glColor3ub(255,255,255);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}
//===========================solar light======================

void solarLight(double x, double y)
{
    // pole
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
        glVertex2d(x, y);
        glVertex2d(x+2, y);
        glVertex2d(x+2, y+30);
        glVertex2d(x, y+30);
    glEnd();

    // lamp head
    glColor3ub(50,50,50);
    glBegin(GL_POLYGON);
        glVertex2d(x-3, y+30);
        glVertex2d(x+5, y+30);
        glVertex2d(x+5, y+35);
        glVertex2d(x-3, y+35);
    glEnd();

    // light (ON/OFF)
    if(isNight)
        glColor3ub(255,255,150); // glowing light
    else
        glColor3ub(100,100,100);

    glBegin(GL_TRIANGLES);
        glVertex2d(x-10, y+30);
        glVertex2d(x+10, y+30);
        glVertex2d(x, y+50);
    glEnd();
}

//===============================gear==============================
void gear(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(gearAngle, 0, 0, 1); // Rotate on Z-axis

    // Gear Body
    glColor3ub(255, 215, 0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0, 0);
        for(int i = 0; i <= 360; i++) {
            double angle = (i * 3.1416) / 180;
            glVertex2d(cos(angle) * 10, sin(angle) * 10);
        }
    glEnd();

    // Gear Spokes
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
        for(int i = 0; i < 8; i++) {
            double angle = (i * 3.1416) / 4;
            glVertex2f(0, 0);
            glVertex2d(cos(angle) * 12, sin(angle) * 12);
        }
    glEnd();
    glPopMatrix();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '+': // Zoom In Boat
            scaleFactor += 0.05f;
            break;
        case '-': // Zoom Out Boat
            scaleFactor -= 0.05f;
            if(scaleFactor < 0.2f) scaleFactor = 0.2f;
            break;
        case 'r': // Reset Size
            scaleFactor = 1.0f;
            break;
    }
    glutPostRedisplay();
}
//-----------------------sky------------------------------------------------------------------

void cloud(double x, double y)
{


    glBegin(GL_TRIANGLE_FAN);
        for(i=0;i<360;i++)
        {
            x=x+cos((i*3.14)/180)*r;
            y=y+sin((i*3.14)/180)*r;

            glVertex2d(x,y);

        }


    glEnd();



}

// ------------------------------------Fence-------------------------------------------------
void fence(int x)
{
    glBegin(GL_POLYGON);
        glColor3ub(184,134,11);

        glVertex2i(190-x,130);
        glVertex2i(190-x,70);
        glVertex2i(187-x,70);
        glVertex2i(187-x,130);
        glVertex2i(190-x,130);



    glEnd();

}

//--------------------------------------------------------------------------------------------





void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
//-----------------------sky------------------------------------------------------------------



//-----------------------sky------------------------------------------------------------------
if(isNight)
{
    glColor3ub(10,10,40);   // dark night sky
}
else
{
    glColor3ub(135,206,250); // day sky
}

glRecti(-200,300,200,100);

if(isNight)
{
    if(starBlink % 2 == 0)
    {
        star(-180,260); star(-140,240); star(-100,270);
        star(-60,250);  star(-20,260);  star(20,240);
        star(60,270);   star(100,250);  star(140,260);
        star(170,230);
    }
}

//-----------------------------------field------------------------------
    glBegin(GL_POLYGON);
        glColor3ub(0,100,0);//green

        glVertex2i(-200,100);
        glVertex2i(-100,160);
        glVertex2i(0,100);
        glVertex2i(50,70);
        glVertex2i(100,180);
        glVertex2i(200,100);
        glColor3ub(255,215,0);//gold
        glVertex2i(200,-200);

        glVertex2i(-200,-200);
        glColor3ub(255,215,0);//gold
        glVertex2i(-200,100);

    glEnd();


    windmill(150, 100);


//-------------------SUN-------------------------
  //-------------------==============================SUN-------------------------
if(!isNight)
{
    glColor3ub(255,215,0);
    sun(sx,250);


}
else
{
    moon(mx,250);
}

//-------------------------------------------CLOUD-------------------------------------------------
	glPushMatrix();
	glColor3ub(220,220,220);
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
    tx+=.01;
    if(tx>200)
    tx=-200;

// ------------------------------------fence--------------------------
    int x=0;
    for(int i=0;i<39;i++)
    {
        fence(x);
        x+=10;
    }

    glColor3ub(184,134,11);
    glRecti(-200,120,200,115);
    glRecti(-200,100,200,95);
    glRecti(-200,85,200,80);

    solarLight(-180, 120);
solarLight(-120, 120);
solarLight(-60, 120);
solarLight(0, 120);
solarLight(60, 120);
solarLight(120, 120);


//-------------------------------------TREE------------------------
    glColor3ub(139,69,19);//
    glRecti(-20,200,-13,140);
    glColor3ub(0,100,0);
    sun(-30,190);
    sun(0,190);
    sun(-10,210);
    sun(-30,175);
    sun(-0,170);
    glBegin(GL_POLYGON); // Main Tree // first part
        glColor3ub(139,69,19);//
        glVertex2i(-170,160);
        glVertex2i(-168,120);
        glColor3ub(139,69,19);//
        glVertex2i(-178,40);
        glVertex2i(-145,40);
        glColor3ub(139,69,19);//
        glVertex2i(-153,120);
        glVertex2i(-150,160);
        glVertex2i(-170,160);
    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // second part
        glColor3ub(139,69,19);//
        glVertex2i(-153,100);
        glVertex2i(-100,200);
        glVertex2i(-95,200);
        glVertex2i(-153,80);
        glVertex2i(-153,100);
    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // third part
        glColor3ub(139,69,19);//
        glVertex2i(-170,160);
        glVertex2i(-185,210);
        glVertex2i(-190,210);
        glVertex2i(-168,90);
        glVertex2i(-170,160);

    glEnd();
    glBegin(GL_POLYGON);  // Main Tree // fourth part
        glColor3ub(139,69,19);//
        glVertex2i(-160,160);
        glVertex2i(-150,210);
        glVertex2i(-140,210);
        glVertex2i(-150,160);
        glVertex2i(-160,160);


    glEnd();
    glColor3ub(0,128,0);//leaf
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


//-----------------------------------------------TUBEWELL-----------------------------------------

    glBegin(GL_POLYGON);  // First part

        glColor3ub(0,100,0);//
        glVertex2i(115,65);
        glVertex2i(95,5);
        glVertex2i(145,5);
        glVertex2i(165,65);
        glVertex2i(115,65);

    glEnd();
    glBegin(GL_POLYGON);  // second part

        glColor3ub(143,188,143);//
        glVertex2i(120,58);
        glVertex2i(104,13);
        glVertex2i(140,12);
        glVertex2i(155,58);
        glVertex2i(120,58);

    glEnd();
    glColor3ub(0,0,0);// third part
        glRecti(95,5,145,-6);

    glBegin(GL_POLYGON);  // fourth  part
        glColor3ub(0,0,0);//
        glVertex2i(165,65);
        glVertex2i(166,55);
        glVertex2i(145,-6);
        glVertex2i(145,5);
        glVertex2i(165,65);
    glEnd();
    glBegin(GL_POLYGON);  // tubewell 1st part
        glColor3ub(184,134,11);
        glVertex2i(120,85);
        glVertex2i(120,30);
        glVertex2i(125,28);
        glVertex2i(130,30);
        glVertex2i(130,85);
        glVertex2i(125,87);
        glVertex2i(120,85);
    glEnd();
    glBegin(GL_POLYGON);  // tubewell second part
        glColor3ub(255,215,0);//golden rod
        glVertex2i(120,85);
        glVertex2i(125,80);
        glVertex2i(130,85);
        glVertex2i(125,87);
        glVertex2i(120,85);

    glEnd();
    glColor3ub(205,133,63);//golden rod // tubewell third part
    glRecti(123,100,126,85);

    glBegin(GL_POLYGON);  // tubewell fourth part
        glColor3ub(139,69,19);//saddle brown
        glVertex2i(126,100);
        glVertex2i(128,102);
        glVertex2i(128,110);
        glVertex2i(126,113);
        glVertex2i(124,111);
        glVertex2i(100,80);
        glVertex2i(90,70);
        glVertex2i(90,65);
        glVertex2i(100,73);
        glVertex2i(126,100);
    glEnd();
    glBegin(GL_POLYGON);  // tubewell 5th part
        glColor3ub(210,105,30);//golden rod
        glVertex2i(130,70);
        glVertex2i(140,70);
        glVertex2i(140,50);
        glVertex2i(136,50);
        glVertex2i(136,60);
        glVertex2i(130,60);
        glVertex2i(130,70);

    glEnd();
    glColor3ub(210,105,30);//golden rod //tubewell last part
    glRecti(123,29,127,20);
    glColor3ub(139,69,19);//saddle brown
    glRecti(118,22,132,14);
// --------------------------------------- HOUSE one----------------------------
    glBegin(GL_POLYGON);  // first Part
        glColor3ub(128,0,0);//gray
        glVertex2i(-58,115);
        glVertex2i(-75,145);
        glVertex2i(-115,150);//point
        glVertex2i(-90,100);
        glVertex2i(-62,100);
        glVertex2i(-58,115);

    glEnd();
    glBegin(GL_POLYGON);  // second Part
        glColor3ub(120,0,0);//maroon
        glVertex2i(-115,150);
        glVertex2i(-130,100);
        glVertex2i(-120,100);//point
        glVertex2i(-108,137);//point
        glVertex2i(-115,150);
    glEnd();
    glBegin(GL_POLYGON);  // third Part
        glColor3ub(46,139,87);//
        glVertex2i(-108,137);
        glVertex2i(-120,100);
        glVertex2i(-120,45);
        glVertex2i(-90,40);//point
        glVertex2i(-90,100);
        glVertex2i(-108,137);
    glEnd();


    glBegin(GL_POLYGON);  // fourth Part
        glColor3ub(143,188,143);//
        glVertex2i(-90,40);
        glVertex2i(-60,45);
        glVertex2i(-60,100);
        glVertex2i(-90,100);

    glEnd();
    glColor3ub(120,0,0);//maroon // Door One
        glRecti(-75,80,-65,40);
    glColor3ub(120,0,0);//maroon // Door One
        glRecti(-110,90,-100,70);
    glBegin(GL_POLYGON);  // third Part (lower part 1)
        glColor3ub(0,0,0);//
        glVertex2i(-90,40);
        glVertex2i(-123,45);
        glVertex2i(-123,35);
        glVertex2i(-90,30);
        glVertex2i(-90,40);

    glEnd();
    glBegin(GL_POLYGON);  // third Part (lower part 2)
        glColor3ub(0,0,0);//
        glVertex2i(-90,40);
        glVertex2i(-55,45);
        glVertex2i(-55,35);
        glVertex2i(-90,30);
        glVertex2i(-90,40);


    glEnd();




//-------------------------------------------  HOUSE  two  -------------------------------------------------
    glBegin(GL_POLYGON);  // First part

        glColor3ub(25,25,112);//midnight blue
        glVertex2i(-50,140);
        glVertex2i(0,149);
        glVertex2i(-12,88);
        glVertex2i(-65,89);
        glVertex2i(-50,140);
    glEnd();





    glBegin(GL_POLYGON);  // Second Part
    glColor3ub(70,130,180);//midnight blue
        glVertex2i(-60,90);
        glVertex2i(-60,30);
        glVertex2i(-10,25);
        glVertex2i(-10,95);
    glEnd();


//---------------------------------------Door------------------------------------------
    glColor3ub(25,25,112);//midnight blue
    glRecti(-45,70,-30,27);

//--------------------------------------------------------------------------
    glBegin(GL_POLYGON);   // Third part
    glColor3ub(95,158,160);//midnight blue
        glVertex2i(-10,25);
        glVertex2i(18,35);
        glVertex2i(18,100);
        glVertex2i(0,148);
        glVertex2i(-10,100);
        glVertex2i(-10,25);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(25,25,112);//midnight blue
        glVertex2i(-1,150);
        glVertex2i(20,100);
        glVertex2i(17,90);
        glVertex2i(-4,140);
        glVertex2i(-1,150);

    glEnd();


    glBegin(GL_POLYGON);  // door
    glColor3ub(25,25,112);//midnight blue
        glVertex2i(0,70);
        glVertex2i(10,73);
        glVertex2i(10,32);
        glVertex2i(0,29);
        glVertex2i(0,70);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 1)
        glColor3ub(0,0,0);//
        glVertex2i(-10,25);
        glVertex2i(-10,15);
        glVertex2i(20,27);
        glVertex2i(20,37);
        glVertex2i(-10,25);


    glEnd();
    glBegin(GL_POLYGON);  // (lower part 2)
        glColor3ub(0,0,0);//
        glVertex2i(-10,25);
        glVertex2i(-62,30);
        glVertex2i(-62,20);
        glVertex2i(-10,15);
        glVertex2i(-10,25);




    glEnd();


//------------------------------------------RIVER--------------------------------------------------
    glBegin(GL_POLYGON);

    if(isNight)
{
    // 🌙 NIGHT RIVER (dark + reflection feel)
    glColor3ub(0,0,50);
}
else
{
    // 🌞 DAY RIVER (blue)
    glColor3ub(30,144,255);
}
  glVertex2i(-200,-50);
glVertex2i(200,-30);

glVertex2i(200,-200);
glVertex2i(-200,-200);
glVertex2i(-200,-50);
    glEnd();
    glBegin(GL_POLYGON); // border
        glColor3ub(128,128,0);
        glVertex2i(-200,-45);
        glVertex2i(200,-25);
        glVertex2i(200,-30);
        glVertex2i(-200,-50 );
        glVertex2i(-200,-45);
    glEnd();


//-------------------------------------------BOAT-------------------------------------------------
    glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);//Black
    glTranslatef(bx,0,0);
    glScalef(scaleFactor, scaleFactor, 1.0);
//    drawGear(-120, -85);
    glBegin(GL_POLYGON);
        glVertex2i(-180,-70);
        glVertex2i(-165,-100);
        glVertex2i(-150,-120);
        glVertex2i(-150,-100);
        glVertex2i(-180,-70);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(-150,-100);
        glVertex2i(-150,-120);
        glVertex2i(-120,-125);
        glVertex2i(-90,-120);
        glVertex2i(-85,-100);
        glVertex2i(-150,-100);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2i(-85,-100);
        glVertex2i(-90,-120);
        glVertex2i(-75,-105);
        glVertex2i(-60,-70);
        glVertex2i(-85,-100);
    glEnd();
    glColor3ub(211,211,211);


    //--------------------------BOAT FLAG----------------------------
    glBegin(GL_POLYGON);
        glColor3ub(173,216,230);
        glVertex2i(-57,-40);
        glVertex2i(-50,-10);
        glVertex2i(-49,10);
        glVertex2i(-50,30);
        glVertex2i(-55,45);
        glVertex2i(-63,57);
        glVertex2i(-73,68); // end
        glVertex2i(-105,45);
        glVertex2i(-50,-10);


    glEnd();
    glBegin(GL_POLYGON);
        glColor3ub(173,216,230);

        glVertex2i(-68,-70);
        glVertex2i(-57,-40);
        glVertex2i(-85,10);
        glVertex2i(-68,-70);
    glEnd();
    glBegin(GL_POLYGON);
        glColor3ub(173,216,230);
        glVertex2i(-85,-100);
        glVertex2i(-68,-70);
        glVertex2i(-80,-10);
        glVertex2i(-85,-100);

    glEnd();

    glColor3ub(139,69,19);
    glRecti(-88,80,-86,-100);  // Boat stand
    glBegin(GL_POLYGON);
        glColor3f(0.55,0.27,0.0745);//wood color
        glVertex2i(-85,-100);
        glVertex2i(-87,-80);
        glVertex2i(-93,-62);
        glVertex2i(-97,-55);
        glVertex2i(-105,-50);
        glVertex2i(-120,-48);
        glVertex2i(-120,-100);
        glVertex2i(-85,-100);

    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(0.55,0.27,0.0745);//wood color
        glVertex2i(-150,-100);
        glVertex2i(-148,-80);
        glVertex2i(-142,-62);
        glVertex2i(-138,-55);
        glVertex2i(-130,-50);
        glVertex2i(-115,-48);
        glVertex2i(-115,-100);
        glVertex2i(-150,-100);


    glEnd();

//--------------------------BOAT LINE----------------------------
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        glVertex2i(-142,-62);
        glVertex2i(-73,68);
        glVertex2i(-73,63);

        glVertex2i(-142,-62);
        glVertex2i(-105,45);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        glVertex2i(-148,-80);
        glVertex2i(-87,-80);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        glVertex2i(-142,-62);
        glVertex2i(-93,-62);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        glVertex2i(-115,-48);
        glVertex2i(-115,-100);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        glVertex2i(-130,-50);
        glVertex2i(-130,-100);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glColor3f(0.0f, 0.0f, 0.0f);//Black
        glVertex2i(-100,-52);
        glVertex2i(-100,-100);
    glEnd();

solarAngle += 0.5;
gear(-120,-90);  // ==============================grar function call
    glPopMatrix();



    glutPostRedisplay();
    glColor3ub(255,255,255);//
    glRecti(-210,310,-200,-210);
    glRecti(200,310,210,-210);

    //========================================= Boat movement
bx += 0.03;
if(bx > 270)
    bx = -180;
// ---------------- GEAR ----------------

// ============================================Gear rotation
gearAngle += 0.05;
if(gearAngle > 360)
    gearAngle -= 360;

    starBlink++;

// ======================================SUN movement
if(!isNight)
{
    sx += 0.03;

    if(sx > 200)
    {
        isNight = true;   // sun gone → night start
        mx = 220;         // moon start position reset
    }
}
else
{
    // ==================================MOON movement
    mx -= 0.03;

    if(mx < -220)
    {
        isNight = false;  // reset to day
        sx = -150;
    }
}

//--------------------------------------------------------------------------------------------
    glFlush();
}



int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(1200,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow(" village scenery ");

    init();
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard); // boat control + Rain

    glutMainLoop();
    return 0;
}
