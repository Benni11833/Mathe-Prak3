#include "C_DGLSolver.h"

double function1_1(CMyVektor y, double x) {
	return 2 * y[1] - x * y[0];
}

double function1_2(CMyVektor y, double x) {
	return y[0] * y[1] - 2 * pow(x, 3);
}

CMyVektor function1_ges(CMyVektor y, double x) {
	CMyVektor tmp{ 2 };
	tmp[0] = function1_1(y, x);
	tmp[1] = function1_2(y, x);
	return tmp;
}

int main() {

	CMyVektor y_start{ 2 };
	y_start[0] = 0;	y_start[1] = 1;

	C_DGLSolver tmp (function1_ges);
	tmp.EulerVerfahren(0, 2, 100, y_start);
	//function1_ges(y_start, 0).print_vals();


	system("pause");
	return 0;
}