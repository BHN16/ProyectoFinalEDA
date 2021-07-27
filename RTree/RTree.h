#pragma once

#include "MBR.h"
#include <vector>
#include <iostream>
#include <limits>
#include <utility>
#include <algorithm>


template <typename Node, typename Point, int K>
class RTree {
private:
    Node* root;
    MBR<typename Point::t, Point> calcularPadre(std::vector<MBR<typename Point::t, Point>>& barrios);
    void buildAuxiliar(std::vector<MBR<typename Point::t, Point>>& barrios, std::vector<Node*>& nodos);
    void buildAuxiliar(std::vector<std::pair<MBR<typename Point::t, Point>,Node*>>& levelUp);
    void printAux(Node* r);
public:
    RTree ();
    void insert (Point p);
    Node* search (Point p);
    void build (std::vector<MBR<typename Point::t, Point>>& barrios);
    void printTree ();

};

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
    if (levelUp.size() == K) {
        std::sort(levelUp.begin(), levelUp.end(), [] (std::pair<MBR<typename Point::t, Point>,Node*>& h1, std::pair<MBR<typename Point::t, Point>,Node*>& h2) {
            return (h1.first.getCentroide().getX() < h2.first.getCentroide().getX());
        });
        std::cout << "MBRs ordenados raiz:\n";

        for (int i = 0; i < levelUp.size(); i++) {
            levelUp[i].first.showMBR();
        }
        Node* entrada = new Node();
        for (int i = 0; i < levelUp.size(); i++) {
            entrada->insertMBRNode(levelUp[i].first, levelUp[i].second);
        }
        this->root = entrada;
        return;
    }
    int aux = 0;
    std::vector<std::pair<MBR<typename Point::t,Point>,Node*>> upperLevel;
    std::sort(levelUp.begin(), levelUp.end(), [] (std::pair<MBR<typename Point::t, Point>,Node*>& h1, std::pair<MBR<typename Point::t, Point>,Node*>& h2) {
        return (h1.first.getCentroide().getX() < h2.first.getCentroide().getX());
    });
    
    
    std::cout << "MBRs ordenados:\n";

    for (int i = 0; i < levelUp.size(); i++) {
        levelUp[i].first.showMBR();
    }

    

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
        /*std::cout << "Hello there\n";
        for (int k = 0; k < levelUp.size(); k++) {
            levelUp[k].first.showMBR();
        }
        std::cout << aux << "\nFinal de impresion\n";*/
        std::vector<MBR<typename Point::t, Point>> auxiliar;
        Node* entrada = new Node();
        while(aux < levelUp.size()) {
            entrada->insertMBRNode(levelUp[aux].first, levelUp[aux].second);
            auxiliar.push_back(levelUp[aux].first);
            aux++;
        }
        upperLevel.push_back({this->calcularPadre(auxiliar), entrada});
    }

    /*
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
void RTree<Node,Point,K>::insert (Point p) {
    std::cout << "HOLA MUNDO INSERTADO\n";
}

template <typename Node, typename Point, int K>
Node* RTree<Node,Point,K>::search (Point p) {
    std::cout << "HOLA MUNDO SERCHEADO\n";
    return nullptr;
}

