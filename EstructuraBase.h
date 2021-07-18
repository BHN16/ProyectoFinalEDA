#pragma once
#include "AuxStructures/Point.h"
#include <vector>
template<typename Node, typename Point>
class EstructuraBase {
protected:
    Node* root;
public:
    virtual void insert(Point) = 0;
    virtual Node* search(Point) = 0;
    virtual std::vector<Node*> range(Point,Point) = 0;
    virtual Point* nearest_neighbor(Point) = 0;
};