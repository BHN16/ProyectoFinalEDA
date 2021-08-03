
#ifndef AVL_RANGETREE_H
#define AVL_RANGETREE_H

#include "RangeNode.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

template<typename T>
class RangeTree 
{
	private:
		//typename Point::t;
		// Raycross
		// Diapos
		RNode<T>* root;
		void insert_helper(vector<pair<T,T>>,RNode<T>**);
		void prehelper (RNode<T>*);
	public:
		RangeTree();
		explicit RangeTree(pair<T,T> val);
		void preorder();
		void insert (const string&);
		void X_RANGEQUERY(T x1, T x2, T y1 , T y2, vector<pair<T, T>>& ans);
		void CheckPoint( T x1, T x2, T y1 , T y2, pair<T, T> point,  vector<pair<T, T>>& ans);
		bool isLeaf(RNode<T>* Node);
		RNode<T>* FindSplitNode(T x1 , T x2);
		void printnode(RNode<T>* Node); 
};

template<typename T>
RangeTree<T>::RangeTree() {
    this->root = nullptr;
}

template<typename T>
RangeTree<T>::RangeTree(pair<T,T> val) {
    this->root = new RNode<pair<T,T>>(val);
}


template<typename T>
void RangeTree<T>::insert_helper(vector<pair<T,T>> v, RNode<T>** r) {
    if (v.empty()) return;
    int mid = (v.size() - 1)/ 2;
    (*r) = new RNode<T>(v[mid]);
    if (v.size() > 1)
    {
		vector<pair<T, T>> left(v.begin(), v.begin() + mid + 1);
		vector<pair<T, T>> right(v.begin() + mid + 1, v.end());
		this->insert_helper(left, &(*r)->left);
		this->insert_helper(right, &(*r)->right);
	}
    
    if (v.size()) {
		(*r)->subtree -> insert_avl(v);
        // for (auto i : v) {
        //     (*r)->subtree->insert(i);
        // }
    }
}



template<typename T>
void RangeTree<T>::CheckPoint( T x1, T x2, T y1 , T y2, pair<T, T> point,  vector<pair<T, T>>& ans)
{
	if ( x1 <= point.first && point.first <= x2 && y1 <= point.second && point.second <= y2 )
	{
		ans.emplace_back( point );
	}
	
}


template<typename T>
bool RangeTree<T>::isLeaf(RNode<T>* Node)
{
	return Node->left == NULL && Node-> right == NULL;
}

template<typename T>
RNode<T>* RangeTree<T>::FindSplitNode(T x1 , T x2)
{
	RNode<T>* V = this->root;
	

	while(!isLeaf(V) && ( x2 <= (V->data).first ||  x1 > (V->data).first  ))
	{
		
		if (x2 <= (V->data).first)	
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


template<typename T>
void RangeTree<T>::X_RANGEQUERY(T x1, T x2, T y1 , T y2, vector<pair<T, T>>& ans) 
{

		
	RNode<T>* VSplit = FindSplitNode(x1 , x2);
	
	
	if (isLeaf( VSplit))
	{
		CheckPoint(x1, x2, y1 , y2, VSplit -> data , ans);
		return ;
	}	
	
	
	
	
	RNode<T>* V = VSplit -> left;
	
	while( !isLeaf(V))
	{
	
		if ( x1 <= (V -> data).first)
		{
			
			
			isLeaf(V->right)? CheckPoint(x1, x2, y1, y2,V->right ->data, ans): 
			V -> right -> subtree-> Y_RANGEQUERY(y1 , y2 , ans);
			
			V = V -> left;
			
		}
		else 
		{
			V = V -> right;	
		}
		
		
		if (V == NULL) break;
		
	}
	

	
	if (V!= NULL) CheckPoint(x1, x2, y1 , y2, V->data, ans);
	
 
 
 
    V = VSplit -> right;
  
	while( !isLeaf(V))
	{
		if ( x2 >= (V -> data).first )
		{
			
			isLeaf(V->left)?  CheckPoint(x1, x2, y1, y2,V->left->data, ans): 
			V -> left -> subtree-> Y_RANGEQUERY(y1 , y2 , ans);
			
			V = V -> right;
			
		}
		else 
		{
			V = V -> left;	
		}
		if (V == NULL) break;
	}
	
	if (V!= NULL) CheckPoint(x1, x2, y1 , y2, V -> data , ans);
	

}


template<typename T>
void RangeTree<T>::printnode(RNode<T>* Node) 
{
	cout << Node-> data.first << " " <<  Node -> data.second << endl;
}


template<typename T>
void RangeTree<T>::insert(const string& f) {
    fstream file(f);
     T x1, x2, y1, y2, n, aux1, aux2;
    if (file.is_open()) {
        vector<pair<T,T>> p;
        set<T> Xset, Yset;
       
        file >> x1 >> y1 >> x2 >> y2;
        file >> n;
        
        while (n--){
            file >> aux1 >> aux2;
            if (Xset.insert(aux1).second && Yset.insert(aux2).second) {
                p.push_back({aux1, aux2});
            }
        }
        
        
        
        file.close();
        sort(p.begin(), p.end());
        
        int mid = (p.size() - 1)/2;
        

		cout << p.size() << endl;
		
        this->root = new RNode<T>(p[mid]);
       
        vector<pair<T,T>> left (p.begin(), p.begin()+mid + 1);
        vector<pair<T,T>> right (p.begin()+mid+1, p.end());
       
        this->insert_helper(left, &this->root->left);
        this->insert_helper(right, &this->root->right);
       
        // for (auto i : p)
        root->subtree->insert_avl(p);
            
       
		
		
		vector<pair<T, T>> ans ;
		
		cout << "end construct" << endl;
		
		
		
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
		
		this-> X_RANGEQUERY(x1, x2, y1 , y2, ans);
		
		
		
		sort(ans.begin(), ans.end());
		
		fstream out;
		out.open("solucion.txt", std::ios_base::out);
		
		out << "Se encontraron " << ans.size() << " valores :" << endl;
		
		for(pair<T, T> &pp : ans)
		{
			out << pp.first << " " << pp.second << endl;
		}
		
        
    }
   
}



template<typename T>
void RangeTree<T>::prehelper(RNode<T> *n) {
    if (n) {
        cout << "Valor del nodo : " << n->data.first << " " << n->data.second << endl;
       
        this->prehelper(n->left);
        this->prehelper(n->right);
    }
}


template<typename T>
void RangeTree<T>::preorder() {
    this->prehelper(this->root);
}

#endif //AVL_RANGETREE_H
