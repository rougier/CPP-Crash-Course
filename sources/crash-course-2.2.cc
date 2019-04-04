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
    const size_t n = 2;
    int **array = new int *[n]; 

    for( size_t i=0; i<n; ++i )
        array[i] = new int[n];

    for( size_t i=0; i<n; ++i )
        for( size_t j=0; j<n; ++j )
            array[i][j] = i*n+j;

    for( size_t i=0; i<n; ++i )
        for( size_t j=0; j<n; ++j )
            std::cout << "array[" << i << "," << j << "] = "
                      << array[i][j] << std::endl;

    for( size_t i=0; i<n; ++i )
        delete [] array[i];
    delete [] array;
}
