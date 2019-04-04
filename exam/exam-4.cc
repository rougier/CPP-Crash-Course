#include <iostream>

struct A { unsigned int color; };
struct B : public A { };
struct C : public A { };
struct D : public B, public C { };

int main(int argc, char** argv) 
{ 
//    D d;
//    d.color = 3;
//    std::cout << d.color << std::endl;
    return 0; 
}
