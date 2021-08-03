
#include "Consultas.h"
#include <iostream>

#include <iomanip>
#include <vector>

using namespace std;
 



int main () {


    std::cout.precision(17);

    Consultas soluciones;

    soluciones.Pregunta1(); 

    soluciones.Pregunta2(); 

    soluciones.Pregunta5(); 






/*
    Point<double> p1(-1,2);
    Point<double> p2(3,-4);
    Point<double> p3(4,2);
    Point<double> p4(-201,6);
    Point<double> p5(9,6);
    Point<double> p6(0,7);
    Point<double> p7(0,6);
    Point<double> p8(10,4);
    Point<double> p9(4,3);
    Point<double> p10(1,2);
    

    KDTree<KDNode<double>, Point<double>> kde;
    //std:cout<<p1.getX()<<endl;
    kde.insert(p1);
    kde.insert(p2);
    kde.insert(p3);
    kde.insert(p4);
    kde.insert(p5);
    kde.insert(p6);
    kde.insert(p7);
    kde.insert(p8);



    kde.search(p10);
    kde.range(p1,p2);
    kde.nearest_neighbor(p1);
    kde.nearest_neighborhood(p9,3.16);
    */
    /*RangeTree<RangeNode<double>, Point<double>> range;
    range.insert(p1);
    range.search(p2);
    range.range(p1,p2);
    range.nearest_neighbor(p1);
    RTree<RNode<double>, Point<double>> r;
    r.insert(p1);
    r.search(p2);
    r.range(p1,p2);
    r.nearest_neighbor(p1);
    */
    //kde.print();
/*
    for(auto val : *retornar){
        std::cout<<val.getX()<<" ; "<<val.getY()<<"\n";
    }
  */  
    //kde.search(buscar);





    






    return 0;
}