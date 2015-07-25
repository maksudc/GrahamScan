#include <iostream>
#include<vector>
#include<cmath>
#include<queue>
#include<cstdlib>

using namespace std;
class GPoint;

class G_Point{

public:
    double x;
    double y;
    double r;
    double theta;

    double get_x(){
        return x;
    }
    double get_y(){
        return y;
    }
    double get_r(){
        return r;
    }
    double get_theta(){
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



    cout << "Hello world!" << endl;

    for(){}
    return 0;
}
