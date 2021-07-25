#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdbool.h>
//position 0 Header Y
//position 1 Body X
//position 2 Body Y
//position 3 Body Z
//position 4 Left Should X
//position 5 Left Should Y
//position 6 Left Should Z
//position 7 Right Should X
//position 8 Right Should Y
//position 9 Right Should Z
//position 10 Left Elbow Z
//position 11 Right Elbow Z

int bodyPositions[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void rotateIn360(int *ref, int value)
{
  *ref = (*ref + value) % 360;
  glutPostRedisplay();
}

void rotateBetweenAngles(int *ref, int value, int angleBegin, int angleEnd)
{
  int sum = *ref + value;
  if (sum >= angleEnd)
  {
    *ref = angleEnd;
  }
  else if (sum <= angleBegin)
  {
    *ref = angleBegin;
  }
  else
  {
    *ref = sum;
  }
  glutPostRedisplay();
}

void keyboardEvent(unsigned char key, int x, int y)
{
  switch (key)
  {
  case '1':
    rotateBetweenAngles(&bodyPositions[0], 5, -90, 90);
    break;
  case '2':
    rotateBetweenAngles(&bodyPositions[0], -5, -90, 90);
    break;
  case '3':
    rotateIn360(&bodyPositions[1], 5);
    break;
  case '4':
    rotateIn360(&bodyPositions[1], -5);
    break;
  case '5':
    rotateIn360(&bodyPositions[2], 5);
    break;
  case '6':
    rotateIn360(&bodyPositions[2], -5);
    break;
  case '7':
    rotateIn360(&bodyPositions[3], 5);
    break;
  case '8':
    rotateIn360(&bodyPositions[3], -5);
    break;
  case 'q':
    rotateBetweenAngles(&bodyPositions[4], 5, 0, 90);
    break;
  case 'Q':
    rotateBetweenAngles(&bodyPositions[4], -5, 0, 90);
    break;
  case 'w':
    rotateBetweenAngles(&bodyPositions[7], 5, 0, 90);
    break;
  case 'W':
    rotateBetweenAngles(&bodyPositions[7], -5, 0, 90);
    break;
  case 'e':
    rotateBetweenAngles(&bodyPositions[6], 5, -90, 90);
    break;
  case 'E':
    rotateBetweenAngles(&bodyPositions[6], -5, -90, 90);
    break;
  case 'r':
    rotateBetweenAngles(&bodyPositions[9], -5, -90, 90);
    break;
  case 'R':
    rotateBetweenAngles(&bodyPositions[9], 5, -90, 90);
    break;
  case 't':
    rotateBetweenAngles(&bodyPositions[10], 5, 0, 120);
    break;
  case 'T':
    rotateBetweenAngles(&bodyPositions[10], -5, 0, 120);
    break;
  case 'y':
    rotateBetweenAngles(&bodyPositions[11], -5, -120, 0);
    break;
  case 'Y':
    rotateBetweenAngles(&bodyPositions[11], 5, -120, 0);
    break;
  case 'u':
    rotateBetweenAngles(&bodyPositions[5], -5, -90, 90);
    break;
  case 'U':
    rotateBetweenAngles(&bodyPositions[5], 5, -90, 90);
    break;
  case 'i':
    rotateBetweenAngles(&bodyPositions[8], 5, -90, 90);
    break;
  case 'I':
    rotateBetweenAngles(&bodyPositions[8], -5, -90, 90);
    break;
  default:
    break;
  }
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0); //Define a cor de fundo
  glColor3f(0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65, 1, 0.5, 500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 13, 0, 0, 0, 0, 1, 0);
}

void printDot(float r, float g, float b)
{
  glColor3f(r, g, b);
  glPointSize(10);
  glBegin(GL_POINTS);
  glVertex3f(0, 0, 0);
  glEnd();
  glColor3f(0, 0, 1);
}

void printBody()
{
  printDot(0, 0, 0);
  glutWireSphere(2, 10, 10);
}

void printHeader()
{
  glPushMatrix();
  glRotatef((GLfloat)bodyPositions[0], 0, 1, 0);
  glTranslatef(0, 2.5, 0);
  printDot(0, 0, 0);
  glutWireSphere(1, 10, 10);
  glTranslatef(0.5, 0, 1);
  glColor3f(1, 0, 0);
  glutSolidSphere(0.25, 10, 10);
  glTranslatef(-1, 0, 0);
  glutSolidSphere(0.25, 10, 10);
  glTranslatef(0.5, -2.5, -1);
  glPopMatrix();
}

void printPart(float x, float y, float z)
{
  printDot(0, 0, 0);
  glPushMatrix();
  glScalef(x, y, z);
  glutWireCube(1);
  glPopMatrix();
}

void printForearm(int elbow, int ref)
{
  glPushMatrix();
  glTranslatef((1 * ref), 0, 0);
  printDot(0, 0, 0);
  glutWireSphere(0.4, 10, 10);
  glRotated((GLfloat)elbow, 0, 0, 1);
  glTranslatef((0.75 * ref), 0, 0);
  printDot(1, 1, 1);
  printPart(1, 0.3, 0.3);
  glTranslatef((0.5 * ref), 0, 0);
  glutWireSphere(0.20, 10, 10);
  // glTranslatef(((ref * -1) * 1.25), 0, 0);
  glPopMatrix();
}

void printArm(int shouldX, int shouldY, int shouldZ, int elbow, int ref)
{
  glPushMatrix();
  glTranslatef((2 * ref), 0, 0);
  printDot(0, 0, 0);
  glutWireSphere(0.5, 10, 10);
  glRotatef((GLfloat)shouldX, 1, 0, 0);
  glRotatef((GLfloat)shouldY, 0, 1, 0);
  glRotatef((GLfloat)shouldZ, 0, 0, 1);
  glTranslatef((1 * ref), 0, 0);
  printPart(2, 0.6, 0.6);
  printForearm(elbow, ref);
  // glTranslated(((ref * -1) * 1), 0, 0);
  glPopMatrix();
}

void printDraw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef((GLfloat)bodyPositions[1], 1, 0, 0);
  glRotatef((GLfloat)bodyPositions[2], 0, 1, 0);
  glRotatef((GLfloat)bodyPositions[3], 0, 0, 1);
  printBody();
  printHeader();
  printArm(bodyPositions[4], bodyPositions[5],
           bodyPositions[6], bodyPositions[10], 1);
  printArm(bodyPositions[7], bodyPositions[8],
           bodyPositions[9], bodyPositions[11], -1);
  glPopMatrix();
  glutSwapBuffers();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Atividade pratica 02");
  init();
  glutDisplayFunc(printDraw);
  glutKeyboardFunc(keyboardEvent);
  glutMainLoop();
  return 0;
}