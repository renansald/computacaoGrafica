#include <iostream>
#include "CarregarArquivo2.cpp"
using namespace std;

CarregarArquivo boat;
float axisY = 0;
float moveX = 0;
float moveZ = 0;
int type = 0;

void keyboardEvents(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_END:
        axisY--;
        break;
    case GLUT_KEY_HOME:
        axisY++;
        break;
    case GLUT_KEY_RIGHT:
        moveX++;
        break;
    case GLUT_KEY_LEFT:
        moveX--;
        break;
    case GLUT_KEY_UP:
        moveZ++;
        break;
    case GLUT_KEY_DOWN:
        moveZ--;
        break;
    }
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, 1, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 13, 0, 0, 0, 0, 1, 0);
    char fileName[] = "boat.obj";
    boat.Carregar(fileName);
}

void floor(float scale, float high)
{
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(0, high, 0);
    glScalef(scale, scale, scale);
    glBegin(GL_QUADS);
    glVertex3f(100, 0, 100);
    glVertex3f(-100, 0, 100);
    glVertex3f(-100, 0, -100);
    glVertex3f(100, 0, -100);
    glEnd();
    glPopMatrix();
}

void boatWireFrame(void)
{
    glPushMatrix();
    for (unsigned int j = 0; j < (boat.faces).size(); ++j)
    {
        glBegin(GL_LINE_LOOP);
        for (unsigned int i = 0; i < (boat.faces[j]).size(); ++i)
        {
            GLfloat vert[3] = {
                (boat.vertices[boat.faces[j][i][0]][0]),
                (boat.vertices[boat.faces[j][i][0]][1]),
                (boat.vertices[boat.faces[j][i][0]][2])};
            glVertex3fv(vert);
        }
        glEnd();
    }
    glPopMatrix();
}

void boatSolid(void)
{
    glPushMatrix();

    for (unsigned int j = 0; j < (boat.faces).size(); ++j)
    {
        glBegin(GL_POLYGON);
        for (unsigned int i = 0; i < (boat.faces[j]).size(); ++i)
        {
            GLfloat vert[3] = {
                (boat.vertices[boat.faces[j][i][0]][0]),
                (boat.vertices[boat.faces[j][i][0]][1]),
                (boat.vertices[boat.faces[j][i][0]][2])};
            glVertex3fv(vert);
        }
        glEnd();
    }

    glPopMatrix();
}
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    floor(1, -2);
    glPushMatrix();
    glTranslatef(0, 0, moveZ);
    glTranslatef(moveX, 0, 0);
    glRotatef(axisY, 0, 1, 0);
    glColor3f(0, 0, 0);
    glScalef(2, 2, 2);
    if (type > 0)
    {
        boatSolid();
    }
    else
    {
        boatWireFrame();
    }
    glPopMatrix();
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    printf("Digite 0 para wireframe\nou digite 1 para solido\n");
    scanf("%d", &type);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Boat");

    init();

    glutDisplayFunc(draw);

    glutSpecialFunc(keyboardEvents);

    glutMainLoop();
    return 0;
}
