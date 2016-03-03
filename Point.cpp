//
// Created by Christopher Corona on 2/24/2016.
//

#include "Point.h"
#include <cmath>

namespace Clustering
{
    unsigned int Point::__idGen = 0;

    Point::Point(int dimension)
    {
        __id = __idGen++;
        __values = new double[dimension];
        __dim = dimension;

        for (int i = 0; i < dimension; ++i)__values[i] = 0.0;
    }

    Point::Point(int dimension, double * dValues)
    {
        __id = __idGen++;
        __values = dValues;
        __dim = dimension;
    }

    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point & point)
    {
        __id = point.__id;
        __dim = point.getDims();
        __values = new double[__dim];

        for(int i = 0; i < __dim; ++i)__values[i] = point.__values[i];
    }

    Point& Point::operator=(const Point & point)
    {
        if(this != &point)
        {
            __id = point.__id;
            delete[] __values;
            __values = point.__values;
            __dim = point.getDims();
        }
        return *this;
    }

    Point::~Point()
    {

    }
    // Accessors & mutators
    int Point:: getId() const {return __id;}

    int Point::getDims() const {return __dim;}

    void Point::setValue(int dimension, double dimValues) {__values[dimension] = dimValues;}

    double Point::getValue(int dimension) const
    {
        if (dimension <= getDims())return __values[dimension];
        else return 0;
    }

    // Functions
    double Point::distanceTo(const Point & point) const
    {
        double distance = 0.0;
        for(int i = 0; i < __dim; ++i)distance = distance + ((__values[i] - point.getValue(i)) * (__values[i] - point.getValue(i)));
        return sqrt(distance);
    }

    const Point Point::operator*(double m) const
    // prevent (p1 * 2) = p2;
    {
        Point *newP = new Point(__dim);
        for (int i = 0; i <__dim; ++i)newP->__values[i] = __values[i] * m;
        return *newP;
    }
    const Point Point::operator/(double d) const
    // p3 = p2 / 2;
    {
        Point *newP = new Point(__dim);
        for (int i = 0; i < __dim; ++i)newP->__values[i] = __values[i] / d;
        return *newP;
    }

    double &Point::operator[](int index) {return __values[index];}

    bool operator==(const Point & point1, const Point & point2)
    {
        bool pass = true;

        if (point1.__id != point2.__id)return false;
        if (point1.__dim != point2.__dim)return false;
        for (int i = 0; i < point1.getDims(); ++i)
        {
            if (point1.__values[i] != point2.__values[i])pass = false;
        }
        return pass;
    }

    bool operator!=(const Point & point1, const Point & point2)
    {
        return !(point1 == point2);
    }

    bool operator<(const Point & point1, const Point & point2)
    {
        if (point1.__dim < point2.__dim)return true;
        if (point1.__dim > point2.__dim)return false;
        for (int i = 0; i < point1.getDims(); ++i)
        {
            if(point1.__values[i] < point2.__values[i])return true;

            else if (point1.__values [i] > point2.__values[i])return false;
        }
        return false;
    }
    bool operator>(const Point & point1, const Point &point2)
    {
        if (point1.__dim > point2.__dim)return true;
        if (point1.__dim < point2.__dim)return false;
        for (int i = 0; i < point1.getDims(); ++i)
        {
            if(point1.__values[i] > point2.__values[i])return true;

            else if (point1.__values [i] < point2.__values[i])return false;
        }
        return false;

    }
    bool operator<=(const Point & point1, const Point & point2)
    {
        if(point1<point2)
        {
            return true;
        }
        if(point1>point2)
        {
            return false;
        }
        return true;
        //return !(point2 > point1);
    }
    bool operator>=(const Point & point1, const Point & point2)
    {
        if(point1>point2)
        {
            return true;
        }
        if(point1<point2)
        {
            return false;
        }
        return true;
        //return !(point1 < point2);
    }

    // Friends
    Point& operator+=(Point & point1, const Point & point2) {
        Point *newP = new Point(point2);
        for (int i = 0; i < point1.__dim; ++i) {
            point1.__values[i] = point1.__values[i] + newP->getValue(i);
        }
        delete newP;
        return point1;
    }

    Point &operator-=(Point & point1, const Point & point2)
    {
        Point *newP = new Point(point2);
        for (int i = 0; i < point1.__dim; ++i)
        {
            point1.__values[i] = point1.__values[i] - newP->getValue(i);
        }
        delete newP;
        return point1;
    }

    // Overloaded operators
    // Members
    Point & Point::operator*=(double m)
    // p *= 6; p.operator*=(6);
    {
        for (int i = 0; i <__dim; ++i)
        {
            __values[i] *= m;
        }
        return *this;
    }

    Point & Point::operator/=(double d)
    {
        for (int i = 0; i < __dim; ++i)
        {
            __values[i] /= d;
        }
        return *this;
    }

    const Point operator+(const Point & point1, const Point & point2)
    {
        Point *newP = new Point(point1);
        *newP += point2;
        return *newP;
    }
    const Point operator-(const Point & point1, const Point & point2) {
        Point *newP = new Point(point1);
        *newP -= point2;
        return *newP;
    }

    std::ostream &operator<<(std::ostream &out, const Point &point1)
    {
        int i =0;
        for(; i<point1.getDims()-1;++i)
        {
            out<< point1.getValue(i);
            out <<", ";
        }
        out << point1.getValue(i);
        return out;
    }

    std::istream &operator>>(std::istream &in, Point &point)
    {
        int index = 0;
        while ((in.peek() != '\n')||(in.peek() != '\r'))
        {
            in >> point[index];
            if((in.peek() == '\n')||(in.peek() != '\r')|| (in.eof()))
            {
                return in;
            }
            in.ignore();
            index++;
        }
        return in;
    }
 }