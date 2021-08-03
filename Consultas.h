#pragma once
#include <iostream>
#include "RTree/RTree.h"
#include "RTree/MBR.h"
#include "RTree/RNode.h"
#include "AuxStructures/Point.h"
#include "KDTree/KDTree.h"
#include "KDTree/KDNode.h"

class Consultas {
public:
    RTree<RNode< MBR<long double, Point<long double>>,5>,Point<long double>,5> Tree2;
    KDTree<KDNode<long double>, Point<long double>> kde;
    

    Consultas () {

        std::cout<<"Insertando Kde\n";
        kde.readFile();
        kde.insertPoints();
        std::cout<<"Insertando RTree\n";

        Tree2.readFile();
        Tree2.readPoints();


        //Tree1_2.getNVal();
    }


    void Pregunta1(){
        std::cout<<"Resolviendo la consulta 1 \n\n";
        Tree2.barriosIguales();

    }

    void Pregunta2(){
        std::cout<<"Resolviendo la consulta 2 \n\n";    
        Tree2.getNVal();

    }

    void Pregunta5(){
        std::cout<<"Resolviendo la consulta 5 \n\n";

        Point<long double> buscar(-73.691947937040596,42.700859069824219);

        auto retornar = kde.nearest_neighborhood(buscar,210);
    }
};