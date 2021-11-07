#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CarregarArquivo2.cpp"
#include <math.h>
using namespace std;

CarregarArquivo boat;

GLubyte textura[256][256][3];
GLuint textura_id;
GLubyte textura2[256][256][3];
GLuint textura_id2;

int rotate = 0;
float obsZ = 0;
int type = 0;
float transX = 0.0;
float transZ = 0.0;
float posYMeteoro = 0;
float posXMeteoro = 0;
float posZMeteoro = 0;
struct timespec t0;

void light(void)
{
    GLfloat luzAmbiente[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0};
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat posicaoLuz[4] = {0.0, 0.0, 13.0, 1.0};
    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
    GLint especMaterial = 60;
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}

void specialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        rotate = (rotate - 1) % 360;
        if (rotate < 0)
        {
            rotate = 360 + rotate;
        }
        break;
    case GLUT_KEY_RIGHT:
        rotate = (rotate + 1) % 360;
        break;
    case GLUT_KEY_UP:
        transX += sin(rotate * M_PI / 180);
        transZ += cos(rotate * M_PI / 180);
        break;
    case GLUT_KEY_F1:
        if (type)
        {
            type = 0;
        }
        else
        {
            type = 1;
        }
    }

    glutPostRedisplay();
}

void idle()
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    if (posYMeteoro > 0)
    {
        if ((now.tv_sec - t0.tv_sec) > 5)
        {
            posYMeteoro = posYMeteoro - 0.5;
        }
    }
    else
    {
        posXMeteoro = rand() % 100;
        if (posXMeteoro > 50)
        {
            posXMeteoro = 50 - posXMeteoro;
        }
        posZMeteoro = rand() % 100;
        if (posZMeteoro > 50)
        {
            posZMeteoro = 50 - posZMeteoro;
        }
        posYMeteoro = 20;
        clock_gettime(CLOCK_REALTIME, &t0);
    }
    glutPostRedisplay();
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65, 1, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    char file[] = "boat.obj";
    boat.Carregar(file);
    printf("Load ok");
    try
    {
        ifstream arq("textureSea.bmp", ios::binary);
        char c;
        if (!arq)
            cout << "Erro ao abrir";

        for (int i = 0; i < 54; i++)
            c = arq.get();
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
            {
                c = arq.get();
                textura[i][j][2] = c;
                c = arq.get();
                textura[i][j][1] = c;
                c = arq.get();
                textura[i][j][0] = c;
            }

        arq.close();
        arq.clear();
    }
    catch (...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
    glGenTextures(1, &textura_id);
    printf("%d", textura_id);

    glBindTexture(GL_TEXTURE_2D, textura_id);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, textura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    try
    {
        ifstream arq("textureLeaf.bmp", ios::binary);
        char c;
        if (!arq)
            cout << "Erro ao abrir";

        for (int i = 0; i < 54; i++)
            c = arq.get();
        for (int i = 0; i < 256; i++)
            for (int j = 0; j < 256; j++)
            {
                c = arq.get();
                textura2[i][j][2] = c;
                c = arq.get();
                textura2[i][j][1] = c;
                c = arq.get();
                textura2[i][j][0] = c;
            }

        arq.close();
        arq.clear();
    }
    catch (...)
    {
        cout << "Erro ao ler imagem" << endl;
    }
    glGenTextures(1, &textura_id2);
    printf("%d", textura_id2);

    glBindTexture(GL_TEXTURE_2D, textura_id2);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, textura2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void floor(float scale, float high)
{
    glColor3f(0.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura_id);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glPushMatrix();
    glTranslatef(0.0, high, 0.0);
    glScalef(scale, scale, scale);
    glBegin(GL_POLYGON);
    glNormal3f(0, -1, 0);
    glTexCoord2f(0, 0);
    glVertex3f(100.0, 0.0, 100.0);
    glTexCoord2f(10, 0);
    glVertex3f(-100.0, 0.0, 100.0);
    glTexCoord2f(10, 10);
    glVertex3f(-100.0, 0.0, -100.0);
    glTexCoord2f(0, 10);
    glVertex3f(100.0, 0.0, -100.0);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void BoatSolid()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura_id2);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    for (unsigned int j = 0; j < (boat.faces).size(); ++j)
    {
        glBegin(GL_POLYGON);
        for (unsigned int i = 0; i < (boat.faces[j]).size(); ++i)
        {
            GLfloat vert[3] = {(boat.vertices[boat.faces[j][i][0]][0]), (boat.vertices[boat.faces[j][i][0]][1]), (boat.vertices[boat.faces[j][i][0]][2])};
            GLfloat nor[3] = {(boat.normais[boat.faces[j][i][2]][0]), (boat.normais[boat.faces[j][i][2]][1]), (boat.normais[boat.faces[j][i][2]][2])};
            GLfloat tex[2] = {boat.texturas[boat.faces[j][i][1]][0], boat.texturas[boat.faces[j][i][1]][1]};
            glNormal3fv(nor);
            glTexCoord2fv(tex);
            glVertex3fv(vert);
        }
        glEnd();
    }

    glPopMatrix();
}
void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if (type == 0)
    {
        gluLookAt(0, 100, 13, 0, 0, 0, 0, 1, 0);
    }
    else
    {
        gluLookAt((transX - 8 * sin(rotate * M_PI / 180)), 5, (transZ - 8 * cos(rotate * M_PI / 180)), transX, 0, transZ, 0, 1, 0);
    }
    light();
    floor(1.0, -3.0);
    glPushMatrix();
    glTranslatef(transX, 0, transZ);
    glRotatef(rotate, 0, 1, 0);
    glColor3f(0.0, 1.0, 0.0);
    glScalef(2.0, 2.0, 2.0);
    BoatSolid();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(posXMeteoro, posYMeteoro, posZMeteoro);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();

    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    srand(time(NULL));

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowSize(800, 800);

    glutInitWindowPosition(0, 0);

    glutCreateWindow("Computacao Grafica: ATV_final");

    init();

    glutDisplayFunc(draw);

    glutSpecialFunc(specialKeyboard);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
