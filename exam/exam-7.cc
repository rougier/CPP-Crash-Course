#include <iostream>

int main(int argc, char** argv)
{
    int x = 0;
    int y = 0;

    if (x++ && y++)
    {
        y += 2;
    }

    std::cout << x + y << std::endl;

    return 0;
}
