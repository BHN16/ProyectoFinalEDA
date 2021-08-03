
#pragma once
#include "AVLTree.h"
#include "AVLNODE.h"

template<typename Point>
class RangeNode {
	public:
	RangeNode<Point> *left;
	RangeNode<Point> *right;
	RangeNode<Point> *parent;
	Point data;
	int height;
	int balanceFactor;
    AVL<Node<Point>, Point>* subtree;


	RangeNode(RangeNode<Point> *left = NULL, RangeNode<Point> *right = NULL, RangeNode<Point> *parent = NULL, Point data = Point() ) 
	{
		this->left = left;
		this->right = right;
		this->parent = parent;
		this->data = data;
		this->height = 0;
		this->balanceFactor = 0;
	}

    
};
