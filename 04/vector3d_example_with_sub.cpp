#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <GL/glut.h>

using namespace std;

// 3�����x�N�g�����������߂̃N���X
class Vector3d {
public:
	double x, y, z;
	Vector3d() { x = y = z = 0; }
	Vector3d(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
	void set(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }

	// ������1�ɐ��K������
	void normalize() {
		double len = length();
		x /= len; y /= len; z /= len;
	}

	// ������Ԃ�
	double length() { return sqrt(x * x + y * y + z * z); }

	// s�{����
	void scale(const double s) { x *= s; y *= s; z *= s; }

	// ���Z�̒�`
	Vector3d operator+(Vector3d v) { return Vector3d(x + v.x, y + v.y, z + v.z); }

	// ���Z�̒�`
	// �����Z�̒�`���Q�l�ɁA���Z�̃R�[�h���L�q���Ă݂�
	// ### new program start ###
	Vector3d operator-(Vector3d v) { return Vector3d(x - v.x, y - v.y, z - v.z); }
	// ### new program end ###

	// ���ς̒�`
	double operator*(Vector3d v) { return x * v.x + y* v.y + z * v.z; }

	// �O�ς̒�`
	Vector3d operator%(Vector3d v) { return Vector3d(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

	// ������Z�̒�`
	Vector3d& operator=(const Vector3d& v){ x = v.x; y = v.y; z = v.z; return (*this); }

	// ���Z����̒�`
	Vector3d& operator+=(const Vector3d& v) { x += v.x; y += v.y; z += v.z; return (*this); }

	// ���Z����̒�`
	// �����Z����̒�`���Q�l�ɁA���Z����̃R�[�h���L�q���Ă݂�
	// ### new program start ###
	Vector3d operator-=(const Vector3d& v) { x -= v.x; y -= v.y; z -= v.z; return (*this); }
	// ### new program end ###

	// �l���o�͂���
	void print() { printf("Vector3d(%f %f %f)\n", x, y, z); }
};

// �}�C�i�X�̕����̕t�����x�N�g����������悤�ɂ��邽�߂̒�` ��Fb=(-a); �̂悤�ɋL�q�ł���
Vector3d operator-( const Vector3d& v ) { return( Vector3d( -v.x, -v.y, -v.z ) ); }

// �x�N�g���Ǝ����̐ς�������悤�ɂ��邽�߂̒�` ��F c=5*a+2*b; c=b*3; �̂悤�ɋL�q�ł���
Vector3d operator*( const double& k, const Vector3d& v ) { return( Vector3d( k*v.x, k*v.y, k*v.z ) );}
Vector3d operator*( const Vector3d& v, const double& k ) { return( Vector3d( v.x*k, v.y*k, v.z*k ) );}

// �x�N�g���������Ŋ��鑀���������悤�ɂ��邽�߂̒�` ��F c=a/2.3; �̂悤�ɋL�q�ł���
Vector3d operator/( const Vector3d& v, const double& k ) { return( Vector3d( v.x/k, v.y/k, v.z/k ) );}


int main(int argc, char**argv) {
	// ### new program start ###
	// �x�N�g���̉��Z�̗�
	Vector3d a(2, 3, 4);
	Vector3d b(3, 5, -2);
	Vector3d c(2, -1, 1);

	// (a)
	printf("(a) ");
	(a - b).print();

	// (b)
	printf("(b) ");
	Vector3d a3 = a;
	a3.scale(3);
	Vector3d b2 = b;
	b2.scale(2);
	(a3 - b2).print();

	// (c)
	printf("(c) ");
	printf("%lf\n", a * b);

	// (d)
	printf("(d) ");
	Vector3d d = a % b;
	d.normalize();
	d.print();

	// (e)
	printf("(e) ");
	((a + b2) % c).print();
	// ### new program end ###

	// Visual Studio �ŃR���\�[���������ɕ��Ȃ��悤�ɂ��邽�߂ɂ͎��̃R�����g�A�E�g���͂���
	//system("pause");
	return 0;
}

