#include <vector>
#include <iostream>
#include <algorithm>

//#include "AVLNODE.h"

using namespace std;



template<typename Node, typename Point>
class AVL
{
	private :

	Node* root;
	typedef typename Point::t query;
	
	public :

	
	
	
	void connectNode(Node *curNode) 
	{
		Node *parent = curNode->parent;
		if (parent == NULL) 
		{
			root = curNode;
		} 
		else if (parent->value.getX() >= curNode->value.getX() ) 
		{
			parent->left = curNode;
		} 
		else 
		{
			parent->right = curNode;
		}
	}

	void updateHeight(Node *curNode) 
	{
		int leftHeight = curNode->left == NULL ? 0 : curNode->left->height + 1;
		int rightHeight = curNode->right == NULL ? 0 : curNode->right->height + 1;
		curNode->height = max(leftHeight, rightHeight);
		curNode->balanceFactor = leftHeight - rightHeight;
	}		


	void leftRotation(Node *node) {
		Node *rightNode = node->right;
		Node *temp = rightNode->left;
		
		rightNode->left = node;
		rightNode->parent = node->parent;
		node->right = temp;
		node->parent = rightNode;
		
		if (temp != NULL) 
		{
			temp->parent = node;
		}
		
		connectNode(rightNode);
		updateHeight(node);
		updateHeight(rightNode);
	}

	void rightRotation(Node *node) 
	{
		
		Node *leftNode = node->left;
		Node *temp = leftNode->right;
		
		leftNode->right = node;
		leftNode->parent = node->parent;
		node->left = temp;
		node->parent = leftNode;	
		
		if (temp != NULL) 
		{
			temp->parent = node;
		}
		
		connectNode(leftNode);
		updateHeight(node);
		updateHeight(leftNode);
	}

	void balanceNode(Node *curNode) 
	{
		if (curNode->balanceFactor >= 2) {
			if (curNode->left->balanceFactor > 0) 
			{
				rightRotation(curNode);
			} 
			else 
			{ 
				leftRotation(curNode->left);
				rightRotation(curNode);
			}
		} 
		else if (curNode->balanceFactor <= -2) 
		{
			if (curNode->right->balanceFactor > 0) 
			{
				rightRotation(curNode->right);
				leftRotation(curNode);
			} else {
				leftRotation(curNode);
			}
		}
	}

	void printBST(Node *node) {
		if (node == NULL) 
		{
			return;
		}
		
		cout << (node-> value).getX() << "(" << node->balanceFactor << " ,  " << node->height << ")" << " ";

		printBST(node->left);
		printBST(node->right);
		
	}
	
	void printBST()
	{
		printBST(root);
	}
	


	void insert(std::vector<Point> v,  Node** curnode ) {
		if (v.empty()) return;
		
		
		int mid = (v.size() - 1)/ 2;
		
		//cout << v[mid].getX() << " " << v[mid].getY() <<  endl;
		
		(*curnode) = new Node( v[mid]);
		
		if (v.size() > 1)
		{
			std::vector<Point> left(v.begin(), v.begin() + mid + 1);
			std::vector<Point> right(v.begin() + mid + 1, v.end());
			this->insert(left, &(*curnode)->left);
			this->insert(right, &(*curnode)->right);
		}	
	}


	void insert_avl(vector<Point> v) 
	{
		
		if (v.size() > 1)
		{
			std::sort(v.begin(), v.end(), [](const Point &left, const Point &right) {
				return left.getY() > right.getY();
			});
		}
	
		int mid = (v.size() - 1)/ 2;
		
		Node* root = new Node(NULL , NULL, NULL , v[mid]);
		insert(v, &root );
	}

	void insertNode( Point val, Node *parent, Node *curNode) 
	{
		if (curNode == NULL) 
		{
			curNode = new Node(NULL, NULL, parent, val);
			connectNode(curNode);
			
			return;
		}
		
		if (val.getX() <= curNode->value.getX()) 
		{	
			insertNode(val, curNode, curNode->left);
		} 
		else 
		{
			
			insertNode(val, curNode, curNode->right);
		}
		
		updateHeight(curNode); 
		balanceNode(curNode);
	}
	
	bool SearchNode(int val , Node *curNode ) 
	{
		
		if (curNode == NULL)
		{
			return false;
		}
		
		if ( val < curNode -> value  )
		{
			return SearchNode( val , curNode -> left);
		}
		else if( val > curNode -> value  )
		{
			return SearchNode( val , curNode -> right );
		}
		else 
		{
			return true;
		}
	}
	
	void insertNode(Point val)
	{
		insertNode(val, NULL,  root);
	}




	void CheckPoint( query y1 , query y2, Point point,  vector<Point>& ans)
	{
		if ( y1 <= point.getY() && point.getY() <= y2 )
		{
			ans.emplace_back( point );
		}
	
	}




	Node* FindSplitNode(query y1 , query y2)
	{
		Node* V = this->root;
		while(!isLeaf(V) && ( y2 <= (V->value).getY() ||  y1 > (V->value).getY() ))
		{
			
			if (y2 <= (V->value).getY())	
			{
				V = V -> left;
			}
			else 
			{
				V = V -> right; 
			}
			
		}
		
		return V;
	}

	void ReportSubTree( Node* n,  vector<Point>& ans ) {
		
		if (!n->left && !n->right) 
		{
			ans.emplace_back(n->value);
		}
		if (n->right != NULL) {
			ReportSubTree(n->right, ans);
		}
		
		if (n->left != NULL) {
			ReportSubTree(n->left, ans);
		}
	
	}


	bool isLeaf(Node* node)
	{
		
		return node->left == NULL && node-> right == NULL;
	}


	void Y_RANGEQUERY(query y1 , query y2, vector<Point>& ans) 
	{
		
		Node* VSplit = FindSplitNode(y1 , y2);

		
		if (isLeaf( VSplit))
		{
			
			CheckPoint(y1 , y2, VSplit -> value , ans);
			return ;
		}	
		
	
		
		
		Node* V = VSplit -> left;

		
		
		while( !isLeaf(V))
		{
			
			if ( y1 <= (V -> value).getY())
			{
				
				ReportSubTree( V ->right, ans);
				
				V = V -> left;
			}
			else 
			{
				V = V -> right;	
			}
		}
		
		CheckPoint( y1 , y2, V->value, ans);
		
		
	
		V = VSplit -> right;
		while( !isLeaf(V))
		{
			if ( y2 >= (V -> value).getY() )
			{
				
				ReportSubTree( V -> left, ans);
				V = V -> right;
				
			}
			else 
			{
				V = V -> left;	
			}
		}
	
		CheckPoint( y1 , y2, V -> value , ans);
	}




}; 

