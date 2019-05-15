#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

class CMyVektor{
private:
    unsigned int dimension_;
    std::vector<double> zeile_;
public:
    CMyVektor(unsigned int dimension)
    :dimension_{dimension}{
		zeile_.resize(dimension);
    }
	~CMyVektor() {
		zeile_.erase(zeile_.begin(), zeile_.end());
	}
    unsigned int getDimension()const{
        return dimension_;
    }
    const double operator[](int index)const{
        if(index >= 0 && index <= dimension_)
            return zeile_[index];
        else
            std::cerr << "Dimension ueberschritten." << std::endl;
    }
    double& operator[](int index){
        if(index >= 0 && index <= dimension_)
            return zeile_[index];
        else
            std::cerr << "Dimension ueberschritten." << std::endl;
    }
    double getLen()const{
        long double sum{0};
        for(unsigned int i=0; i < dimension_; i++)
            sum += pow(zeile_[i], 2);
        return sqrt(sum);
    }
    void print()const{
        for(unsigned int i=0; i < dimension_; i++){
			std::cout << std::setw(5) << zeile_[i];
            if(i%10 == 0 && i!=0)
                std::cout << std::endl;
        }
         std::cout << std::endl;
    }
	void print_vals()const {
		std::cout << "(";
		for (int i = 0; i < getDimension(); i++)
			std::cout << zeile_[i] << "; ";
		std::cout << ")" << std::endl;
	}
    friend CMyVektor operator+(CMyVektor a, CMyVektor b);
    friend CMyVektor operator*(double lambda, CMyVektor a);
	friend void operator+=(CMyVektor& a, const CMyVektor& b);
};

CMyVektor operator+(CMyVektor a, CMyVektor b){
	if (a.getDimension() != b.getDimension()) {
		std::cerr << "Vektoren haben nicht die gleiche Dimension." << std::endl;
	}
	else {
		CMyVektor erg{ a.getDimension() };
		for (unsigned int i = 0; i < a.getDimension(); i++)
			erg[i] = b.zeile_[i] + a.zeile_[i];
	return erg;
	}
    
}

CMyVektor operator*(double lambda, CMyVektor a){
    for(unsigned int i=0; i < a.getDimension(); i++)
        a.zeile_[i] *= lambda;
    return a;
}

void operator+=(CMyVektor& a, const CMyVektor& b) {
	a = a + b;
}