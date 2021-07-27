#pragma once

#include <vector>
#include <iostream>

template <typename MBR, int Size>
class RNode {
private:
    struct subNode {
        MBR mbr;
        RNode<MBR,Size>* rnode;
        subNode () {

        }
    };
    int capacity;
public:

    std::vector<subNode*> childrens;

    RNode () {
        this->capacity = 0;
    }

    void insertMBR(MBR region) {
        subNode* n = new subNode();
        n->mbr = region;
        n->rnode = nullptr;
        this->childrens.push_back(n);
        capacity++;
    }

    void insertMBRNode (MBR region, RNode<MBR,Size>* node) {
        subNode* n = new subNode();
        n->mbr = region;
        n->rnode = node;
        this->childrens.push_back(n);
        capacity++;
    }

    void show() {
        for (int i = 0; i < childrens.size(); i++) {
            std::cout << childrens[i]->mbr.getEsquinaSuperior().getX() << "," << childrens[i]->mbr.getEsquinaSuperior().getY() << " - " << childrens[i]->mbr.getEsquinaInferior().getX() << "," << childrens[i]->mbr.getEsquinaInferior().getY() << std::endl;
        }
    }

    MBR& getMBR (int i) {
        return this->childrens[i];
    }

    bool isLeaf() {
        for (int i = 0; i < childrens.size(); i++)
            if (childrens[i]->rnode) return false;
        return true;
    }
};