#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
class Node {
	public:
	Node<T> *left;
	Node<T> *right;
	Node<T> *parent;
	pair<T, T> value;
	int height;
	int balanceFactor;

	Node(Node<T> *left = NULL, Node<T> *right = NULL, Node<T> *parent = NULL, pair<T, T> value = pair<T, T>() ) 
	{
		this->left = left;
		this->right = right;
		this->parent = parent;
		this->value = value;
		this->height = 0;
		this->balanceFactor = 0;
	}
};


template<typename T>
class AVL
{
	public :

	//typedef Node<T> Node;
	
	Node<T>* root = NULL;
	
	
	void connectNode(Node<T> *curNode) 
	{
		Node<T> *parent = curNode->parent;
		if (parent == NULL) 
		{
			root = curNode;
		} 
		else if (parent->value >= curNode->value) 
		{
			parent->left = curNode;
		} 
		else 
		{
			parent->right = curNode;
		}
	}

	void updateHeight(Node<T> *curNode) 
	{
		int leftHeight = curNode->left == NULL ? 0 : curNode->left->height + 1;
		int rightHeight = curNode->right == NULL ? 0 : curNode->right->height + 1;
		curNode->height = max(leftHeight, rightHeight);
		curNode->balanceFactor = leftHeight - rightHeight;
	}		


	void leftRotation(Node<T> *node) {
		Node<T> *rightNode = node->right;
		Node<T> *temp = rightNode->left;
		
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

	void rightRotation(Node<T> *node) 
	{
		
		Node<T> *leftNode = node->left;
		Node<T> *temp = leftNode->right;
		
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

	void balanceNode(Node<T> *curNode) 
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

	void printBST(Node<T> *node) {
		if (node == NULL) 
		{
			return;
		}
		
		cout << (node-> value).first << "(" << node->balanceFactor << ")" << " ";
		//printf("%d(%d)  ", node->value , node->balanceFactor);
		printBST(node->left);
		printBST(node->right);
		
	}
	
	void printBST()
	{
		printBST(root);
	}

	void insert(vector<pair<T,T>> v, Node<T>** curnode ) {
		if (v.empty()) return;

		int mid = (v.size() - 1)/ 2;
		(*curnode) = new Node<T>(NULL, NULL, NULL, v[mid]);
		
		if (v.size() > 1)
		{
			vector<pair<T, T>> left(v.begin(), v.begin() + mid + 1);
			vector<pair<T, T>> right(v.begin() + mid + 1, v.end());
			this->insert(left, &(*curnode)->left );
			this->insert(right, &(*curnode)->right );
		}	
	}


	void insert_avl(vector<pair<T,T>> v) 
	{
		std::sort(v.begin(), v.end(), [](const std::pair<T,T> &left, const std::pair<T,T> &right) {
			return left.second < right.second;
		});
		insert(v, &root);
	}

	
	void insertNode(pair<T, T> val, Node<T> *parent, Node<T> *curNode) 
	{
		if (curNode == NULL) 
		{
			curNode = new Node<T>(NULL, NULL, parent, val);
			connectNode(curNode);
			
			return;
		}
		
		if (val <= curNode->value) 
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
	
	bool SearchNode(int val , Node<T> *curNode ) 
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
	



	void CheckPoint( T y1 , T y2, pair<T, T> point,  vector<pair<T, T>>& ans)
	{
		if ( y1 <= point.second && point.second <= y2 )
		{
			ans.emplace_back( point );
		}
		
	}



	



	Node<T>* FindSplitNode(T y1 , T y2)
	{
		Node<T>* V = this->root;
		// cout << "ga99" << endl;
		// cout << (V->value).second << endl;
		// cout << "ga89" << endl;
		while(!isLeaf(V) && ( y2 <= (V->value).second ||  y1 > (V->value).second  ))
		{
			
			if (y2 <= (V->value).second)	
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

	void ReportSubTree( Node<T>* n,  vector<pair<T, T>>& ans ) {
		
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


	bool isLeaf(Node<T>* Node)
	{
		
		return Node->left == NULL && Node-> right == NULL;
	}

	void Y_RANGEQUERY(T y1 , T y2, vector<pair<T, T>>& ans) 
	{
		
		Node<T>* VSplit = FindSplitNode(y1 , y2);

		//cout << (VSplit->value).second << endl;
		
		if (isLeaf( VSplit))
		{
			
			CheckPoint(y1 , y2, VSplit -> value , ans);
			return ;
		}	
		
	
		
		
		Node<T>* V = VSplit -> left;

		
		
		while( !isLeaf(V))
		{
			
			if ( y1 <= (V -> value).second)
			{
				// 1DRANGE
				ReportSubTree( V ->right, ans);
				//addValues(ans, this->rangehelper(y , y1))
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
			if ( y2 >= (V -> value).second )
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



