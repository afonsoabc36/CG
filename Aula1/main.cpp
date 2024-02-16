#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

float cupRotation = 0;

void changeSize(int w, int h)
{
	// prevent a divide by zero, when window is too short
	// (you can not make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;

	// set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// et the viewport to be the entire window
	glViewport(0, 0, w, h);
}


void renderScene(void) {
    // Clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set camera
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,
              0.0f, 0.0f, -1.0f,
              0.0f, 1.0f, 0.0f);

    // Calculate scale factor based on time
    float timeSinceStart = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Time in seconds
    float scaleFactor = sin(timeSinceStart) * 0.5f + 1.5f; // Oscillate between 1.0 and 2.0

    // Apply scaling
    glPushMatrix(); // Save current transformation state
    glScalef(scaleFactor, scaleFactor, scaleFactor); // Scale the teapot

    glRotatef(cupRotation,0.0f,1.0f,0.0f);
    // Draw the teapot
    glutWireTeapot(1.0);
    cupRotation += 1.0f;

    glPopMatrix(); // Restore previous transformation state

    // End of frame
    glutSwapBuffers();
}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}


int main(int argc, char** argv)
{
	// put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1400,800);
    glutCreateWindow("CG@DI");
	
    
	// put callback registry here
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);


	
	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    printInfo();
	
	// enter GLUTs main cycle
	glutMainLoop();
	
	return 1;
}