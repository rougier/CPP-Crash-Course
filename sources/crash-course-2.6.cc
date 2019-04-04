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

int main( int argc, char **argv )
{
    int i1 = 1;
    int i2 = 2;

    int const *p1 = &i1;
    int *const p2 = &i1;
    int const * const p3 = &i1;

    p1 = &i2;    // OK
    // *p1 = 2;  // WRONG

    // p2 = &i2;  // WRONG
    *p2 = 2;      // OK

    // p3 = &i2;  // WRONG
    // *p3 = 2;   // WRONG

    // To have no warning at compilation for unused variables
    if( p3 == p2 ) { };

    return 0;
}
