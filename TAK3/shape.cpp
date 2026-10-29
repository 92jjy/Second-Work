#include<iostream>
#include "shape.hpp"
#include<cmath>
using namespace std;
class triangle : public shape {
private:
    double a, b, c;
public:
    triangle(double a_, double b_, double c_) {
        this->a=a_;
        this->b=b_;
        this->c=c_;
    }
    
    double perimeter()  override {
        return a + b + c;
    }
    
    double area()  override {
        // 使用海伦公式计算三角形面积
        double p = perimeter() / 2.0;
       return sqrt(p * (p - a) * (p - b) * (p - c)); 
     }
    };


class rectangle : public shape {
private:
    double length, width;
public:
    rectangle(double l, double w)  {
        this->length=l;
        this->width=w; 
    }

    double perimeter() override {
        return 2 *(length + width);
    }

    double area()  override {
        return length * width;
    }
};

class circle : public shape {
private:
    double r;
public:
    circle(double r_) {
        this->r=r_;
    }

    double perimeter()  override {
        return 2 * M_PI * r;
    }

    double area() override {
        return M_PI * r * r;
    }
};


int main(){
triangle s(3.0,4.0,5.0);
    cout<<"三角形周长为 "<<s.perimeter()<<endl;
    cout<<"三角形面积为 "<<s.area()<<endl;
rectangle r(4.0, 3.0);
    cout << "矩形周长为 " << r.perimeter() << endl;
    cout << "矩形面积为 " << r.area() << endl;
circle c(2.0);
    cout << "圆形周长为 " << c.perimeter() << endl;
    cout << "圆形面积为 " << c.area() << endl;
    
    return 0;
}