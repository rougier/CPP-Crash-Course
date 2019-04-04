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
#include <typeinfo>
#include <exception>

class Foo
{ virtual void method( void ) { } };

class Bar : public Foo
{ };

void unexpected( void )
{ throw; }

void function( void ) throw( int, std::bad_exception )
{ throw 'x'; }


int main( int argc, char **argv )
{

    // Bad alloc
    try
    {
        int * array = new int[-1];
        int i = 0;
        i = array[0];
    }
    catch( std::bad_alloc & e )
    {
        std::cerr << "bad_alloc caught: " << e.what() << std::endl;
    }

    // Bad cast
    try
    {
        Foo f;
        Bar & b = dynamic_cast<Bar &>( f );
    }
    catch( std::bad_cast & e )
    {
        std::cerr << "bad_cast caught: " << e.what() << std::endl;
    }

    // Bad exception
    std::set_unexpected( unexpected );
    try {
        function();
    }
    catch( int )
    {
        std::cerr << "caught int" << std::endl;
    }
    catch( std::bad_exception e )
    {
        std::cerr << "bad_exception caught " << e.what() << std::endl;
    }

    return 0;
}
