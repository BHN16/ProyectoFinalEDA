#pragma once
#include <iostream>
template <typename T>
class Point {

private:
    T x;
    T y;
public:
    typedef T t;
    Point (T x, T y);
    Point ();
    bool operator== ( Point<T>&);
    double distance ( Point<T>&);
    T getX ();
    T getY ();
};

template <typename T>
Point<T>::Point (T x, T y) {
    this->x = x;
    this->y = y;
}

template <typename T>
Point<T>::Point () {
}

template <typename T>
bool Point<T>::operator== ( Point<T>& p) {
    return (this->x == p.getX() && this->y == p.getY())? true : false;
}

template <typename T>
double Point<T>::distance ( Point<T>& p) {
    return sqrt((p.getX() - this->x)*(p.getX() - this->x) + (p.getY() - this->y)*(p.getY() - this->y));
}

template <typename T>
T Point<T>::getX () {
    return this->x;
}

template <typename T>
T Point<T>::getY () {
    return this->y;
}