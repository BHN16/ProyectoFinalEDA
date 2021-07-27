#include<iostream>
#include<vector>
#include "RTree.h"
#include "MBR.h"
#include "RNode.h"
#include "../AuxStructures/Point.h"

using namespace std;

int main () {
    vector<MBR<int,Point<int>>> regiones;
    Point<int> p1s(4,19); 
    Point<int> p1i(1,8);
    MBR<int, Point<int>> r0(p1s,p1i);
    regiones.push_back(r0);
    Point<int> p2s(5,6); 
    Point<int> p2i(1,1);
    MBR<int, Point<int>> r1(p2s,p2i);
    regiones.push_back(r1);
    Point<int> p3s(7,9); 
    Point<int> p3i(3,5);
    MBR<int, Point<int>> r2(p3s,p3i);
    regiones.push_back(r2);
    Point<int>p4s(9,16); 
    Point<int>p4i(6,11);
    MBR<int, Point<int>> r3(p4s,p4i);
    regiones.push_back(r3);
    Point<int>p5s(17,19); 
    Point<int>p5i(8,15);
    MBR<int, Point<int>> r4(p5s,p5i);
    regiones.push_back(r4);
    Point<int>p6s(15,11); 
    Point<int>p6i(10,5);
    MBR<int, Point<int>> r5(p6s,p6i);
    regiones.push_back(r5);
    Point<int>p7s(17,13); 
    Point<int>p7i(13,7);
    MBR<int, Point<int>> r6(p7s,p7i);
    regiones.push_back(r6);
    Point<int>p8s(17,4); 
    Point<int>p8i(15,1);
    MBR<int, Point<int>> r7(p8s, p8i);
    regiones.push_back(r7);
    Point<int>p9s(24,13);
    Point<int>p9i(19,7);
    MBR<int, Point<int>> r8(p9s,p9i);
    regiones.push_back(r8);
    Point<int>p10s(23,3); 
    Point<int>p10i(21,1);
    MBR<int, Point<int>> r9(p10s,p10i);
    regiones.push_back(r9);
    RTree<RNode< MBR<int, Point<int>>,2>,Point<int>,2> Tree;
    Tree.build(regiones);
    cout << "Prueba de impresion\n";
    Tree.printTree();
    cout << "Hello world\n";
    return 0;
}