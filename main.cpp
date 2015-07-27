#include <iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<stack>

using namespace std;

#define PI 3.14159265
#define RIGHT_ANGLE_DEGREE 90
#define RIGHT_ANGLE PI/2

#define NUM_MIN_POINT 3

#define LEFT_TURN 1
#define NON_LEFT_TURN -1

class GPoint;

class G_Point{

public:
    double x;
    double y;
    double r;
    double theta;

    double get_x() const{
        return x;
    }
    double get_y() const{
        return y;
    }
    double get_r() const{
        return r;
    }
    double get_theta() const{
        return theta;
    }

    void set_x(double x){
        this->x = x;
    }
    void set_y(double y){
        this->y = y;
    }
    void set_r(double r){
        this->r = r;
    }
    void set_theta(double theta){
        this->theta = theta;
    }
};

G_Point *min_point = NULL;


double compareAngle(const G_Point *lp , const G_Point *rp){
    /**
    * Find the angle assuming lp as the root
    **/
    double del_y = lp->get_y()  - rp->get_y();
    double del_x = lp->get_x()  - rp->get_x();

    double slope = 0;
    double angle = 0;

    if(del_x == 0){
        angle = RIGHT_ANGLE_DEGREE;
    }
    else{
       slope = del_y/del_x;
       angle  = atan(slope)*180/PI;
    }

    return angle;
}

struct ComparePointsByAngle : public std::binary_function<G_Point*, G_Point*, bool> {
    bool operator()(const G_Point *lhs , const G_Point *rhs) const{
        double angle_lhs = compareAngle(min_point , lhs);
        double angle_rhs = compareAngle(min_point , rhs);

        /**
        * For min heap
        **/
        if(angle_lhs == angle_rhs){
            return (lhs->get_x() > rhs->get_x());
        }

        return angle_lhs > angle_rhs;
    }
};

int determine_turn(G_Point *rp1 , G_Point *rp2 , G_Point *p){
    /**
    * To determine whether the p causes left turn w.r to the reference points rp1 , rp2
    * we need to find the cross product of
        ( rp1 , rp2 ) Cross ( rp1 , p )

        If the result is positive it means the p needs left turn
        If the result is negative it means the p needs right/non-left turn
    **/

    double x1 = rp2->get_x() - rp1->get_x();
    double y1 = rp2->get_y() - rp1->get_y();

    double x2 = p->get_x() - rp1->get_x();
    double y2 = p->get_y() - rp1->get_y();

    double determinate = x1*y2 - x2*y1;

    if(determinate >= 0){
        return LEFT_TURN;
    }

    return NON_LEFT_TURN;
}


int main()
{
    /**
    * Firstly we need to find the bottomest and leftest point
    * So this should be done in O(n) since we need to go through each point and find the
    * point with the minimum y co ordinate . If the tie is up we need to find the leftest item.
    *
    * So while scanning we can get the bottom and leftest point which should optimize the process a bit.
    **/
    vector<G_Point *> *input_points = new vector<G_Point *>();

    vector<G_Point *>::iterator input_points_iterator;

    for( input_points_iterator = input_points->begin() ; input_points_iterator != input_points->end(); input_points_iterator++){

        G_Point *current_point = *input_points_iterator;

        if(min_point==NULL){
            min_point = current_point;
        }
        else{
            /**
            * Compare the current point with the minimum point
            * Put into the min poingt whichever has  y co ordinate smaller
            * If the y co ordinate is equal then put based on smallest x value
            **/

            if(current_point->get_y() < min_point->get_y()){
                min_point = current_point;
            }
            else if(current_point->get_y()==min_point->get_y()){
                if(current_point->get_x() < min_point->get_x()){
                    min_point = current_point;
                }
            }
        }
    }

    /**
    * We have run through the points and should have the corner point right now
    * Now based on thsi point we will try to sort by the angle other points create with keeping it as origin.
    * We can run through the points and maintain a priority queue based on the angle.
    **/
    priority_queue<G_Point*, vector<G_Point*> , ComparePointsByAngle  > *pq = new priority_queue<G_Point* , vector<G_Point*> ,ComparePointsByAngle>();

    for(input_points_iterator = input_points->begin() ; input_points_iterator != input_points->end() ; input_points_iterator++){
        G_Point *current_point = *input_points_iterator;
        if(current_point != min_point){
            pq->push(current_point);
        }
    }

    stack<G_Point* , vector<G_Point*> > *S = new stack<G_Point* , vector<G_Point*> >();

    G_Point *p0 = min_point;
    S->push(p0);

    if(pq->size() >= NUM_MIN_POINT){
        G_Point *p1 = pq->top();
        pq->pop();
        S->push(p1);

        G_Point *p2 = pq->top();
        pq->pop();
        S->push(p2);
    }

    while(!pq->empty()){
        G_Point* pi = pq->top();

        int turn_type;
        do{

            G_Point* top = S->top();
            S->pop();

            G_Point *next_to_top = S->top();

            S->push(top);

            turn_type = determine_turn( next_to_top , top , pi);

            if(turn_type == NON_LEFT_TURN){
                S->pop();
            }

        }while(turn_type == NON_LEFT_TURN);

        S->push(pi);

        pq->pop();
    }

    /**
    * S: (stack ) should have the points which constitutes the convex hull in counter clickwise order
    **/

    /**
    * Freeing up the memory so that the program can release the memory
    **/
    for(input_points_iterator = input_points->begin() ; input_points_iterator != input_points->end() ; input_points_iterator++){

        G_Point *current_point = *input_points_iterator;
        free(current_point);
    }
    free(input_points);
    free(pq);
    free(S);
    return 0;
}
