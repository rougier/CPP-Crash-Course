/*
 * Copyright (C) 2012 Nicolas P. Rougier
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either  version 3 of the  License, or (at your  option) any later
 * version.
 *
 * This program is  distributed in the hope that it will  be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR  A  PARTICULAR PURPOSE.  See  the GNU  General  Public  License for  more
 * details.
 *
 * You should have received a copy  of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>

class Foo {
private:
    int _value;


public:
    Foo( int value = 0 ) : _value(value) 
    {
        std::cout << "Foo default constructor called" << std::endl;
    }

    Foo( const Foo & other )
    {
        std::cout << "Foo copy constructor called" << std::endl;
    }

    Foo & operator= ( const Foo &other )
    {
        std::cout << "Foo operator = called" << std::endl;

        // Gracefully handle self assignment
        if( this == &other ) return *this;
        
        _value = other._value;
        return *this;
    }
 
   ~Foo( void )
    {
        std::cout << "Foo destructor called" << std::endl;
    }
};

int main( int argc, char **argv )
{
    Foo foo_1(2);
    Foo foo_2(foo_1);
    Foo foo_3;
    foo_3 = foo_1;
    
    return 0;
}
