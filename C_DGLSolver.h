#include "CMyVektor.h"

class C_DGLSolver{
private:
    CMyVektor (*function1)(CMyVektor y, double x);
	double (*function2)(CMyVektor y, double x);
	bool DGL_first_order;
    CMyVektor ableitungen(CMyVektor y, double x){
        if(DGL_first_order){    //DGL erster Ordnung
           return function1(y, x);
        }else{  //Hoeherere ordnung umformen....
            //Subs durchfuehren
           CMyVektor y_new{y.getDimension()};
           for(int i=0; i < y.getDimension()-1; i++)
                y_new[i] = y[i+1];
		   y_new[y.getDimension() - 1] = function2(y, x);
		   return y_new;
        }
    }
public:
    C_DGLSolver(CMyVektor (*f_DGL_System)(CMyVektor y, double x)){
        DGL_first_order = true;
		function1 = f_DGL_System;
    }
    C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x)){
        DGL_first_order = false;
		function2 = f_DGL_nterOrdnung;
    }
	CMyVektor EulerVerfahren_abweichung(double x, double x_end, int anz_Schritte, CMyVektor y) {
		double h{ (x_end - x) / anz_Schritte };
		for (int i = 0; i < anz_Schritte; i++) {
			y += (h * ableitungen(y, x));	x += h;
		}
		return y;
	}
	CMyVektor EulerVerfahren(double x, double x_end, int anz_Schritte, CMyVektor y) {
		double h{ (x_end - x) / anz_Schritte };
		for (int i = 0; i < anz_Schritte; i++) {
			std::cout << "Schritt " << i << std::endl
				<< "\t x = " << x << std::endl
				<< "\t y = "; y.print_vals();
			std::cout << "\ty' = "; ableitungen(y, x).print_vals();
			std::cout << std::endl << std::endl;
			y += (h * ableitungen(y, x));	x += h;
		}
		std::cout << "Ende bei " << std::endl
			<< "\tx = " << x << std::endl
			<< "\ty = "; y.print_vals();
		return y;
	}
	CMyVektor HeunVerfahren_abweichung(double x, double x_end, int anz_Schritte, CMyVektor y) {
		double h{ (x_end - x) / anz_Schritte };
		CMyVektor y_mittel{ y.getDimension() }, y_test{ y.getDimension() };

		for (int i = 0; i < anz_Schritte; i++) {
			y_test = y + (h * ableitungen(y, x));
			y_mittel = 0.5 * (ableitungen(y, x) + ableitungen(y_test, x + h));
			y += h * y_mittel;	x += h;
		}
		return y;
	}
	CMyVektor HeunVerfahren(double x, double x_end, int anz_Schritte, CMyVektor y) {
		double h{ (x_end - x) / anz_Schritte };
		CMyVektor y_mittel{ y.getDimension() }, y_test{ y.getDimension() };
		
		for (int i = 0; i < anz_Schritte; i++) {
			y_test = y + (h * ableitungen(y, x));
			y_mittel = 0.5 * (ableitungen(y, x) + ableitungen(y_test, x+h));
			std::cout << "Schritt " << i << std::endl
				<< "\t x = " << x << std::endl
				<< "\t y = "; y.print_vals();
			std::cout << "\ty'_orig = "; ableitungen(y, x).print_vals();
			std::cout << "\ty_Test = ";  y_test.print_vals();
			std::cout << "\ty'_Test = "; ableitungen(y_test, x+h).print_vals();
			std::cout << "\ty'_Mittel = "; y_mittel.print_vals();
			std::cout << std::endl << std::endl;
			y += h * y_mittel;	x += h;
		}
		std::cout << "Ende bei " << std::endl
			<< "\tx = " << x << std::endl
			<< "\ty = "; y.print_vals();
			
		return y;
	}
};