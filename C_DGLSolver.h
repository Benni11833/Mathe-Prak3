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
	void EulerVerfahren(double x_start, double x_end, int anz_Schritte, CMyVektor y_start) {
		double h{ (x_end - x_start) / anz_Schritte };
		for (int i = 0; i < anz_Schritte; i++) {
			std::cout << "Schritt " << i << std::endl
				<< "\t x = " << x_start << std::endl
				<< "\t y = "; y_start.print_vals();
			std::cout << std::endl << "\ty' = "; ableitungen(y_start, x_start).print_vals();
			std::cout << std::endl << std::endl;
			y_start = y_start + (ableitungen(y_start, x_start) * h);	x_start += h;
		}
		std::cout << "Ende bei " << std::endl
			<< "\tx = " << x_start << std::endl
			<< "\ty = "; y_start.print_vals();
	}
};