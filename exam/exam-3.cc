#include <iostream>
using namespace std;

void swap1( int  a, int  b ) { int c=a; a=b; b=c; }
void swap2( int *a, int *b ) { int c=*a; *a=*b; *b=c; }
void swap3( int &a, int &b ) { int &c=a; a=b; b=c; }

int main( int argc, char **argv )
{
    int a, b;

    a = 1; b = 2; swap1(a,b);
    cout << "a: " << a << ", " <<"b: " << b << endl;

    a = 1; b = 2; swap2(&a,&b);
    cout << "a: " << a << ", " <<"b: " << b << endl;

    a = 1; b = 2; swap3(a,b);
    cout << "a: " << a << ", " <<"b: " << b << endl;
}
