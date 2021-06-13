#define _USE_MATH_DEFINES
#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>

int obj = 0;

void eventKeyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '1':
    obj = 1;
    return;
  case '2':
    obj = 2;
    return;
  case '3':
    obj = 3;
    return;
  case '4':
    obj = 4;
    return;
  case '5':
    obj = 5;
    return;
  case '6':
    obj = 6;
    return;
  case '7':
    obj = 7;
    return;
  default:
    glutPostRedisplay();
  }
}

void questaoUmEDois(int deslocamentoX, int deslocamentoY)
{
  int posicoes[6][2] = {{1, 1}, {6, 1}, {6, 5}, {3, 3}, {1, 6}, {1, 1}};
  glColor3f(1, 0, 0); // cor da caneta
  glLoadIdentity();
  glOrtho(0, 20, 0, 20, -1, 1);
  if (deslocamentoX > 0 || deslocamentoY > 0)
  {
    glColor3f(0, 0, 1); // cor da caneta
    glTranslatef(deslocamentoX, deslocamentoY, 0);
  }
  glBegin(GL_POLYGON);
  for (int count = 0; count < 6; count++)
  {
    int x = posicoes[count][0];
    int y = posicoes[count][1];
    glVertex2f(x, y);
  }
  glEnd();
}

void questaoTresEQuatro(float translateX, float translateY, float scaleX, float scaleY,
                        float rotateAnglo, float rotateX, float rotateY, float rotateZ)
{
  int posicoes[5][2] = {{2, 1}, {6, 1}, {6, 2}, {2, 2}, {2, 1}};
  glColor3f(0.5, 0.5, 0.5);
  glLoadIdentity();
  glOrtho(-15, 15, -10, 10, -1, 1);
  if (translateX > 0 || translateY > 0)
  {
    glTranslatef(translateX, translateY, 0);
  }
  if (scaleX > 0 || scaleY > 0)
  {
    glScalef(scaleX, scaleY, 0);
  }
  if (rotateAnglo > 0 || rotateX > 0 || rotateY > 0 || rotateZ > 0)
  {
    glRotatef(rotateAnglo, rotateX, rotateY, rotateZ);
  }
  glBegin(GL_POLYGON);
  for (int count = 0; count < 5; count++)
  {
    float x = posicoes[count][0];
    float y = posicoes[count][1];
    glVertex2f(x, y);
  }
  glEnd();
}

void questaoCinco()
{
  double x, y;
  glColor3f(1, 1, 0.5);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, -1, 1);
  glBegin(GL_POLYGON);
  for (double t = 0; t <= M_PI * 2; t += 0.2)
  {
    x = 0 + 2 * cos(t);
    y = 0 + 5 * sin(t);
    glVertex2f(x, y);
  }
  glEnd();
}

void questaoSeis()
{
  int pontos[4][2] = {{0, 2}, {1, -2}, {3, 0}, {4, 3}};
  glColor3b(1, 0, 1);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -1, 1);
  glBegin(GL_LINE_STRIP);
  for (float t = 0.0; t < 1; t += 0.05)
  {
    float x = pow((1 - t), 3) * pontos[0][0] + 3 * t * pow((1 - t), 2) * pontos[1][0] + 3 * pow(t, 2) * (1 - t) * pontos[2][0] + pow(t, 3) * pontos[3][0];
    float y = pow((1 - t), 3) * pontos[0][1] + 3 * t * pow((1 - t), 2) * pontos[1][1] + 3 * pow(t, 2) * (1 - t) * pontos[2][1] + pow(t, 3) * pontos[3][1];
    glVertex2f(x, y);
  }
  glEnd();
}

void questaoSete()
{
  int ponto[4][2] = {{0, 1}, {1, 0}, {0, 0}, {0, 1}};
  glColor3b(1, 0, 1);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -1, 1);
  glBegin(GL_POLYGON);
  for (int count = 0; count < 4; count++)
  {
    glVertex2f(ponto[count][0], ponto[count][1]);
  }
  glEnd();
}
void PrintDraw(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0); //Define a cor de fundo
  glClear(GL_COLOR_BUFFER_BIT);
  if (obj == 1)
    questaoUmEDois(0, 0);
  if (obj == 2)
    questaoUmEDois(6, 2);
  if (obj == 3)
    questaoTresEQuatro(-1, -1, 2, 2, 0, 0, 0, 0);
  if (obj == 4)
    questaoTresEQuatro(0, 0, 0, 0, 45, 0, 0, 1);
  if (obj == 5)
    questaoCinco();
  if (obj == 6)
    questaoSeis();
  if (obj == 7)
    questaoSete();
  glFlush();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutInitWindowSize(600, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Lista 01");
  glutDisplayFunc(PrintDraw);
  glutKeyboardFunc(eventKeyboard);
  glutMainLoop();
  return 0;
}