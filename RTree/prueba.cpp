#include<iostream>
#include<vector>
#include "RTree.h"
#include "MBR.h"
#include "RNode.h"
#include "../AuxStructures/Point.h"

using namespace std;

int main () {

    //RTree<RNode< MBR<int, Point<int>>,10>,Point<int>,10> Tree;
    RTree<RNode< MBR<long double, Point<long double>>,5>,Point<long double>,5> Tree2;
    //Tree.build(regiones);
    //cout << "Prueba de impresion\n";
    //Tree.printTree();
    /*cout << "Prueba de insercion de puntos:\n";
    Point<int> p1(2,17);
    Tree.insert(p1);
    cout << "punto1\n";
    Point<int> p2(3,4);
    Tree.insert(p2);
    cout << "punto2\n";
    Point<int> p3(5,6);
    Tree.insert(p3);
    cout << "punto3\n";
    Point<int> p4(5,18);
    Tree.insert(p4);
    cout << "punto4\n";
    Point<int> p5(7,14);
    Tree.insert(p5);
    cout << "punto5\n";
    Point<int> p6(12,3);
    Tree.insert(p6);
    cout << "punto6\n";
    Point<int> p7(19,3);
    Tree.insert(p7);
    cout << "punto7\n";
    Point<int> p8(14,9);
    Tree.insert(p8);
    cout << "punto8\n";
    Point<int> p9(22,10);
    Tree.insert(p9);
    cout << "punto9\n";
    Tree.showLeafsPoints();
    cout << "Hello world\n";*/
    Tree2.readFile();
    Tree2.readPoints();
    Tree2.getNVal();
    Tree2.barriosIguales();
    // barrios con mayor cantidad de viajes
    // viajes con origen y destino el mismo barrio
    //Tree2.printTree();
    return 0;
}