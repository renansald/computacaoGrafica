#include <iostream>
#include "CarregarArquivo2.cpp"
using namespace std;

CarregarArquivo boat;
float axisY = 0;
float moveX = 0;
float moveZ = 0;
int type = 0;
GLfloat camX = 0;
GLfloat camZ = 13;

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
    case GLUT_KEY_F1:
        if (camX == 0 && camZ == 13)
        {
            camX = 13;
            camZ = 0;
        }
        else if (camX == 13 && camZ == 0)
        {
            camX = 0;
            camZ = -13;
        }
        else if (camX == 0 && camZ == -13)
        {
            camX = -13;
            camZ = 0;
            break;
        }
        else
        {
            camX = 0;
            camZ = 13;
        }
        break;
    }
    glutPostRedisplay();
}

void lightCamOne(void)
{
    GLfloat enviromentLight[4] = {0.9, 0.9, 0.9, 1};
    GLfloat diffuseLightZ[4] = {0.7, 0.7, 0.7, 1}; // "cor"
    GLfloat specularLightZ[4] = {1, 1, 1, 1};      // "brilho"
    GLfloat lightPosition[4] = {0, 0, 13, 1};
    // Capacidade de brilho do material
    GLfloat specularity[4] = {1.0, 1.0, 1.0, 1.0};
    GLint materialSpecular = 60;
    // Define a reflet�ncia do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
    // Define a concentra��o do brilho
    glMateriali(GL_FRONT, GL_SHININESS, materialSpecular);
    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, enviromentLight);
    // Define os par�metros da luz de n�mero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, enviromentLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightZ);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightZ);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    GLfloat diffuseLightX[4] = {0.2, 0.2, 0.2, 1};  // "cor"
    GLfloat specularLightX[4] = {0.5, 0.5, 0.5, 1}; // "brilho"

    glLightfv(GL_LIGHT1, GL_AMBIENT, enviromentLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLightX);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specularLightX);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);

    glLightfv(GL_LIGHT2, GL_AMBIENT, enviromentLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLightZ);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specularLightZ);
    glLightfv(GL_LIGHT2, GL_POSITION, lightPosition);

    GLfloat diffuseLightOtherX[4] = {0, 0, 0, 0};
    GLfloat specularLightOtherX[4] = {0, 0, 0, 0};

    glLightfv(GL_LIGHT3, GL_AMBIENT, enviromentLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuseLightOtherX);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specularLightOtherX);
    glLightfv(GL_LIGHT3, GL_POSITION, lightPosition);
}

void init(void)
{
    glClearColor(1, 1, 1, 0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, 1, 0.5, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    char fileName[] = "boat.obj";
    boat.Carregar(fileName);
}

void floor(float scale, float high)
{
    glPushMatrix();
    glColor3f(0, 0, 1);
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
            GLfloat nor[3] = {
                (boat.normais[boat.faces[j][i][2]][0]),
                (boat.normais[boat.faces[j][i][2]][1]),
                (boat.normais[boat.faces[j][i][2]][2])};
            glVertex3fv(vert);
            glNormal3fv(nor);
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
            GLfloat nor[3] = {
                (boat.normais[boat.faces[j][i][2]][0]),
                (boat.normais[boat.faces[j][i][2]][1]),
                (boat.normais[boat.faces[j][i][2]][2])};
            glVertex3fv(vert);
            glNormal3fv(nor);
        }
        glEnd();
    }

    glPopMatrix();
}
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glColor3f(0, 0, 1);
    floor(1, -2);
    gluLookAt(camX, 0, camZ, 0, 0, 0, 0, 1, 0);
    glTranslatef(0, 0, moveZ);
    glTranslatef(moveX, 0, 0);
    glRotatef(axisY, 0, 1, 0);
    glColor3f(0, 1, 0);
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
