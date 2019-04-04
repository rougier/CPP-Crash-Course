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

void swap_ref( int & a, int & b )
{
    int c = a;
    a = b;
    b = c;
}

void swap_ptr( int * a, int * b )
{
    int c = *a;
    *a = *b;
    *b = c;
}

void swap_ref_ptr( int * & a, int * & b )
{
    int *c = a;
    a = b;
    b = c;
}

int main( int argc, char **argv )
{
    int i1 = 1;
    int i2 = 2;
    int * p1 = &i1;
    int * p2 = &i2;

    std::cout << "i1 = " << i1 << ", " << "i2 = " << i2 << std::endl;
    swap_ref(i1,i2);
    std::cout << "i1 = " << i1 << ", " << "i2 = " << i2 << std::endl;
    std::cout << std::endl;

    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;
    swap_ptr(p1,p2);
    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;
    std::cout << std::endl;

    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;
    swap_ref_ptr(p1,p2);
    std::cout << "*p1 = " << *p1 << ", " << "*p2 = " << *p2 << std::endl;

    return 0;
}
