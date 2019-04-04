#include <iostream>

int main(int argc, char** argv)
{
    long x[50];
    // A // memset(x, 0, 50);
    // B // memset(x, 0, sizeof(x));
    // C // memset(x, 0, 50 * 4);
    // D // memset(x, 0, 50 * sizeof(x));

    std::cout << "sizeof(x): " << sizeof(x) << std::endl;
    memset(x, 0, sizeof(x));
 }
