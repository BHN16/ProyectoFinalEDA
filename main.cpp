#include <iostream>
#include "AuxStructures/Point.h"
#include "KDTree/KDTree.h"
#include "KDTree/KDNode.h"
#include "RangeTree/RangeTree.h"
#include "RangeTree/RangeNode.h"
#include "RTree/RTree.h"
#include "RTree/RNode.h"
using namespace std;

int main () {
    Point<double> p1(1,2);
    Point<double> p2(3,4);
    KDTree<KDNode<double>, Point<double>> kde;
    kde.insert(p1);
    kde.search(p2);
    kde.range(p1,p2);
    kde.nearest_neighbor(p1);
    RangeTree<RangeNode<double>, Point<double>> range;
    range.insert(p1);
    range.search(p2);
    range.range(p1,p2);
    range.nearest_neighbor(p1);
    RTree<RNode<double>, Point<double>> r;
    r.insert(p1);
    r.search(p2);
    r.range(p1,p2);
    r.nearest_neighbor(p1);
    return 0;
}