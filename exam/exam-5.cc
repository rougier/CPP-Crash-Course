#include <iostream>

struct A { A() {  std::cout << "Hello World" << std::endl; } };
struct A1 : public A { };
struct A2 : public A { };
struct A3 : public A { };
struct A4 : public A { };
struct B : public A1, public A2, public A3, public A4 { };

int main(int argc, char** argv) 
{
    B b;
    return 0; 
}
