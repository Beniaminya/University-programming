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

    double get_a(){
        return a;
    }

    double get_b(){
        return b;
    }
    double get_c(){
        return c;
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

class Circle{
    public:
    float r,x,y;

    Circle (float r, float x, float y){
        this -> r = r;
        this -> x = x;
        this -> y = y;
    }
    
    void set_circle (float r, float x, float y){
        this -> r = r;
        this -> x = x;
        this -> y = y;
    }

    float square(){
        const double PI = 3.14159265358979323846;
        return PI*r*r;
    }

    bool triangle_around (Triangle & t){
        double s = t.square();
        double a = t.get_a();
        double b = t.get_b();
        double c = t.get_c();
        return (r == (a*b*c)/(4*s));
    }

    bool triangle_in (Triangle & t){
        double pol = t.perimetr()/2;
        double s = t.square();
        return ((s/pol) == r);
    }

    bool check_circle (Circle &c){
        float x1 = c.x;
        float y1 = c.y;
        float x2 = x;
        float y2 = y;
        float r1 = c.r;
        float r2 = r;
        return ((r1+r2) > sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1))) && (sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1)) > abs(r-c.r));
    }
};

#include "main1_4.cpp"
