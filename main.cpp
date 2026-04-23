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
int starBlink = 0;
float solarAngle = 0;

bool isRaining = false;
float rainX[200], rainY[200];

float manX = -200;
float womanX = -120;
float childX = -50;

float scaleFactor = 1.0f;
bool scaleUp = true;
float gearAngle = 0.0f;

// DDa algorithom
void DDA(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for(int i = 0; i <= steps; i++)
    {
        glVertex2f(x, y);
        x += xInc;
        y += yInc;
    }
    glEnd();
}

// mid point
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

    // ⭐ ADD THIS (IMPORTANT)
    glEnable(GL_POINT_SMOOTH);
    glPointSize(4);
    glPointSize(2.0);

    // rain
    for(int i=0;i<200;i++)
{
    rainX[i] = rand()%400 - 200;
    rainY[i] = rand()%300;
}
}

// _________Windmaill
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


//-----------------------sky------------------------------------------------------------------

//-----------------------cloud-----------------------------------------------------------------
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



void moon(double x, double y)
{
    glPushMatrix();

    glColor3ub(255,255,255); // pure white moon

    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(x, y);

    for(i=0;i<=360;i++)
    {
        double angle = (i * 3.1416) / 180;
        glVertex2d(x + cos(angle)*15,
                   y + sin(angle)*15);
    }
    glEnd();

    glPopMatrix();
}

void star(float x, float y)
{
    glColor3ub(255,255,255);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}

//__________solar light
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

// Walikin path
void walkingPath()
{
    glColor3ub(245,245,245);

    // main path
    DDA(-200, -20, 200, -20);

    // side border lines
    glColor3ub(200,200,200);
    DDA(-200, -25, 200, -25);
    DDA(-200, -15, 200, -15);
}

// human
void drawHuman(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);

    // Body
    glColor3ub(0,0,0);
    glRecti(-3, 10, 3, 30);

    // Head
    glColor3ub(255,220,177);
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0;i<=360;i++)
        {
            float a = i * 3.1416 / 180;
            glVertex2f(cos(a)*5, 35 + sin(a)*5);
        }
    glEnd();

    // Arms
    glColor3ub(0,0,0);
    glBegin(GL_LINES);
        glVertex2i(-3,25); glVertex2i(-8,18);
        glVertex2i(3,25);  glVertex2i(8,18);
    glEnd();

    // Legs
    glBegin(GL_LINES);
        glVertex2i(-2,10); glVertex2i(-5,0);
        glVertex2i(2,10);  glVertex2i(5,0);
    glEnd();

    glPopMatrix();
}


// -------------Gear ________________________

void gear(double x, double y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(gearAngle, 0, 0, 1);

    // 🔵 Outer circle
    glColor3ub(255,215,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0,0);
    for(int i=0;i<=360;i++)
    {
        double angle = (i * 3.1416) / 180;
        glVertex2d(cos(angle)*10, sin(angle)*10);
    }
    glEnd();

    // ⚫ Spokes (rotation visible hobe)
    glColor3ub(0,0,0);
    glBegin(GL_LINES);

    for(int i=0;i<8;i++) // 8 ta line
    {
        double angle = (i * 3.1416) / 4;

        glVertex2f(0,0);
        glVertex2d(cos(angle)*10, sin(angle)*10);
    }

    glEnd();

    glPopMatrix();
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

// rain
void drawRain()
{
    if(!isRaining) return;

    glColor3ub(173,216,230);

    glBegin(GL_LINES);
    for(int i=0;i<200;i++)
    {
        glVertex2f(rainX[i], rainY[i]);
        glVertex2f(rainX[i], rainY[i]-10);

        rainY[i] -= 4;

        if(rainY[i] < -200)
            rainY[i] = 300;
    }
    glEnd();
}


// dram man
void drawMan()
{
    glPushMatrix();
    glTranslatef(manX, -20, 0);   // path position

    // Body
    glColor3ub(0,0,0);
    glRecti(-3, 10, 3, 30);

    // Head (simple circle)
    glColor3ub(255,220,177);
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0;i<=360;i++)
        {
            float a = i * 3.1416 / 180;
            glVertex2f(cos(a)*5, 35 + sin(a)*5);
        }
    glEnd();

    // Legs (walking effect)
    glBegin(GL_LINES);
        glVertex2i(-2,10);
        glVertex2i(-5,0);

        glVertex2i(2,10);
        glVertex2i(5,0);
    glEnd();

    // Arms
    glBegin(GL_LINES);
        glVertex2i(-3,25);
        glVertex2i(-8,18);

        glVertex2i(3,25);
        glVertex2i(8,18);
    glEnd();

    glPopMatrix();
}


//-------------------------Boat scelaing control-------------------------------------------------------------------

//---------------- KEYBOARD ONLY BOAT ----------------
void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '+':   // zoom in
            scaleFactor += 0.05f;
            break;

        case '-':   // zoom out
            scaleFactor -= 0.05f;
            if(scaleFactor < 0.2f) scaleFactor = 0.2f; // limit
            break;

        case 'r':   // reset size
            scaleFactor = 1.0f;
            break;
    }

        switch(key)
    {
        case 's':   // rain ON
            isRaining = true;
            break;

        case 't':   // rain OFF
            isRaining = false;
            break;
    }
}


void display()
{

    glClear(GL_COLOR_BUFFER_BIT);
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
if(!isNight)
{
    glColor3ub(255,215,0);
    sun(sx,250);


}
else
{
    moon(mx,250);
}
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

drawMan();
drawHuman(manX, -20);
drawHuman(womanX, -25);
drawHuman(childX, -30);

walkingPath();
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

if(isNight)
{
    glColor3ub(0,0,30);
}
else
{
    glColor3ub(0,0,128);
}

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
//-------------------------------------------BOAT-------------------------------------------------
    glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);//Black
    glTranslatef(bx,0,0);
    glScalef(scaleFactor, scaleFactor, 1.0);
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

if(isNight && isRaining)
{
    glColor3ub(80, 80, 120); // dark rain mood
}
drawRain();

solarAngle += 0.5;
gear(-120,-90);

    glPopMatrix();



    glutPostRedisplay();
    glColor3ub(255,255,255);//
    glRecti(-210,310,-200,-210);
    glRecti(200,310,210,-210);

    // Boat movement
bx += 0.03;
if(bx > 270)
    bx = -180;

// Gear rotation
gearAngle += 1.0;
if(gearAngle > 360)
    gearAngle -= 360;

// star blink animation
starBlink++;

// SUN movement
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
    // MOON movement
    mx -= 0.03;

    if(mx < -220)
    {
        isNight = false;  // reset to day
        sx = -150;
    }
}

// man
manX += 0.05;
if(manX > 200) manX = -200;

// woman (slow)
womanX += 0.03;
if(womanX > 200) womanX = -200;

// child (fast)
childX += 0.04;
if(childX > 200) childX = -200;
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

    glutKeyboardFunc(keyboard); // boat control

    glutMainLoop();
    return 0;
}
