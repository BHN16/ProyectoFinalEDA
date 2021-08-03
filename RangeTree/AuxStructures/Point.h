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
    bool operator== (const Point<T>&);
    T distance (const Point<T>&);
    T getX()const;
    T getY() const;
    void show ();
    //~Point ();
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
void Point<T>::show () {
    std::cout << "(" << this->x << "," << this->y << ") ";
}

template <typename T>
bool Point<T>::operator== (const Point<T>& p) {
    return (this->x == p.getX() && this->y == p.getY())? true : false;
}

template <typename T>
T Point<T>::distance (const Point<T>& p) {
    return sqrt((p.getX() - this->x)*(p.getX() - this->x) + (p.getY() - this->y)*(p.getY() - this->y));
}

template <typename T>
T Point<T>::getX () const {
    return this->x;
}

template <typename T>
T Point<T>::getY () const{
    return this->y;
}
