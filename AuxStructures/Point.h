#pragma once


#include <iostream>
#include <math.h>

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
    T distance ( Point<T>&);
    T getPerpendicularX ( Point<T>);
    T getPerpendicularY ( Point<T>);
    T distance (const Point<T>&);
    T getX ();
    T getY ();
    T distanceM(T, T, T, T);
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
bool Point<T>::operator== ( Point<T>& p) {
    return (this->x == p.getX() && this->y == p.getY())? true : false;
}

template <typename T>
void Point<T>::show () {
    std::cout << "(" << this->x << "," << this->y << ") ";
}

template <typename T>
T Point<T>::distanceM(T lat1, T lon1, T lat2, T lon2){
    T longTierra = 6378.137;
    T dLat = lat2*M_PI/180 - lat1*M_PI/180;
    T dLon = lon2*M_PI/180 - lon1*M_PI/180;
    T a = sin(dLat/2)*sin(dLat/2) + cos(lat1*M_PI/180)*cos(lat2*M_PI/180)*sin(dLon/2)*sin(dLon/2);
    //std::cout<<a<<std::endl;
    T c = 2*atan2(sqrt(a),sqrt(1-a));
    //std::cout<<c<<std::endl;
    T d = longTierra*c;
    //std::cout<<d<<std::endl;
    return d*1000;    
}

template <typename T>
T Point<T>::getPerpendicularX ( Point<T> p) {
    //return distanceM(this->x,p.getY(),this->x, this->y);
    return std::sqrt((p.getY() - this->y)*(p.getY() - this->y));
}

template <typename T>
T Point<T>::getPerpendicularY ( Point<T> p) {
    //return distanceM(p.getX(),this->y,this->x,this->y);
    return std::sqrt((p.getX() - this->x)*(p.getX() - this->x));
}

template <typename T>
T Point<T>::distance ( Point<T> &p) {
    return distanceM(p.getX(),p.getY(),this->x,this->y);
    //return std::sqrt((p.getX() - this->x)*(p.getX() - this->x) + (p.getY() - this->y)*(p.getY() - this->y));
}

template <typename T>
T Point<T>::getX () {
    return this->x;
}

template <typename T>
T Point<T>::getY () {
    return this->y;
}
/*
template <typename T>
Point<T>::~Point () {
}*/