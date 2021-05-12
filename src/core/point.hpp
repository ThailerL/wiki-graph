/**
 * @file point.cpp
 * Implementation of Point class.
 */

#include <cmath>

#include "point.h"

/**
 * Point constructor. Initializes everything to 0.
 */
template <int Dim, typename V>
Point<Dim, V>::Point() {
    for (int i = 0; i < Dim; ++i)
        vals[i] = 0;
    data = V();
}

/**
 * Point constructor
 *
 * Copy the array of points in
 */
template <int Dim, typename V>
Point<Dim, V>::Point(double arr[Dim]) {
    for (int i = 0; i < Dim; ++i)
        vals[i] = arr[i];
    data = V();
}

template <int Dim, typename V>
template <typename T>
Point<Dim, V>::Point(T x, ...) {
    vals[0] = x;
    va_list ap;
    va_start(ap, x);
    for (int i = 1; i < Dim; i++)
        vals[i] = va_arg(ap, T);
    va_end(ap);
    data = V();
}

template<int Dim, typename V>
Point<Dim, V>::Point(double x1, double x2, V v) {
    vals[0] = x1;
    vals[1] = x2;
    data = v;
}

template <int Dim, typename V>
Point<Dim, V>& Point<Dim, V>::operator=(const Point<Dim, V>& other)
{
    for (int i = 0; i < Dim; i++) {
        vals[i] = other.vals[i];
    }

    return *this;
}

template <int Dim, typename V>
double Point<Dim, V>::operator[](int index) const {
    if (index >= Dim) {
        out_of_range e("Point index out of range");
        throw e;
    }

    return vals[index];
}

template <int Dim, typename V>
double& Point<Dim, V>::operator[](int index) {
    if (index >= Dim) {
        out_of_range e("Point index out of range");
        throw e;
    }

    return vals[index];
}

template <int Dim, typename V>
void Point<Dim, V>::set(int index, double val) {
    if (index >= Dim) {
        out_of_range e("Point index out of range");
        throw e;
    }
    vals[index] = val;
}

template <int Dim, typename V>
void Point<Dim, V>::print(std::ostream& out /* = cout */) const {
    out << '(';

    for (int i = 0; i < Dim - 1; ++i)
        out << vals[i] << ", ";
    out << vals[Dim - 1];

    out << ')';
}

template <int Dim, typename V>
std::ostream& operator<<(std::ostream& out, const Point<Dim, V>& p) {
    p.print(out);
    return out;
}

template<int Dim, typename V>
double distance2(const Point<Dim, V>& p1, const Point<Dim, V>& p2) {
    double d = 0;
    for (int i = 0; i < Dim; i++) {
        d += std::pow(p1[i] - p2[i], 2);
    }
    return d;
}

template <int Dim, typename V>
bool Point<Dim, V>::operator==(const Point<Dim, V> p) const {
    return !(*this != p);
}

template <int Dim, typename V>
bool Point<Dim, V>::operator!=(const Point<Dim, V> p) const {
    bool eq = true;
    for (int i = 0; i < Dim; ++i)
        eq &= (vals[i] == p.vals[i]);
    return !eq;
}

template <int Dim, typename V>
bool Point<Dim, V>::operator<(const Point<Dim, V> p) const {
    bool less = false;
    for (int i = 0; i < Dim; ++i) {
        less = vals[i] < p[i];
        if (vals[i] != p[i])
            break;
    }
    return less;
}

template <int Dim, typename V>
bool Point<Dim, V>::operator<=(const Point<Dim, V> p) const {
    return (*this < p) || (*this == p);
}

template <int Dim, typename V>
bool Point<Dim, V>::operator>(const Point<Dim, V> p) const {
    return !(*this < p);
}

template <int Dim, typename V>
bool Point<Dim, V>::operator>=(const Point<Dim, V> p) const {
    return (*this > p) || (*this == p);
}
