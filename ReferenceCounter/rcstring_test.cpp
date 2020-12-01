
// String with a Reference Counter - Test File

#include <iostream>
#include <cstdlib> 

#include "reference_counter.hpp"

using namespace std;

int main()
{
    //system("clear");
    RCString str1("Hello");
    RCString str2(str1);
    RCString str3 = str2;
    
    cout << str1;
    cout << str2;
    cout << str3;

    RCString str4("WOW");

    
    cout << "check should be (1): " << (str1 == str3) << endl;
    cout << "check should be (1): " << (str1 != str4) << endl;
    cout << "check should be (1): " << (str1 < str4) << endl;
    cout << "check should be (0): " << (str1 > str4) << "\n" << endl;

    cout << "The length of st1 is (5): " << str1.Length() << endl;
    cout << "The length of st2 is (5): " << str2.Length() << endl;
    cout << "The length of st3 is (5): " << str3.Length() << endl;
    cout << "The length of st4 is (3): " << str4.Length() << "\n" << endl;

    cout << str1.Concat(str2) << endl;

    str1[2] = 'e';
    cout << str1;

    char c = str2[2];

    cout << c << endl;

    cout << str4;
    str4 = str1.Concat(str2);
    cout << str2;
    cout << str4;

    str4 = str4;
    cout << str4;
    

    return (0);
}


