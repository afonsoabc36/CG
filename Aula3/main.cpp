#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

// Camera position in spherical coordinates
float camRadius = 5.0f;
float camTheta = M_PI / 4;
float camPhi = M_PI / 4;

void changeSize(int w, int h) {
    if (h == 0)
        h = 1;
    float ratio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawCylinder(float radius, float height, int slices) {
    float angle;
    float step = (2.0f * M_PI) / slices;

    // SIDES
    glBegin(GL_LINES);
    for (int i = 0; i < slices; ++i) {
        angle = i * step;
        float x1 = radius * cos(angle);
        float z1 = radius * sin(angle);
        float x2 = radius * cos(angle + step);
        float z2 = radius * sin(angle + step);

        // Draw lines for the first triangle
        glVertex3f(x1, height / 2.0, z1);
        glVertex3f(x1, -height / 2.0, z1);

        glVertex3f(x1, -height / 2.0, z1);
        glVertex3f(x2, height / 2.0, z2);

        glVertex3f(x2, height / 2.0, z2);
        glVertex3f(x1, height / 2.0, z1);

        // Draw lines for the second triangle
        glVertex3f(x1, -height / 2.0, z1);
        glVertex3f(x2, -height / 2.0, z2);

        glVertex3f(x2, -height / 2.0, z2);
        glVertex3f(x2, height / 2.0, z2);

        glVertex3f(x2, height / 2.0, z2);
        glVertex3f(x1, -height / 2.0, z1);
    }
    glEnd();

    // TOP AND BOTTOM
    glBegin(GL_LINES);
    for (int i = 0; i < slices; ++i) {
        angle = i * step;
        float x1 = radius * cos(angle);
        float z1 = radius * sin(angle);
        float x2 = radius * cos(angle + step);
        float z2 = radius * sin(angle + step);

        // Top base
        glVertex3f(0.0, height / 2.0, 0.0);
        glVertex3f(x1, height / 2.0, z1);

        glVertex3f(x1, height / 2.0, z1);
        glVertex3f(x2, height / 2.0, z2);

        glVertex3f(x2, height / 2.0, z2);
        glVertex3f(0.0, height / 2.0, 0.0);

        // Bottom base
        glVertex3f(0.0, -height / 2.0, 0.0);
        glVertex3f(x1, -height / 2.0, z1);

        glVertex3f(x1, -height / 2.0, z1);
        glVertex3f(x2, -height / 2.0, z2);

        glVertex3f(x2, -height / 2.0, z2);
        glVertex3f(0.0, -height / 2.0, 0.0);
    }
    glEnd();
}


void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camRadius * sin(camPhi) * cos(camTheta), camRadius * cos(camPhi), camRadius * sin(camPhi) * sin(camTheta),
              0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);

    drawCylinder(0.75, 2, 20);

    glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy) {
    float deltaTheta = 0.1f;
    float deltaPhi = 0.1f;
    if (key == 'w') {
        camPhi -= deltaPhi;
        if (camPhi < 0.1f)
            camPhi = 0.1f;
    } else if (key == 's') {
        camPhi += deltaPhi;
        if (camPhi > M_PI - 0.1f)
            camPhi = M_PI - 0.1f;
    } else if (key == 'a') {
        camTheta -= deltaTheta;
    } else if (key == 'd') {
        camTheta += deltaTheta;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
    // Additional special key handling can be added here if needed
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glutMainLoop();

    return 1;
}