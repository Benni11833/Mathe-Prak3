#include "C_DGLSolver.h"

double function1_1(CMyVektor y, double x) {
	return 2 * y[1] - x * y[0];
}

double function1_2(CMyVektor y, double x) {
	return y[0] * y[1] - 2 * pow(x, 3);
}

CMyVektor function1_ges(CMyVektor y, double x) {
	CMyVektor tmp{ y.getDimension() };
	tmp[0] = function1_1(y, x);
	tmp[1] = function1_2(y, x);
	return tmp;
}

double function2_ges(CMyVektor y, double x) {
	return 2 * x*y[1] * y[2] + 2 * pow(y[0], 2)*y[1];
}

int main() {

	/*CMyVektor y_start{ 2 };
	y_start[0] = 0;	y_start[1] = 1;*/

	CMyVektor y_start{ 3 };
	y_start[0] = 1;	y_start[1] = -1;	y_start[2] = 2;

	C_DGLSolver tmp{ function2_ges };
	tmp.HeunVerfahren(0, 2, 100, y_start);

	system("pause");
	return 0;
}