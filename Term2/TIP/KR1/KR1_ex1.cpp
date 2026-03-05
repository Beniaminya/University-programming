#include <iostream>
#include <cmath>
using namespace std;

class Triangle{
    public:
    double a,b,c;
    bool exst_tr(){
        if ((a + b > c) && (a + c > b) && (b + c > a)){
            return true;
        }
        else return false;
    }

    void set(double a1, double b1, double c1){
        a = a1;
        b = b1;
        c = c1;
    }

    void show(){
        cout << "A = " << a << ", B = " << b << ", C = " << c << '\n';
    }

    double perimetr(){
        return a + b + c;
    }
    double square(){
        double p = perimetr()/2;
        return sqrt(p*(p-a)*(p-b)*(p-c)); 
    }
};

#include "main1_1.cpp"