#pragma once
#include <iostream>
#include "RTree/MBR.h"
#include "RTree/RNode.h"
#include "RTree/RTree.h"
class Consultas {
public:
    Consultas () {
        RTree<RNode< MBR<long double, Point<long double>>,5>,Point<long double>,5> Tree1_2;
        Tree1_2.readFile();
        Tree1_2.readPoints();
        Tree1_2.getNVal();
        Tree1_2.barriosIguales();
    }
};