#include <math.h>
#include <GL/glut.h> // ���C�u�����p�w�b�_�t�@�C���̓ǂݍ���

// �萔�΂̒�`
#ifndef M_PI
#define M_PI 3.14159265358979
#endif

// �f�B�X�v���C���X�g�̊w�K
// ����`�悷��`�施�߈ꎮ���A�f�B�X�v���C���X�g�Ƃ��č쐬���Ă���
// �K�v�Ȏ��ɁA���̖��߂��Ăяo��

#define ID_DRAW_STAR 1 //  glNewList �֐��Ŏg�p���鎯��ID�B�l�͉��ł��\��Ȃ�

int rotateAngle; // ��]�p�x���L�^���Ă����ϐ�

// �\�����������̊֐��ŋL��
void display(void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);  // �����F�w��
	glClear(GL_COLOR_BUFFER_BIT);       // ��ʂƉ��s������������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotated(rotateAngle, 0, 0, 1);

	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	glTranslated(0.5, 0, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);
	glTranslated(0, 0.5, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glPopMatrix();

	glPushMatrix();
	glColor3d(0.0, 0.0, 1.0);
	glTranslated(-0.5, 0, 0);
	glRotated(rotateAngle, 0, 0, 1);
	glCallList(ID_DRAW_STAR);
	glPopMatrix();

	glutSwapBuffers(); // �o�b�t�@�̓���ւ�
}

// ��莞�Ԃ��ƂɌĂяo�����֐�
void timer(int value) {
	rotateAngle++; // ��]�p�x�̍X�V

	glutPostRedisplay(); // �ĕ`�施��
	glutTimerFunc(100 , timer , 0); // 100�~���b��Ɏ��g�����s����
}

// �f�B�X�v���C���X�g���쐬����
void buildDisplayList() {
	glNewList(ID_DRAW_STAR,GL_COMPILE);

	double r0 = 0.15; // ���̓��a
	double r1 = 0.4; // ���̊O�a
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 5; i++) { // 5�̎O�p�`�Ő���\������
		int deg = i * 72;
		glVertex3d(r0 * cos( (deg - 36) * M_PI / 180.0), r0 * sin( (deg - 36) * M_PI / 180.0), 0);  // �����̒��_
		glVertex3d(r1 * cos( deg * M_PI / 180.0), r1 * sin( deg * M_PI / 180.0), 0);  // �O���̒��_
		glVertex3d(r0 * cos( (deg + 36) * M_PI / 180.0), r0 * sin( (deg + 36) * M_PI / 180.0) ,0);  // �����̒��_
	}
	glEnd();

	glEndList();
}


// ���C���v���O����
int main (int argc, char *argv[]) {
	glutInit(&argc, argv);          // ���C�u�����̏�����
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowSize(400 , 400);  // �E�B���h�E�T�C�Y���w��
	glutCreateWindow(argv[0]);      // �E�B���h�E���쐬
	glutDisplayFunc(display);       // �\���֐����w��

	glutTimerFunc(100 , timer , 0); // 100�~���b��Ɏ��s����֐��̎w��

	buildDisplayList();

	rotateAngle = 0;                // �ϐ��̏����l�̐ݒ�

	glutMainLoop();                 // �C�x���g�҂�
	return 0;
}
