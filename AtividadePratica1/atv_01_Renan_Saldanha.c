#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>

int obj = 0;
float redColor[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
float blueColor[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
float greenColor[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int screenMapper(int x, int y)
{
  return ((3 * (y / 100)) + (y / 100) + (x / 100));
}

void eventMouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    int viewPort = screenMapper(x, y);
    redColor[viewPort] = (float)(rand() % 10) / 10;
    blueColor[viewPort] = (float)(rand() % 10) / 10;
    greenColor[viewPort] = (float)(rand() % 10) / 10;
    glutPostRedisplay();
  }
}

void printForm(float red, float green, float blue)
{
  float ponto[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, 1}};
  glColor3f(red, green, blue);
  glLoadIdentity();
  glBegin(GL_POLYGON);
  for (int count = 0; count < 4; count++)
  {
    glVertex2f(ponto[count][0], ponto[count][1]);
  }
  glEnd();
}
void PrintDraw(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  for (int line = 0; line < 4; line++)
  {
    for (int column = 0; column < 4; column++)
    {
      glViewport((column * 100), (line * 100), 100, 100);
      printForm(redColor[(12 - (line * 4) + column)], greenColor[(12 - (line * 4) + column)], blueColor[(12 - (line * 4) + column)]);
    }
  }
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  srand(time(NULL));
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Atividade pratica 01");
  glClearColor(1.0, 1.0, 1.0, 1.0); //Define a cor de fundo
  glutDisplayFunc(PrintDraw);
  glutMouseFunc(eventMouse);
  glutMainLoop();
  return 0;
}