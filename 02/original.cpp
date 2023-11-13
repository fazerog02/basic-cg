#include <math.h>
#include <GL/glut.h>
#include <random>

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#define ID_DRAW_CIRCLE 1
#define ID_DRAW_BRACKET 2
#define ID_DRAW_BAR 3

#define BRACKET_NUM 32

int rotateAngle;

GLdouble colors[][3] = {
	{1.0, 0, 0},
	{0, 1.0, 0},
	{0, 0, 1.0},
	{1.0, 1.0, 0},
	{1.0, 0, 1.0},
	{0, 1.0, 1.0},
	{1.0, 1.0, 1.0}
};
GLdouble* ranc;
GLdouble random_colors[BRACKET_NUM][3];

GLdouble* getRandomColor() {
	std::random_device rd;
	return colors[rd() % 7];
}

void display(void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		glCallList(ID_DRAW_BAR);
		glRotated(-20, 0, 0, 1);
		glCallList(ID_DRAW_BAR);
		glRotated(40, 0, 0, 1);
		glCallList(ID_DRAW_BAR);
	glPopMatrix();

	glRotated(rotateAngle, 0, 0, 1);

	for(int i = 0; i < 3; i++) {
		glPushMatrix();
			glColor3d(0.0, 0.0, 0.0);
			glScaled(0.3 + (float)i * 0.2, 0.3 + (float)i * 0.2 ,1);
			glTranslated(0, 0, 0);
			glCallList(ID_DRAW_CIRCLE);
		glPopMatrix();
	}

	glPushMatrix();
		for(int i = 0; i < BRACKET_NUM; i++) {
			glPushMatrix();
				glRotated(360.0 / (float)BRACKET_NUM * (float)i, 0, 0, 1);
				glTranslated(0, 0.7, 0);
				glPushMatrix();
					if(i % 2 == 0) {
						glColor3d(0.0, 0.0, 0.0);
						glBegin(GL_LINE_STRIP);
							glVertex2d(0, 0);
							glVertex2d(0, -0.7);
						glEnd();
					}
					glScaled(0.05, 0.05 ,1);
					glRotated(-1.0 * 360.0 / (float)BRACKET_NUM * (float)i - rotateAngle, 0, 0, 1);

					glColor3d(random_colors[i][0], random_colors[i][1], random_colors[i][2]);
					glCallList(ID_DRAW_BRACKET);
				glPopMatrix();
			glPopMatrix();
		}
	glPopMatrix();

	glutSwapBuffers();
}

void timer(int value) {
	rotateAngle++;

	glutPostRedisplay();
	glutTimerFunc(100 , timer , 0);
}

void buildDisplayList() {
	glNewList(ID_DRAW_CIRCLE,GL_COMPILE);
		double r = 1.0;
		glBegin(GL_LINE_LOOP);
			for(int i = 0; i < 36; i++) {
				int deg = i * 10;
				glVertex3d(r*cos(deg*M_PI/180.0), r*sin(deg*M_PI/180.0), 0);
			}
		glEnd();
	glEndList();

	glNewList(ID_DRAW_BRACKET,GL_COMPILE);
		r = 1.0;
		glBegin(GL_POLYGON);
			for(int i = 0; i < 19; i++) {
				int deg = i * -10;
				glVertex3d(r*cos(deg*M_PI/180.0), r*sin(deg*M_PI/180.0), 0);
			}
		glEnd();
		glColor3d(0.7, 0.7, 0.7);
		glBegin(GL_POLYGON);
			for(int i = 0; i < 19; i++) {
				int deg = i * 10;
				glVertex3d(r*cos(deg*M_PI/180.0), r*sin(deg*M_PI/180.0), 0);
			}
		glEnd();
		glColor3d(0.0, 0.0, 0.0);
		glCallList(ID_DRAW_CIRCLE);
	glEndList();

	glNewList(ID_DRAW_BAR, GL_COMPILE);
	glColor3d(0.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
			glVertex2d(-0.01, 0);
			glVertex2d(0.01, 0);
			glVertex2d(0.01, -2);
			glVertex2d(-0.01, -2);
		glEnd();
	glEndList();
}


int main (int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowSize(400 , 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);

	for(int i = 0; i < BRACKET_NUM; i++) {
		ranc = getRandomColor();
		for(int j = 0; j < 3; j++) random_colors[i][j] = ranc[j];
	}

	glutTimerFunc(100 , timer , 0);

	buildDisplayList();

	rotateAngle = 0;

	glutMainLoop();
	return 0;
}
