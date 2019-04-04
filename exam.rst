.. sectnum::

===============================================================================
C++ exam
===============================================================================

Name:


.. :Author: `Nicolas P. Rougier <http://www.loria.fr/~rougier>`_
.. :Sources: `exam.rst <exam.rst>`_
.. Most questions comes from http://www.mycppquiz.com/


Extern
===============================================================================

The code below declares and defines variable x. **True** or **False** ?

.. code:: c++

   extern int x;


Namespace
===============================================================================
In namespace foo, the function bar can access the variable x also declared in
namespace foo ? **True** or **False** ?

.. code:: c++

   #include <iostream>

   namespace foo
   {
       void bar()
       {
           x++;
       }
       int x;
   }

   int main(int argc, char** argv)
   {
       return 0;
   }


References
===============================================================================
What is the output of the following program ?

.. code:: c++

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


Inheritance
===============================================================================
What is the output of the program ?

.. code:: c++

 #include <iostream>

 struct A { unsigned int color; };
 struct B : public A { };
 struct C : public A { };
 struct D : public B, public C { };

 int main(int argc, char** argv) 
 { 
    D d;
    d.color = 3;
    std::cout << d.color << std::endl;
    return 0; 
 }

Inheritance
===============================================================================
How many times is "Hello World" printed by this program ?

.. code:: c++

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


Initialization
===============================================================================
What is the value of x, y & z ?

.. code:: c++

 #include <iostream>

 struct A
 {
   A(int n) : x(n++), y(n++), z(n++) {}
   int x;
   int y;
   int z;
 };

 int main(int argc, char** argv)
 {
   Foo f(3);

   std::cout << "x: " << f.x << std::endl;
   std::cout << "y: " << f.y << std::endl;
   std::cout << "z: " << f.z << std::endl;

   return 0;
 }


Logic
===============================================================================
What value gets printed by the program?

.. code:: c++

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

Constructors
===============================================================================
Which lines below should not compile ? 

.. code:: c++

 struct A
 {
    A(int x) : n(x) {}
    int n;
 };

 int main(int argc, char** argv)
 {
   A a1;
   A a2(2);
   A a3(a2);
   return 0;
 }



Memory
===============================================================================
Which of the following implementations of the reset function is best for
initializing the array to all zero.

.. code:: c++

 class foo{
 public:
     foo(){
         reset();
     }
 private:
     void reset(){
 
     // A // memset(x, 0, 50);
     // B // memset(x, 0, sizeof(x));
     // C // memset(x, 0, 50 * 4);
     // D // memset(x, 0, 50 * sizeof(x));
     }

     long x[50];
 };


References
===============================================================================
What is the output of the program ?

.. code:: c++

 #include <iostream>

 int main(int argc, char** argv) 
 { 
   // assume address of x is 0x822222222
   int x = 3;

   int*& rpx = &x;

   std::cout << rpx << std::endl;
  
   return 0; 
 }


End
===============================================================================
