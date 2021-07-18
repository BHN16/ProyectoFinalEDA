#pragma once

#include "../EstructuraBase.h"
#include <vector>
#include <iostream>

template <typename Node, typename Point>
class KDTree : public EstructuraBase<Node,Point> {
public:
    KDTree ();
    void insert (Point p) override;
    Node* search (Point p) override;
    std::vector<Node*> range(Point p1, Point p2) override;
    Point* nearest_neighbor (Point p) override;
};

template <typename Node, typename Point>
KDTree<Node,Point>::KDTree () {
    std::cout << "HOLA MUNDO\n";
}

template <typename Node, typename Point>
void KDTree<Node,Point>::insert (Point p) {
    std::cout << "HOLA MUNDO INSERTADO\n";
}

template <typename Node, typename Point>
Node* KDTree<Node,Point>::search (Point p) {
    std::cout << "HOLA MUNDO SERCHEADO\n";
    return nullptr;
}

template <typename Node, typename Point>
std::vector<Node*> KDTree<Node,Point>::range (Point p1, Point p2) {
    std::cout << "HOLA MUNDO EN RANGO\n";
    std::vector<Node*> v = {nullptr};
    return v;
}

template <typename Node, typename Point>
Point* KDTree<Node,Point>::nearest_neighbor (Point p) {
    std::cout << "HOLA MUNDO VECINO\n";
    return nullptr;
}