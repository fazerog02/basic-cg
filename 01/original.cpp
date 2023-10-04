#include <GL/glut.h>
#include <complex>

#define DIVERGENCE_CHECK_LOOP_NUM 20
#define DIVERGENCE_CHECK_THRESHOLD 2.0

#define DRAW_STEP 0.005


bool doesIncludedInMandelBlotSet(std::complex<float> c) {
	std::complex<float> z(0.0, 0.0);
	for(int i = 0; i < DIVERGENCE_CHECK_LOOP_NUM; i++) {
		if(abs(z) > DIVERGENCE_CHECK_THRESHOLD) return false;
		z = z * z + c;
	}
	return true;
}


void display(void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT);

	glColor3d(0.0, 0.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for(float x = -1; x < 1; x += DRAW_STEP) {
		for(float y = -1; y < 1; y += DRAW_STEP) {
			std::complex<float> c(x, y);
			if(doesIncludedInMandelBlotSet(c)) glVertex2d(x, y);
		}
	}
	glEnd();

	glFlush();
}

int main (int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(400 , 400);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
