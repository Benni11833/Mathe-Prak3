#include "CMyVektor.h"

class C_DGLSolver{
private:
    CMyVektor (*function)(CMyVektor y, double x);
    bool DGL_first_order;
    CMyVektor ableitungen(CMyVektor y, double x){
        if(DGL_first_order){    //DGL erster Ordnung
           return function(y, x);
        }else{  //Hoeherere ordnung umformen....
            //Subs durchfuehren
           CMyVektor y_new{y.getDimension()};
           for(int i=0; i < y.getDimension()-1; i++)
            if(i == y.getDimension()-2)
                //function
                ;
            else
                y_new[i] = y[i+1];
        }
    }
public:
    C_DGLSolver(CMyVektor (*f_DGL_System)(CMyVektor y, double x)){
        DGL_first_order = true;
    }
    C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x)){
        DGL_first_order = false;
    }
};