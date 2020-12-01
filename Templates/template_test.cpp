
// Getting to know Templates - Test File

#include <iostream>

#include "template.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//                                  MAIN                                     //
///////////////////////////////////////////////////////////////////////////////
int main()
{
    Point<int> p1(2,5);
    Point<float> p2(4.4, 8.1);
    Point<double> p3(3.6, 1.543);
    Point<int> p4(5, 7);

    cout << p1.GetX() << endl;

    Point<int> check(p1 + p4);

    p1 += p4;    

    cout << "(" << p1.GetX() << ", " << p1.GetY() << ")" << endl;

    return (0);
}
