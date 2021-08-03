#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <string>

template <typename T, typename Point>
class MBR {
private:
    Point esquinaSuperior;
    Point esquinaInferior;
    std::vector<Point>* childrens;
    double hilbertVal;
    Point centroide;
    std::string nombre;
public:
    MBR (Point a, Point b) {
        this->esquinaSuperior = a;
        this->esquinaInferior = b;
        this->childrens = nullptr;
        this->hilbertVal = 0;
        this->centroide = this->calculateCentroid(); 
        this->childrens = new std::vector<Point>();
    }

    MBR (Point a, Point b, std::string n) {
        this->esquinaSuperior = a;
        this->esquinaInferior = b;
        this->childrens = nullptr;
        this->hilbertVal = 0;
        this->centroide = this->calculateCentroid(); 
        this->childrens = new std::vector<Point>();
        this->nombre = n;
    }

    MBR () {
        this->childrens = new std::vector<Point>();
    }

    std::string getNombre () {
        return this->nombre;
    }

    bool emptyChildrens() {
        return this->childrens->empty();
    }

    void showPoints () {
        for (int i = 0; i < this->childrens->size(); i++) {
            (*this->childrens)[i].show();
            std::cout << std::endl;
        }
    }

    int getNumberPoints() {
        return this->childrens->size();
    }

    void showMBR() {
        std::cout << this->esquinaSuperior.getX() << "," << this->esquinaSuperior.getY() << " - " << this->esquinaInferior.getX() << "," << this->esquinaInferior.getY() << std::endl;
    }

    bool insideArea (Point p) {
        if (p.getX() >= this->esquinaInferior.getX() && p.getY() >= this->esquinaInferior.getY() && p.getX() <= this->esquinaSuperior.getX() && p.getY() <= this->esquinaSuperior.getY()) {
            return true;
        }
        return false;
    }

    Point getEsquinaSuperior () {
        return this->esquinaSuperior;
    }

    Point getEsquinaInferior () {
        return this->esquinaInferior;
    }

    std::pair<typename Point::t,typename Point::t> getX () {
        return {this->esquinaSuperior.getX(), this->esquinaInferior.getX()};
    }

    std::pair<typename Point::t,typename Point::t> getY () {
        return {this->esquinaSuperior.getY(), this->esquinaInferior.getY()};
    }

    typename Point::t getMaxX () {
        return this->esquinaSuperior.getX();
    }

    typename Point::t getMaxY () {
        return this->esquinaSuperior.getY();
    }

    typename Point::t getMinX () {
        return this->esquinaInferior.getX();
    }

    typename Point::t getMinY () {
        return this->esquinaInferior.getY();
    }

    double getHilbertVal () {
        return this->hilbertVal;
    }

    void insert (Point p) {
        this->childrens->push_back(p);
    }

    Point getCentroide () {
        return this->centroide;
    }

    Point calculateCentroid() {
        return {(this->esquinaSuperior.getX()+this->esquinaInferior.getX())/2, (this->esquinaSuperior.getY()+this->esquinaInferior.getY())/2};
    }

    bool operator > (MBR<typename Point::t,Point>& m) const {
        return (this->centroide.getX() > m.getCentroide().getX())? true : false;
    }
    /*
    ~MBR () {
        delete childrens;
    }
    */
    /*
    void calculateHilbertVal (double n) {
        int s;
        double rx, ry, d=0, x = this->calculateCentroid().first, y = this->calculateCentroid().second;
        for (s=n/2; s>0; s/=2) {
            rx = (x & s) > 0;
            ry = (y & s) > 0;
            d += s * s * ((3 * rx) ^ ry);
            if (ry == 0) {
                if (rx == 1) {
                    x = n-1 - x;
                    y = n-1 - y;
                }
                int t  = x;
                x = y;
                y = t;
            }
        }
        this->hilbertVal = d;
    }*/
};

