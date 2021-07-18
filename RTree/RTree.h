#pragma once

#include "../EstructuraBase.h"
#include <vector>
#include <iostream>

template <typename Node, typename Point>
class RTree : public EstructuraBase<Node,Point> {
public:
    RTree ();
    void insert (Point p) override;
    Node* search (Point p) override;
    std::vector<Node*> range(Point p1, Point p2) override;
    Point* nearest_neighbor (Point p) override;
};

template <typename Node, typename Point>
RTree<Node,Point>::RTree () {
    std::cout << "HOLA MUNDO\n";
}

template <typename Node, typename Point>
void RTree<Node,Point>::insert (Point p) {
    std::cout << "HOLA MUNDO INSERTADO\n";
}

template <typename Node, typename Point>
Node* RTree<Node,Point>::search (Point p) {
    std::cout << "HOLA MUNDO SERCHEADO\n";
    return nullptr;
}

template <typename Node, typename Point>
std::vector<Node*> RTree<Node,Point>::range (Point p1, Point p2) {
    std::cout << "HOLA MUNDO EN RANGO\n";
    std::vector<Node*> v = {nullptr};
    return v;
}

template <typename Node, typename Point>
Point* RTree<Node,Point>::nearest_neighbor (Point p) {
    std::cout << "HOLA MUNDO VECINO\n";
    return nullptr;
}