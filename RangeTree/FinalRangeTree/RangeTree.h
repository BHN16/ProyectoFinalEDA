#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;
template<typename RangeNode, typename Point>
class RangeTree 
{
	private:
		RangeNode* root = NULL;
	    typedef typename Point::t query;
	public:

		RangeTree(string path);
        void insert(std::vector<Point> v,  RangeNode** curnode );
        void insert(vector<Point> v);
		void x_rangequery(query x1, query x2, query y1 , query y2, vector<Point>& ans);
		void CheckPoint( query x1, query x2, query y1 , query y2, Point point,  vector<Point>& ans);
		bool isLeaf(RangeNode* node);
		RangeNode* FindSplitNode(query x1 , query x2);
        vector<Point> Query(query x1, query x2, query y1 , query y2);

        void printBST(RangeNode *node) {
		if (node == NULL) 
		{
            cout << "nada" << endl; 
			return;
		}
		
		//cout << (node-> data).getX() << "(" << node->balanceFactor << " ,  " << node->height << ")" << " ";
		//printf("%d(%d)  ", node->value , node->balanceFactor);
		printBST(node->left);
		printBST(node->right);
		
	}
	
    void printBST()
    {
        cout << "impresion" << endl;
        printBST(root);
    }

};

template <typename RangeNode, typename Point>
RangeTree<RangeNode,Point>::RangeTree(string path) 
{

    string line, word;
    ifstream myfile (path);

    getline ( myfile, line );

    vector<Point> Points;

    int  i = 0;
    while ( getline ( myfile, line ) ) 
    {
        stringstream ss(line);
        
        for (int i = 0 ; i < 5; i++) getline(ss, word, ',');

        query x, y;
        
        ss >> x ;
        ss.ignore();
        ss >> y;

        Point origin(x, y);
        
        Points.emplace_back( origin );

        i++;
        // if (i > 2) break;
      
        continue;
    }

    this -> insert(Points);
    
    
    myfile.close();

}


template <typename RangeNode, typename Point>
void RangeTree<RangeNode,Point>::insert(std::vector<Point> v,  RangeNode** curnode ) {
    
    if (v.empty()) return;
    
    int mid = (v.size() - 1)/ 2;
 
    (*curnode) = new RangeNode(NULL , NULL, NULL , v[mid]);
    if (v.size() > 1)
    {
        std::vector<Point> left(v.begin(), v.begin() + mid + 1);
        std::vector<Point> right(v.begin() + mid + 1, v.end());
        this->insert(left, &(*curnode)->left);
        this->insert(right, &(*curnode)->right);
    }

     if (v.size() > 1) 
     {
		(*curnode)->subtree -> insert_avl(v);
    }	
}

template <typename RangeNode, typename Point>
void RangeTree<RangeNode,Point>::insert(vector<Point> v) 
{
    std::sort(v.begin(), v.end(), [](const Point &left, const Point &right) {
        return left.getX() > right.getX();
    });


    insert(v, &root );
}

// -73.922592163085938	40.754528045654297
// -73.952751159667969	40.677711486816406
// -73.843009948730469	40.71905517578125



template <typename RangeNode, typename Point>
void RangeTree<RangeNode,Point>::CheckPoint( query x1, query x2, query y1 , query y2, Point point,  vector<Point>& ans)
{
	if ( x1 <= point.getX() && point.getX() <= x2 && y1 <= point.getY() && point.getY() <= y2 )
	{
		ans.emplace_back( point );
	}
	
}


template <typename RangeNode, typename Point>
bool RangeTree<RangeNode,Point>::isLeaf(RangeNode* node)
{
	return node->left == NULL && node-> right == NULL;
}




template <typename RangeNode, typename Point>
RangeNode* RangeTree<RangeNode,Point>::FindSplitNode(query x1 , query x2)
{
	RangeNode* V = this->root;
	

	while(!isLeaf(V) && ( x2 <= (V->data).getX() ||  x1 > (V->data).getX()  ))
	{
		
		if (x2 <= (V->data).getX())	
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


template <typename RangeNode, typename Point>
void RangeTree<RangeNode,Point>::x_rangequery(query x1, query x2, query y1 , query y2, vector<Point>& ans) 
{

		
	RangeNode* VSplit = FindSplitNode(x1 , x2);
	
	
	if (isLeaf( VSplit))
	{
		CheckPoint(x1, x2, y1 , y2, VSplit -> data , ans);
		return ;
	}	
	
	
	
	
	RangeNode* V = VSplit -> left;
	
	while( !isLeaf(V))
	{
	
		if ( x1 <= (V -> data).getX())
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
		if ( x2 >= (V -> data).getX())
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

template <typename RangeNode, typename Point>
vector<Point> RangeTree<RangeNode,Point>::Query(query x1, query x2, query y1 ,  query y2)
{
    vector<Point> ans;

    if (x1 > x2) swap(x1, x2);
    if (y1 > y2)  swap(y1 , y2);
    x_rangequery(x1, x2, y1 , y1 , ans); 

    return ans;
}


