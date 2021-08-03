#pragma once

#include "../EstructuraBase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

template <typename Node, typename Point>
class KDTree : public EstructuraBase<Node,Point> {
public:

    KDTree ();
    Node* search (Point p) override;
    void insert (Point p) override;

    std::vector<Node*> range(Point p1, Point p2) override;
    Point* nearest_neighbor (Point p) override;
    void print();
    std::vector<Point>* nearest_neighborhood(Point p, typename Point::t distance);
    void readFile();
    void insertPoints();

private:

    Node** Intersearch(Point p, Node** current, bool level);
    void Inter_nearest_neighborhood(Point p, typename Point::t distance, std::vector<Point>* vector_neighboors, Node* current , bool level);
    void Interprint(Node *);

    class travel{
        public:
        travel(long long id_ , std::pair<typename Point::t , typename Point::t> origin_,  std::pair<typename Point::t , typename Point::t> destination_) :
        id(id_),
        origin(origin_),
        destination(destination_){}

    long long id; // numero de fila en el csv
    
    std::pair<typename Point::t, typename Point::t> origin; // punto de partida del viaje
    std::pair<typename Point::t , typename Point::t> destination; // destino del viaje

    };

    std::vector<travel> travels;

    void GetTravels();



};

template<typename Node, typename Point>
void KDTree<Node, Point>::insertPoints(){

    int contador = 0 ;

    std::cout << "\n fila  ;  coordenadas origen ; coordenadas  destino \n\n"; 
    for (travel t : this->travels)
    {
        // first es longitude y second es latitude
        //std::cout << t.id << " ; " << t.origin.first <<  " " << t.origin.second << "  ; "  << t.destination.first << " " << t.destination.second << "\n";  
        //Point<double> p(t.origin.first, t.origin.second);
        this->insert(Point(t.origin.first,t.origin.second));
        this->insert(Point(t.destination.first,t.destination.second));

        contador++;
     
    }
    std::cout<<"acabon insertada\n";
}

template<typename Node, typename Point>
void KDTree<Node, Point>::readFile(){
    GetTravels();
}

template <typename Node, typename Point>
void KDTree<Node, Point>::GetTravels(){
    std::string path = "green_tripdata_2015-01.csv";
    std::string line, word;
    std::ifstream myfile (path);



    getline ( myfile, line );

    long long id = 1;

    while ( getline ( myfile, line ) ) 
    {
        std::stringstream ss(line);
        
        for (int i = 0 ; i < 5; i++) getline(ss, word, ',');

        std::pair<typename Point::t , typename Point::t> origin;
        std::pair<typename Point::t , typename Point::t> destination;
        
        ss >> origin.first ;
        ss.ignore();
        ss >> origin.second;

        ss.ignore();

        ss >> destination.first ;
        ss.ignore();
        ss >> destination.second;

        //this->insert(Point(origin.first,origin.second));
        //this->insert(Point(destination.first,destination.second));


        this->travels.emplace_back( travel(id , origin, destination ) );
        
        id++;
    
        continue;
    }
    
    std::cout<<"Acabo lectura \n";
    
    myfile.close();

}





template <typename Node, typename Point>
KDTree<Node,Point>::KDTree () {
    std::cout << "HOLA MUNDO\n";
    this->root=nullptr;
}   


template <typename Node, typename Point>
void KDTree<Node, Point>::Interprint(Node *current){
    if(current==nullptr)
        return;
    if(*(current->left())!=nullptr){
        Interprint(*(current->left()));
    }
    std::cout<<current->get_point().getX()<<" - "<<current->get_point().getY()<<"\n";
    if(*(current->right())!=nullptr){
        Interprint(*(current->right()));
    }
    return;

}


template <typename Node, typename Point>
void KDTree<Node, Point>::print(){
    Interprint(this->root);
}





