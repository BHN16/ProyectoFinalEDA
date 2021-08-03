#ifndef AVL_RANGENODE_H
#define AVL_RANGENODE_H

#include "AVL.h"
#include <utility>

using namespace std;

template<typename T>
class RNode {
public:
    pair<T,T> data;
    RNode<T>* left;
    RNode<T>* right;
    RNode<T>* parent;
    AVL<T>* subtree;
    int height{};
    RNode();
    explicit RNode(pair<T,T> val);
    RNode(pair<T,T> val, RNode<T>* p);
    RNode(pair<T,T> val, RNode<T>* p, AVL<T>* t);
};

template <typename T>
RNode<T>::RNode() {
    this->height = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->subtree = new AVL<T>;
}

template <typename T>
RNode<T>::RNode(pair<T,T> val) {
    this->data = val;
    this->height = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->subtree = new AVL<T>;
}

template <typename T>
RNode<T>::RNode(pair<T,T> val, RNode<T>* p) {
    this->data = val;
    this->height = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = p;
    this->subtree = new AVL<T>;
}

template <typename T>
RNode<T>::RNode(pair<T,T> val, RNode<T>* p, AVL<T>* t) {
    this->data = val;
    this->height = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = p;
    this->subtree = t;
}
#endif //AVL_RANGENODE_H