#include<iostream>
using namespace std;
class shape{
public:
virtual double area()=0;
virtual double perimeter()=0;
virtual ~shape() = default;

};