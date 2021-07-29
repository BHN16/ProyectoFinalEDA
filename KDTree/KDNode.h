#pragma once

template <typename T>
class KDNode {
private:
    Point<T> _p;
    KDNode* _left;
    KDNode* _right;
    bool level=0;

public:
    KDNode ();
    KDNode (Point<T> new_point) : _p(new_point){};
    Point<T> get_point(){return this->_p;}
    KDNode** left(){return &this->_left;};
    KDNode** right(){return &this->_right;};
    bool get(bool level, Point<T> p){
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
