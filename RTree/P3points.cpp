#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;
 

class travel
{
    public:
    travel(long long id_ , pair<long double , long double> origin_,  pair<long double , long double> destination_) :
        id(id_),
        origin(origin_),
        destination(destination_)
    {
    }

    long long id; // numero de fila en el csv
    
    pair<long double , long double> origin; // punto de partida del viaje
    pair<long double , long double> destination; // destino del viaje

    // para el tipo pair ,  first es longitude y second es latitude
};




vector <travel> GetTravels()
{ 
    string path = "green_tripdata_2015-01.csv";
    string line, word;
    ifstream myfile (path);

    getline ( myfile, line );

    cout << setprecision(17);

    long long id = 1;

    vector<travel> travels;

    while ( getline ( myfile, line ) ) 
    {
        stringstream ss(line);
        
        for (int i = 0 ; i < 5; i++) getline(ss, word, ',');

        pair<long double , long double> origin;
        pair<long double , long double> destination;
        
        ss >> origin.first ;
        ss.ignore();
        ss >> origin.second;

        ss.ignore();

        ss >> destination.first ;
        ss.ignore();
        ss >> destination.second;

        travels.emplace_back( travel(id , origin, destination ) );
        
        id++;
      
        continue;
    }
    
    
    myfile.close();

    return travels;
}






int main() {
    vector< travel > travels  = GetTravels();
    int contador = 0 ;     
    cout << "\n fila  ;  coordenadas origen ; coordenadas  destino " << endl << endl;
    for (travel t : travels) {
        // first es longitude y second es latitude
       cout << t.id << " ; " << t.origin.first <<  " " << t.origin.second << "  ; "  << t.destination.first << " " << t.destination.second << endl;  
       contador++;
       if (contador > 10) break; 
    }
    return 0;
}