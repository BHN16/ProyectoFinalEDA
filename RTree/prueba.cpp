#include<iostream>
#include<vector>
#include "RTree.h"
#include "MBR.h"
#include "RNode.h"
#include "../AuxStructures/Point.h"

using namespace std;

int main () {
    vector<MBR<int,Point<int>>> regiones;
    Point<int> p1s(-1,19); 
    Point<int> p1i(-4,8);
    MBR<int, Point<int>> r0(p1s,p1i);
    regiones.push_back(r0);
    Point<int> p2s(-1,6); 
    Point<int> p2i(-5,1);
    MBR<int, Point<int>> r1(p2s,p2i);
    regiones.push_back(r1);
    Point<int> p3s(-3,9); 
    Point<int> p3i(-7,5);
    MBR<int, Point<int>> r2(p3s,p3i);
    regiones.push_back(r2);
    Point<int>p4s(-6,16); 
    Point<int>p4i(-9,11);
    MBR<int, Point<int>> r3(p4s,p4i);
    regiones.push_back(r3);
    Point<int>p5s(-8,19); 
    Point<int>p5i(-17,15);
    MBR<int, Point<int>> r4(p5s,p5i);
    regiones.push_back(r4);
    Point<int>p6s(-10,11); 
    Point<int>p6i(-15,5);
    MBR<int, Point<int>> r5(p6s,p6i);
    regiones.push_back(r5);
    Point<int>p7s(-13,13); 
    Point<int>p7i(-17,7);
    MBR<int, Point<int>> r6(p7s,p7i);
    regiones.push_back(r6);
    Point<int>p8s(-15,4); 
    Point<int>p8i(-17,1);
    MBR<int, Point<int>> r7(p8s, p8i);
    regiones.push_back(r7);
    Point<int>p9s(-19,13);
    Point<int>p9i(-24,7);
    MBR<int, Point<int>> r8(p9s,p9i);
    regiones.push_back(r8);
    Point<int>p10s(-21,3); 
    Point<int>p10i(-23,1);
    MBR<int, Point<int>> r9(p10s,p10i);
    regiones.push_back(r9);
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