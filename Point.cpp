//
// Created by Christopher Corona on 2/24/2016.
//

#include "Point.h"
#include "Cluster.h"

namespace Clustering
{
    Point::Point(int)
    {

    };
    Point::Point(int , double *)
    {

    };
    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point &)
    {

    };
    Point &operator=(const Point &)
    {

    };
    Point::~Point()
    {

    };
    // Accessors & mutators
    int Point:: getId() const
    {
        return 0;
    };
    int Point::getDims() const
    {
        return 0;
    };
    void Point::setValue(int, double)
    {

    };
    double Point::getValue(int) const
    {
        return 0;
    };
    // Functions
    double Point::distanceTo(const Point &) const
    {
        return 0;
    };
    // Overloaded operators
    // Members
    Point & Point::operator*=(double)
    // p *= 6; p.operator*=(6);
    {

    };
    Point & Point::operator/=(double)
    {

    };
    const Point Point::operator*(double) const
    // prevent (p1 * 2) = p2;
    {

    };
    const Point Point::operator/(double) const
    // p3 = p2 / 2;
    {

    };
    double &Point::operator[](int index)
    {

    };
    // Friends
    Point &operator+=(Point &, const Point &)
    {

    };
    Point &operator-=(Point &, const Point &)
    {

    };
    const Point operator+(const Point &, const Point &)
    {

    };
    const Point operator-(const Point &, const Point &)
    {

    };
    bool operator==(const Point &, const Point &)
    {

    };
    bool operator!=(const Point &, const Point &)
    {

    };
    bool operator<(const Point &, const Point &)
    {

    };
    bool operator>(const Point &, const Point &)
    {

    };
    bool operator<=(const Point &, const Point &)
    {

    };
    bool operator>=(const Point &, const Point &)
    {

    };
    std::ostream &operator<<(std::ostream &, const Point &)
    {

    };
    std::istream &operator>>(std::istream &, Point &)
    {

    };
};