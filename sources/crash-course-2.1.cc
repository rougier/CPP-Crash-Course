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
int main( int argc, char **argv )
{
    // Pointer to a char
    char * p1 = new char;

    // A constant pointer to a char
    char * const p2 = p1;

    // A pointer to a constant char
    const char * p3 = p1;

    // A constant pointer to a constant char
    const char * const p4 = p2;
    
    // A reference to a char
    char & r1 = *p2;

    // A reference to a constant char:
    const char & r2 = *p4;

    // To have no warning at compilation for unused variables
    if( *p3 == r1 ) { }
    if( *p3 == r2 ) { }

}
