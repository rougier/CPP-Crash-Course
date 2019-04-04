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
#include <cmath>


class Real {
public:
    Real( float value = 0 ) : _value(value) { };
    virtual Real operator+(Real &other) { return Real(_value + other._value); }
    virtual Real operator-(Real &other) { return Real(_value - other._value); }
    virtual Real operator*(Real &other) { return Real(_value * other._value); }
    virtual Real operator/(Real &other) { return Real(_value / other._value); }
    friend std::ostream& operator<< ( std::ostream& output, Real const & that )
    { return output << that._value; }
protected:
    float _value;
};

class Integer : public Real {
public:
    Integer( int value = 0 ) : Real(int(round(value))) { };
protected:
    int _value;
};



int main( int argc, char **argv )
{
    Real r1(1.23), r2(4.56);
    Integer i1(1), i2(2);

    std::cout << i1+i2 << " " << std::endl;
    std::cout << r1+r2 << " " << std::endl;
    std::cout << r1+i2 << " " << std::endl;
    std::cout << i1+r2 << " " << std::endl;

    return 0;
}
