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
#include <stdexcept>
#include <cmath>

struct DivideByZero : public std::runtime_error
{ DivideByZero( void ) : std::runtime_error("DivideByZero") { } };

struct OverflowError : public std::runtime_error
{ OverflowError( void ) : std::runtime_error("OverflowError") { } };

struct UnderflowError : public std::runtime_error
{ UnderflowError( void ) : std::runtime_error("UnderflowError") { } };


class Integer {
public:
    Integer( int value = 0 ) : _value(value) { };

    virtual Integer operator+(Integer &other)
    {
        unsigned char result = _value+other._value;
        if( result < _value )
        { throw new OverflowError; }
        return Integer(result);
    }

    virtual Integer operator-(Integer &other)
    {
        unsigned char result = _value-other._value;
        if( result > _value )
        { throw new UnderflowError; }
        return Integer(result);
    }

    virtual Integer operator*(Integer &other)
    {
        unsigned char result = _value * other._value;
        if((_value > 1) and (other._value >1 ) and ( result < _value ))
        { throw new OverflowError; }
        return Integer(result);
    }

    virtual Integer operator/(Integer &other)
    {
        if( other._value == 0 )
        { throw new DivideByZero; }

        return Integer(_value / other._value);
    }

    friend std::ostream& operator<< ( std::ostream& output, Integer const & that )
    { return output << that._value; }
protected:
    unsigned char _value;
};

int main( int argc, char **argv )
{
    Integer a(129), b(128), zero(0);

    Integer c(a+b); // overflow
    Integer c(b-a); // underflow
    Integer c(a/zeor); // divide by zero

    return 0;
}
