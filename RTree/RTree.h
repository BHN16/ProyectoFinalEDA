#pragma once

#include "MBR.h"
#include <vector>
#include <iostream>
#include <limits>
#include <utility>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

template <typename Node, typename Point, int K>
class RTree {
private:
    Node* root;
    MBR<typename Point::t, Point> calcularPadre (std::vector<MBR<typename Point::t, Point>>& barrios);
    void buildAuxiliar (std::vector<MBR<typename Point::t, Point>>& barrios, std::vector<Node*>& nodos);
    void buildAuxiliar (std::vector<std::pair<MBR<typename Point::t, Point>,Node*>>& levelUp);
    void printAux (Node* r);
    void showLeafsPointsHelper (Node* n);
    void getNValHelper (Node* n, std::vector<std::pair<int,std::string>>& v);
    bool sameRegionHelper (Node* n, Point in, Point out);
public:
    RTree ();
    void insert (Point p);
    void insertAux (Point p, Node* n);
    Node* search (Point p);
    void build (std::vector<MBR<typename Point::t, Point>>& barrios);
    void printTree ();
    void showLeafsPoints ();
    void getNVal ();
    void readFile ();
    void readPoints();
    bool sameRegion (Point in, Point out);
    void barriosIguales ();
    //~RTree();
};

/*
template <typename Node, typename Point, int K>
RTree<Node,Point,K>::~RTree() {
    std::cout << "hola rtree\n";
    delete root;
    this->root = nullptr;
}*/

template <typename Node, typename Point, int K>
bool RTree<Node,Point,K>::sameRegionHelper (Node* n, Point in, Point out) {
    if (n->isLeaf()) {
        for (int i = 0; i < n->childrens.size(); i++) {
            if (n->childrens[i]->mbr.insideArea(in) && n->childrens[i]->mbr.insideArea(out)) {
                return true;
            }
        }
        return false;
    }
    for (int i = 0; i < n->childrens.size(); i++) {
        if (n->childrens[i]->mbr.insideArea(in) && n->childrens[i]->mbr.insideArea(out)) {
            return true && this->sameRegionHelper(n->childrens[i]->rnode, in, out);
        }
    }
    return false;
}

