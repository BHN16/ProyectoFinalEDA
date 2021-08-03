#pragma once

template <typename T>
class KDNode {
private:
    Point<T> _p;
    KDNode* _left = nullptr;
    KDNode* _right = nullptr;
    bool level=0;

public:
    KDNode ();
    KDNode (Point<T> new_point) : _p(new_point){};
    KDNode (T x, T y) : _p(Point<T>(x,y)){};
    Point<T> get_point(){return this->_p;}
    KDNode** left(){return &this->_left;};
    KDNode** right(){return &this->_right;};
    bool get(bool level, Point<T> p){
        //std::cout<<level<<"\n";
        if(level){
            if(this->_p.getY()<p.getY()){
                return true;
            }
            return false;
        }

        if(this->_p.getX()<p.getX()){

            return true;
        }

        return false;
    }
};
