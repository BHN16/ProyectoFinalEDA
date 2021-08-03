
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;


int N = 310;

class city
{
public:
  city(string name_, pair<long double , long double> II_,  pair<long double , long double> SD_) :
    name(name_),
    II(II_),
    SD(SD_)
  {
  }
  string name;
  pair<long double , long double> II; // inferior izqueirda
  pair<long double , long double> SD; // superior derecha
};




int main()
{

  vector< city > cities;
  
  std::ifstream myfile;
  myfile.open ("datos.txt");
  
    string name;
    long double lonII, latII;
    long double lonSD, latSD;
  
  for (int i = 0 ; i < N ; i++)
  {
   
    getline(myfile, name);
    
    myfile >> lonII >> latII;
    myfile >> lonSD >> latSD;
    
    myfile.ignore();
    
    cities.emplace_back( city( name , { lonII , latII } , { lonSD, latSD }));
  }


  // PRUEBA EN CONSOLA
  cout << setprecision(17);
  for (auto u : cities)
  {
    cout << u.name << endl;
    cout << u.II.first << " " << u.II.second << endl; 
    cout << u.SD.first << " " << u.SD.second << endl; 
  }

  return 0;

}