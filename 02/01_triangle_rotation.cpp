#include <math.h>
#include <GL/glut.h> // ���C�u�����p�w�b�_�t�@�C���̓ǂݍ���

int rotateAngle; // ��]�p�x���L�^���Ă����ϐ�

// �\�����������̊֐��ŋL��
void display(void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);  // �����F�w��
	glClear(GL_COLOR_BUFFER_BIT);       // ��ʂƉ��s������������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotated(rotateAngle, 0, 0, 1);

	glColor3d(1.0, 0.0, 0.0);   // �F�w��(R,G,B)��0�`1�܂�
	glBegin(GL_TRIANGLES);
	    glVertex3d(0,     0, 0);
	    glVertex3d(0.5,   0, 0);
	    glVertex3d(0.5, 0.5, 0);
	glEnd();

	glutSwapBuffers(); // �o�b�t�@�̓���ւ�
}

// ��莞�Ԃ��ƂɌĂяo�����֐�
void timer(int value) {
	rotateAngle++; // ��]�p�x�̍X�V

	glutPostRedisplay(); // �ĕ`�施��
	glutTimerFunc(100 , timer , 0); // 100�~���b��Ɏ��g�����s����
}


// ���C���v���O����
int main (int argc, char *argv[]) {
	glutInit(&argc, argv);          // ���C�u�����̏�����
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowSize(400 , 400);  // �E�B���h�E�T�C�Y���w��
	glutCreateWindow(argv[0]);      // �E�B���h�E���쐬
	glutDisplayFunc(display);       // �\���֐����w��

	glutTimerFunc(100 , timer , 0); // 100�~���b��Ɏ��s����֐��̎w��

	rotateAngle = 0;                // �ϐ��̏����l�̐ݒ�

	glutMainLoop();                 // �C�x���g�҂�
	return 0;
}
