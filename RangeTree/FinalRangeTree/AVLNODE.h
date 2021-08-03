template<typename Point>
class Node {
	public:
	Node<Point> *left;
	Node<Point> *right;
	Node<Point> *parent;
	Point value;
	int height;
	int balanceFactor;

	Node(Node<Point> *left = NULL, Node<Point> *right = NULL, Node<Point> *parent = NULL, Point value = Point(0 , 0) ) 
	{
		this->left = left;
		this->right = right;
		this->parent = parent;
		this->value = value;
		this->height = 0;
		this->balanceFactor = 0;
	}

	Node(Point value_) 
	{
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->value = value_;
		this->height = 0;
		this->balanceFactor = 0;
	}

};