template <typename Node, typename Point, int K>
bool RTree<Node,Point,K>::sameRegion (Point in, Point out) {
    for (int i = 0; i < this->root->childrens.size(); i++) {
        if (this->root->childrens[i]->mbr.insideArea(in) && this->root->childrens[i]->mbr.insideArea(out)) {
            return true && sameRegionHelper(this->root->childrens[i]->rnode, in, out);
        }
    }
    return false;
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::readFile () {
    std::vector<MBR<typename Point::t, Point>> barrios;
    std::ifstream myFile("../Data/datos.txt");
    std::string name;
    typename Point::t lonII, latII, lonSD, latSD;
    for (int i = 0; i < 310; i++) {
        std::getline(myFile, name);
        myFile >> lonII >> latII;
        myFile >> lonSD >> latSD;
        myFile.ignore();
        barrios.push_back(MBR<typename Point::t, Point>(Point(lonSD, latSD) ,Point(lonII, latII), name));
    }
    /*
    for (int i = 0; i < barrios.size(); i++) {
        barrios[i].showMBR();
    }*/
    this->build(barrios);
    myFile.close();
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::barriosIguales() {
    std::string line, word;
    std::ifstream myFile("../Data/green_tripdata_2015-01.csv"); 
    std::getline ( myFile, line );
    std::cout << std::setprecision(17);
    long long id = 1;
    typename Point::t aux1, aux2;
    std::vector<std::pair<int,std::pair<Point,Point>>> travels;
    while (std::getline (myFile, line)) {
        std::stringstream ss(line);
        for (int i = 0 ; i < 5; i++) std::getline(ss, word, ',');
        ss >> aux1 ;
        ss.ignore();
        ss >> aux2;
        ss.ignore();
        Point origin(aux1,aux2);
        ss >> aux1;
        ss.ignore();
        ss >> aux2;
        Point destino (aux1, aux2);
        if (this->sameRegion (origin, destino)) {
            travels.push_back({id, {origin,destino}});
        }
        id++;
        continue;
    }
    for (int i = 0; i < travels.size(); i++) {
        std::cout << travels[i].first << " - ";
        travels[i].second.first.show();
        travels[i].second.second.show();
        std::cout << std::endl;
    }
    std::cout<<travels.size()<<std::endl;
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::readPoints () {
    std::string line, word;
    std::ifstream myFile("../Data/green_tripdata_2015-01.csv"); 
    std::getline ( myFile, line );
    std::cout << std::setprecision(17);
    long long id = 1;
    typename Point::t aux1, aux2;
    std::vector<Point> travels;
    while ( std::getline ( myFile, line ) ) {
        std::stringstream ss(line);
        for (int i = 0 ; i < 5; i++) std::getline(ss, word, ',');
        ss >> aux1 ;
        ss.ignore();
        ss >> aux2;
        ss.ignore();
        Point origin(aux1,aux2);
        ss >> aux1;
        ss.ignore();
        ss >> aux2;
        //Point destino (aux1, aux2);
        travels.emplace_back(origin);
        //travles.emplace_back(destino)
        id++;
        continue;
    }
    for (int i = 0; i < travels.size(); i++) {
        this->insert(travels[i]);
    }
    myFile.close();
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::showLeafsPointsHelper (Node* r) {
    if (r->isLeaf()) {
        for (int i = 0; i < r->childrens.size(); i++) {
            if (!r->childrens[i]->mbr.emptyChildrens()) {
                std::cout << "MBR:\n";
                r->childrens[i]->mbr.showMBR();
                std::cout << "Puntos:\n";
                r->childrens[i]->mbr.showPoints();
                std::cout << "\n";
            }
        }
        return;
    }
    for (int i = 0; i < r->childrens.size(); i++) {
        showLeafsPointsHelper(r->childrens[i]->rnode);
    }
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::showLeafsPoints () {
    if (!this->root) return;
    this->showLeafsPointsHelper(this->root);
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::getNValHelper (Node* n, std::vector<std::pair<int,std::string>>& v) {
    if (n->isLeaf()) {
        for (int i = 0; i < n->childrens.size(); i++) {
            if (v.size() == 5) {
                int minimo = v[0].first;
                int aux = 0;
                for (int i = 1; i < v.size(); i++) {
                    if (minimo > v[i].first) {
                        minimo = v[i].first;
                        aux = i;
                    }
                }
                if (n->childrens[i]->mbr.getNumberPoints() > minimo) {
                    v[aux] = {n->childrens[i]->mbr.getNumberPoints(), n->childrens[i]->mbr.getNombre()};
                }
            } else {
                v.push_back({n->childrens[i]->mbr.getNumberPoints(), n->childrens[i]->mbr.getNombre()});
            }
        }
        return;
    }
    for (int i = 0; i < n->childrens.size(); i++) {
        this->getNValHelper(n->childrens[i]->rnode, v);
    }
}

//Implementación de priority queue
template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::getNVal () {
    std::vector<std::pair<int,std::string>> topBarrios;
    if (!this->root) return;
    int aux = 0;
    this->getNValHelper(this->root, topBarrios);
    for (int i = 0; i < topBarrios.size(); i++) {
        aux+=topBarrios[i].first;
        std::cout << topBarrios[i].first << " - " << topBarrios[i].second << std::endl;
    }
    std::cout << aux << std::endl;
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::printAux (Node* r) {
    if (r->isLeaf()) {
        return;
    }
    for (int i = 0; i < r->childrens.size(); i++) {
        r->childrens[i]->rnode->show();
        printAux(r->childrens[i]->rnode);
    }
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::printTree () {
    if (!this->root) return;
    for (int i = 0; i < this->root->childrens.size(); i++) {
        this->root->childrens[i]->mbr.showMBR();
    }
    this->printAux(this->root);
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::insertAux (Point p, Node* n) {
    if (n->isLeaf()) {
        for (int i = 0; i < n->childrens.size(); i++) {
            if (n->childrens[i]->mbr.insideArea(p)) {
                n->childrens[i]->mbr.insert(p);
            }
        }
        return;
    }
    for (int i = 0; i < n->childrens.size(); i++) {
        if (n->childrens[i]->mbr.insideArea(p)) {
            this->insertAux(p, n->childrens[i]->rnode);
        }
    }
    return;
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::insert (Point p) {
    for (int i = 0; i < this->root->childrens.size(); i++) {
        if (this->root->childrens[i]->mbr.insideArea(p)) {
            this->insertAux(p, this->root->childrens[i]->rnode);
        }
    }
}


template <typename Node, typename Point, int K>
RTree<Node,Point,K>::RTree () {
    this->root = nullptr;
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::buildAuxiliar(std::vector<MBR<typename Point::t, Point>>& barrios, std::vector<Node*>& nodos) {
    if (nodos.size() == 1) {
        this->root = nodos[0];
        return;
    }
    std::sort(barrios.begin(), barrios.end());

}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::buildAuxiliar(std::vector<std::pair<MBR<typename Point::t, Point>,Node*>>& levelUp) {
    std::sort(levelUp.begin(), levelUp.end(), [] (std::pair<MBR<typename Point::t, Point>,Node*>& h1, std::pair<MBR<typename Point::t, Point>,Node*>& h2) {
        return (h1.first.getCentroide().getX() < h2.first.getCentroide().getX());
    });

    if (levelUp.size() <= K) {
        /*
        std::cout << "MBRs ordenados raiz:\n";
        for (int i = 0; i < levelUp.size(); i++) {
            levelUp[i].first.showMBR();
        }
        */
        Node* entrada = new Node();
        for (int i = 0; i < levelUp.size(); i++) {
            entrada->insertMBRNode(levelUp[i].first, levelUp[i].second);
        }
        this->root = entrada;
        return;
    }

    int aux = 0;
    std::vector<std::pair<MBR<typename Point::t,Point>,Node*>> upperLevel;
    /*
    std::cout << "MBRs ordenados:\n";
    for (int i = 0; i < levelUp.size(); i++) {
        levelUp[i].first.showMBR();
    }
    */
    for (int i = 0; i < levelUp.size()-(levelUp.size()%(int)K); i+=(int)K, aux = i) {
        std::vector<MBR<typename Point::t, Point>> auxiliar;

        Node* entrada = new Node();
        for (int j = 0; j < K; j++) {
            entrada->insertMBRNode(levelUp[i+j].first, levelUp[i+j].second);
            auxiliar.push_back(levelUp[i+j].first);
        }

        /*
        for (int k = 0; k < auxiliar.size(); k++) {
            auxiliar[k].showMBR();
        }
        */

        upperLevel.push_back({this->calcularPadre(auxiliar), entrada});
    }
    if (aux < levelUp.size()) {
        //Funcional pero desequilibrado
        std::vector<MBR<typename Point::t, Point>> auxiliar;
        Node* entrada = new Node();
        while(aux < levelUp.size()) {
            entrada->insertMBRNode(levelUp[aux].first, levelUp[aux].second);
            auxiliar.push_back(levelUp[aux].first);
            aux++;
        }
        upperLevel.push_back({this->calcularPadre(auxiliar), entrada});
    }

    // PRUEBA FUNCIONAL, HAY QUE VER SI SE PUEDE USAR PARA ESTE CASO.
    /*
    if (aux+1 == levelUp.size()) {
        upperLevel.push_back(levelUp[aux]);
    } else {
        std::vector<MBR<typename Point::t, Point>> auxiliar;
        Node* entrada = new Node();
        while(aux < levelUp.size()) {
            entrada->insertMBRNode(levelUp[aux].first, levelUp[aux].second);
            auxiliar.push_back(levelUp[aux].first);
            aux++;
        }
        upperLevel.push_back({this->calcularPadre(auxiliar), entrada});
    }
    */
    // FIN DE PRUEBA
    /*
    std::cout << "Nivel con MBRS: \n";
    
    for (int i = 0; i < upperLevel.size(); i++) {
        upperLevel[i].first.showMBR();
    }
    */

    this->buildAuxiliar(upperLevel);
}

template <typename Node, typename Point, int K>
void RTree<Node,Point,K>::build(std::vector<MBR<typename Point::t, Point>>& barrios) {
    int aux = 0;
    // Se ordenan los MBR en base al eje X de su centroide de menor a mayor.
    std::sort(barrios.begin(), barrios.end(), [] (MBR<typename Point::t, Point>& h1, MBR<typename Point::t, Point>& h2) {
        return h1.getCentroide().getX() < h2.getCentroide().getX();
    });
    /*
    std::cout << "MBRS ordenados:\n";

    
    for (int i = 0; i < barrios.size(); i++) {
        std::cout << barrios[i].getCentroide().getX() << ":" << barrios[i].getEsquinaSuperior().getX() << "," << barrios[i].getEsquinaSuperior().getY() << " - " << barrios[i].getEsquinaInferior().getX() << "," << barrios[i].getEsquinaInferior().getY() << std::endl;
    }
    */

    // Implementación para ordenar MBR con su respectivo puntero
    std::vector<std::pair<MBR<typename Point::t,Point>,Node*>> levelUp;


    // Se crea el MBR de cada grupo K de MBRs agrupados, también se insertan en el nodo correspondiente y se inserta en el vector de nodos que se encuentran en el nivel de hojas, ya que este es el primero en llamarse.
    for(int i = 0; i < barrios.size()-(barrios.size()%K); i+=K, aux = i) {
        std::vector<MBR<typename Point::t, Point>> auxiliar;
        Node* entrada = new Node();
        for (int j = 0; j < K; j++) {
            entrada->insertMBR(barrios[i+j]);
            auxiliar.push_back(barrios[i+j]);
        }
        levelUp.push_back({this->calcularPadre(auxiliar), entrada});
    }
    // Cálculo del último MBR junto con su respectivo nodo.
    if (aux < barrios.size()) {
        std::vector<MBR<typename Point::t, Point>> auxiliar;
        Node* entrada = new Node();
        while(aux < barrios.size()) {
            entrada->insertMBR(barrios[aux]);
            auxiliar.push_back(barrios[aux]);
            aux++;
        }
        levelUp.push_back({this->calcularPadre(auxiliar), entrada});
    }

    // Llamada de build auxiliar para empezar a armar el árbol de manera bottom-up.
    //this->buildAuxiliar(nodosUp, nodos);

    // Implementación para nodos de arriba.
    //std::cout << "Hola\n";
    this->buildAuxiliar(levelUp);
}

// Se calcula el MBR que contiene a los MBR que pasamos por parámetro
template <typename Node, typename Point, int K>
MBR<typename Point::t, Point> RTree<Node,Point,K>::calcularPadre(std::vector<MBR<typename Point::t, Point>>& barrios) {
    if (barrios.size() == 1) {
        MBR<typename Point::t, Point> mbr(barrios[0].getEsquinaSuperior(), barrios[0].getEsquinaInferior());
        return mbr;
    }
    typename Point::t maxX = std::numeric_limits<typename Point::t>::min(), maxY = std::numeric_limits<typename Point::t>::min();
    typename Point::t minX = std::numeric_limits<typename Point::t>::max(), minY = std::numeric_limits<typename Point::t>::max();
    for (int i = 0; i < barrios.size(); i++) {
        if (barrios[i].getMinY() < minY) minY = barrios[i].getMinY();
        if (barrios[i].getMinX() < minX) minX = barrios[i].getMinX();
        if (barrios[i].getMaxX() > maxX) maxX = barrios[i].getMaxX();
        if (barrios[i].getMaxY() > maxY) maxY = barrios[i].getMaxY();
    }
    Point max(maxX, maxY);
    Point min(minX, minY);
    MBR<typename Point::t, Point> mbr(max, min);
    return mbr;
}

template <typename Node, typename Point, int K>
Node* RTree<Node,Point,K>::search (Point p) {
    std::cout << "HOLA MUNDO SERCHEADO\n";
    return nullptr;
}