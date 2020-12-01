////////////////////////////////////////////////////////////////////////////////
// File Name: storage_test.cpp                                                //
// Author: Lior Cohen                                                         //
// Date 03/08/2020                                                            //
// Purpose: test file for the storage class                                   //
// Code Reviewer: Yaacov Evenchik                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "storage.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    Storage<60> store1(8);

    char write1[] = "That's my secret cap.. I'm always angry (Brus Banner)";
    char write2[] = "Ohhh... My... God (Dr. Jane Foster)";
    store1.Write(1, write2);
    store1.Write(3, write1);    

    char read1[60];
    char read3[60];

    store1.Read(3, read3);
    cout << read3 << endl;

    store1.Read(1, read1);
    cout << read1 << endl;

    return (0);
}