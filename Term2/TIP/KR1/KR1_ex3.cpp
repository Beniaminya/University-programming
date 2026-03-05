#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

class Triangle{
    public:
    double a,b,c;
    Triangle(double a, double b, double c){
        this-> a = a;
        this-> b = b;
        this-> c = c;
        if(!exst_tr()){
            this ->a = 3;
            this ->b = 4;
            this ->c = 5;
        }
    }

    bool exst_tr(){
        if ((a + b > c) && (a + c > b) && (b + c > a)){
            return true;
        }
        else return false;
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
	bool is_similar(Triangle & t2){
    	double arr1[3]{a,b,c};
        double arr2[3]{t2.a, t2.b, t2.c};
        sort(arr1, arr1+3);
        sort(arr2, arr2+3);
        double k1 = arr1[0]/arr2[0];
        double k2 = arr1[1]/arr2[1];
        double k3 = arr1[2]/arr2[2];
        return (k1 == k2 && k2 == k3);
    }
};

#include "main1_3.cpp"