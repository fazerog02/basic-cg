#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define OUTPUT_FILENAME "parametric_surface_ex_01.obj" // 出力ファイル名
#define PI 3.1415926535

#define NUM_U 50  // U方向の分割数
#define NUM_V 50  // V方向の分割数

#define INNER_R 0.3
#define OUTER_R 1.0

double x[NUM_U+1][NUM_V+1]; // x 座標
double y[NUM_U+1][NUM_V+1]; // y 座標
double z[NUM_U+1][NUM_V+1]; // z 座標

// 配列に座標値を設定する
void setCoordinates() {

	for(int i = 0; i < NUM_U+1; i++) {
		for(int j = 0; j < NUM_V+1; j++) {

			// u と v の値を 0.0 ～ 1.0 に正規化する
			double u = 2.0 * PI / NUM_U * i;
			double v = 2.0 * PI / NUM_V * j;

			// 座標値の設定 ★ 以下の例ではz=0の平面になる
			x[i][j] = OUTER_R * cos(u) + INNER_R * cos(u) * cos(v);
			y[i][j] = OUTER_R * sin(u) + INNER_R * sin(u) * cos(v);
			z[i][j] = INNER_R * sin(v);
		}
	}
}

// OBJ 形式でのファイルの出力
void exportOBJ() {
	FILE *fout;

	// 出力用ファイルを開く
	//---------------------------
	fout = fopen(OUTPUT_FILENAME, "w");
	if(fout == NULL) {
		printf("Error: fopen\n");
		exit(0);
	}
	
	
	// Visual Studio で上記ではうまくいかない場合次のものに置き換える
/*
	// 出力用ファイルを開く
	//---------------------------
	if(0 != fopen_s(&fout, OUTPUT_FILENAME, "w") ) {
		printf("Error: fopen \n");
		exit(0);
	}
*/	

	// 頂点情報の出力
	//---------------------------
	for(int i = 0; i < NUM_U+1; i++) {
		for(int j = 0; j < NUM_V+1; j++) {
			// 各頂点の座標値を出力する
			fprintf(fout, "v %f %f %f\n", x[i][j], y[i][j] , z[i][j]); 
		}
	}

	// 面情報の出力
	/*
    	★ 面情報を出力するには、以下のコメントアウトを外する
	*/
	//---------------------------
	for(int i = 0; i < NUM_U + 1; i++) {
		for(int j = 0; j < NUM_V + 1; j++) {
			// それぞれの格子に対して2つの三角形を出力する
			
			// OBJ形式では頂点番号は1から始まる
		    int lb_index = (i * NUM_U + j) % (NUM_U * NUM_V);
			int lt_index = (lb_index + 1) % (NUM_U * NUM_V);
			int rb_index = (lb_index + NUM_U) % (NUM_U * NUM_V);
			int rt_index = (lt_index + NUM_U) % (NUM_U * NUM_V);

			// 三角形を構成する頂点番号を出力
			fprintf(fout, "f %d %d %d\n", lb_index, rt_index, lt_index); 
			fprintf(fout, "f %d %d %d\n", lb_index, rb_index, rt_index);
		}
	}

	// 出力用ファイルを閉じる
	//---------------------------
	fclose(fout);
}

int main(int argc, char** argv) {
	setCoordinates();
	exportOBJ();
	return 0;
}