#include <GL/glut.h>

void display(){
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0);
glPointSize(10);
glBegin(GL_POINTS);
glVertex2f(0.0, 0.0);

glEnd();
glFinish();
}


void init() {
glClearColor(0.6, 0.8, 1.0, 1.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

}

int main(int argc, char** argv){

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(300, 300);
glutInitWindowPosition(200, 200);
glutCreateWindow("OpenGL Small Point");
init();
glutDisplayFunc(display);
glutMainLoop();
return 0;

}