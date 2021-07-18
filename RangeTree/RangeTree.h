#pragma once

#include "../EstructuraBase.h"
#include <vector>
#include <iostream>

template <typename Node, typename Point>
class RangeTree : public EstructuraBase<Node,Point> {
public:
    RangeTree ();
    void insert (Point p) override;
    Node* search (Point p) override;
    std::vector<Node*> range(Point p1, Point p2) override;
    Point* nearest_neighbor (Point p) override;
};

template <typename Node, typename Point>
RangeTree<Node,Point>::RangeTree () {
    std::cout << "HOLA MUNDO\n";
}

template <typename Node, typename Point>
void RangeTree<Node,Point>::insert (Point p) {
    std::cout << "HOLA MUNDO INSERTADO\n";
}

template <typename Node, typename Point>
Node* RangeTree<Node,Point>::search (Point p) {
    std::cout << "HOLA MUNDO SERCHEADO\n";
    return nullptr;
}

template <typename Node, typename Point>
std::vector<Node*> RangeTree<Node,Point>::range (Point p1, Point p2) {
    std::cout << "HOLA MUNDO EN RANGO\n";
    std::vector<Node*> v = {nullptr};
    return v;
}

template <typename Node, typename Point>
Point* RangeTree<Node,Point>::nearest_neighbor (Point p) {
    std::cout << "HOLA MUNDO VECINO\n";
    return nullptr;
}