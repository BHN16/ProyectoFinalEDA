#pragma once

#include "../EstructuraBase.h"
#include <vector>
#include <iostream>

template <typename Node, typename Point>
class KDTree : public EstructuraBase<Node,Point> {
public:
    KDTree ();
    Node* search (Point p) override;
    void insert (Point p) override;

    std::vector<Node*> range(Point p1, Point p2) override;
    Point* nearest_neighbor (Point p) override;
    void print();
    std::vector<Point>& nearest_neighborhood(Point p, double distance);

private:
    Node** Intersearch(Point p, Node** current, bool level);
    void Inter_nearest_neighborhood(Point p, double distance, std::vector<Point>& vector_neighboors, Node* current , bool level);
    void Interprint(Node *);
};

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

    if(*current == nullptr){
        return current;
    }
    else if((*current)->get_point()==p){
        return current;
    }

    //std::cout<<"buscando "<<p.getX()<<"\n";

    auto cur_point = (*current)->get_point();


    if((*current)->get(level,p)){
        return this->Intersearch(p,(*current)->right(),!level);
    }
    else{
        return this->Intersearch(p,(*current)->left(),!level);
    }


    return nullptr;
}


template <typename Node, typename Point>
void KDTree<Node,Point>::insert (Point p) {

    
    auto target = Intersearch(p,&this->root,0);
    if(*target==nullptr){
        //std::cout<<"Insertado "<<p.getX()<<"\n";
        *target = new Node(p);
    }

    

    //std::cout<<this->root->get_point().getX()<<" _ "<<this->root->get_point().getY()<<"\n";
    std::cout << "HOLA MUNDO INSERTADO\n";

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
std::vector<Point>& KDTree<Node,Point>::nearest_neighborhood(Point p, double distance){

    std::vector<Point> vector_neighboors;
    Inter_nearest_neighborhood(p, distance, vector_neighboors,this->root,0);
    return vector_neighboors;
}

template <typename Node, typename Point>
void KDTree<Node,Point>::Inter_nearest_neighborhood(Point p, double distance, std::vector<Point>& vector_neighboors, Node *current, bool level){


    if(current == nullptr ){
        return ;
    }

    auto cur_point = current->get_point();


    if(current->get(level,p)){

        this->Inter_nearest_neighborhood(p,distance,vector_neighboors,*(current->right()),!level);
        if(current->get_point().distance(p)<=distance){
            std::cout<<"Pusheo -> ("<<current->get_point().getX()<<"-"<<current->get_point().getY()<<")\n";

            vector_neighboors.push_back(current->get_point());
        }
        if(current->left()==nullptr) return;
        double per_distance;

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
            vector_neighboors.push_back(current->get_point());
        }
        if(current->right()==nullptr) return;
        double per_distance;
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