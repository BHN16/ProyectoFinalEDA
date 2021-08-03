#include "../AuxStructures/Point.h"
#include <vector>
#include <utility>
#include "RangeTree.h"
#include "RangeNode.h"

using namespace std;


int main()
{ 

    RangeTree< RangeNode<Point<double>> , Point<double>> Tree("green_tripdata_2015-01.csv");

	double x1, x2 , y1, y2;
	cout << "Rango a buscar" << endl;
	
	
	cout << " ingresar  x1 : " << endl;
	
	cin >> x1;
	
	cout << " ingresar  x2: " << endl;

	cin >> x2;



	cout << " ingresar  y1 : " << endl;
	
	cin >> y1;
	
	cout << " ingresar  y2 : " << endl;

	cin >> y2;

    vector<Point<double>> ans = Tree.Query(x1 , x2, y1 , y2);


	cout << "Cantidad" << endl;
    cout << ans.size() << endl;


	
}