template <typename Node, typename Point>
Node** KDTree<Node,Point>::Intersearch (Point p, Node** current, bool level) {

    //std::cout<<p.getX()<<"-"<<p.getY()<<std::endl;
    //std::cout<<current->get_point().getX()<<std::endl;
        //std::cout<<"Nullpointer\n";

    if(*current == nullptr){
        return current;
    }
    else if((*current)->get_point()==p){

        return current;
    }


    auto cur_point = (*current)->get_point();
    //std::cout<<"Llego aca"<<"\n";

    if((*current)->get(level,p)){

        //std::cout<<"buscando redercha "<<p.getX()<<"\n";

        return this->Intersearch(p,(*current)->right(),!level);
    }
    else{
        //std::cout<<"buscando ozquierda"<<p.getX()<<"\n";

        return this->Intersearch(p,(*current)->left(),!level);
    }


    return nullptr;
}


template <typename Node, typename Point>
void KDTree<Node,Point>::insert (Point p) {

    
    auto target = Intersearch(p,&this->root,0);

    if(*target==nullptr){

        *target = new Node(p.getX(),p.getY());
    }

    

    //std::cout<<this->root->get_point().getX()<<" _ "<<this->root->get_point().getY()<<"\n";
    //std::cout << "HOLA MUNDO INSERTADO\n";

}

template <typename Node, typename Point>
Node* KDTree<Node,Point>::search( Point p){
    std::cout << "HOLA MUNDO SERCHEADO\n";
    auto searching = *(this->Intersearch(p,&this->root,0));
    if((searching)!=nullptr){
        std::cout<<"Encontrado\n";
    }
    else{
        std::cout<<"No encontrado\n";
    }
    return searching;
    //return *(this->Intersearch(p,&this->root,0));

}


template <typename Node, typename Point>
std::vector<Point>* KDTree<Node,Point>::nearest_neighborhood(Point p, typename Point::t distance ){


    std::vector<Point>* vector_neighboors = new std::vector<Point>();
    Inter_nearest_neighborhood(p, distance, vector_neighboors,this->root,0);
    return vector_neighboors;
}

template <typename Node, typename Point>
void KDTree<Node,Point>::Inter_nearest_neighborhood(Point p, typename Point::t distance , std::vector<Point>* vector_neighboors, Node *current, bool level){


    if(current == nullptr ){
        return ;
    }

    auto cur_point = current->get_point();


    if(current->get(level,p)){

        this->Inter_nearest_neighborhood(p,distance,vector_neighboors,*(current->right()),!level);
        if(current->get_point().distance(p)<=distance){
            //std::cout<<"Pusheo -> ("<<current->get_point().getX()<<"-"<<current->get_point().getY()<<")\n";

            vector_neighboors->push_back(current->get_point());
        }
        if(current->left()==nullptr) return;
        typename Point::t per_distance;

        if(level==true){
            per_distance = p.getPerpendicularX(current->get_point());

        }else{
            per_distance = p.getPerpendicularY(current->get_point());
        }
        if(per_distance<=distance){
            this->Inter_nearest_neighborhood(p,distance,vector_neighboors,*(current->left()),!level);        
        }


    }
    else{





         this->Inter_nearest_neighborhood(p,distance,vector_neighboors,*(current->left()) ,!level);
        if(current->get_point().distance(p)<=distance){
            std::cout<<"Pusheo -> ("<<current->get_point().getX()<<"-"<<current->get_point().getY()<<")\n";
            vector_neighboors->push_back(current->get_point());
        }
        if(current->right()==nullptr) return;
        typename Point::t per_distance;
        if(level==true){
            per_distance = p.getPerpendicularX(current->get_point());
        }else{
            per_distance = p.getPerpendicularY(current->get_point());
        }
        if(per_distance<=distance){
            this->Inter_nearest_neighborhood(p,distance,vector_neighboors,*(current->right()),!level);        
        }


    }

}



template <typename Node, typename Point>
std::vector<Node*> KDTree<Node,Point>::range (Point p1, Point p2) {
    std::cout << "HOLA MUNDO EN RANGO\n";
    std::vector<Node*> v = {nullptr};
    return v;
}

template <typename Node, typename Point>
Point* KDTree<Node,Point>::nearest_neighbor (Point p) {
    std::cout << "HOLA MUNDO VECINO\n";
    return nullptr;
}