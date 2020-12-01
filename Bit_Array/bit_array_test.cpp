
// Bit Array - Test File

#include <iostream>  // cout, cin, cerr
#include <algorithm> // for_each()

#include "bit_array.hpp"

using namespace std;

#define BITS (13)

// g++ -ansi -pedantic-errors -Wall -Wextra -g bit_array_test.cpp bit_array.cpp

int main()
{
    system("clear");

    BitArray<BITS> bit;
    BitArray<BITS> bit2;

    cout << endl;
    cout << "bit is: " << bit.ToString() << endl;
    cout << "bit2 is: " << bit2.ToString() << endl;
    cout << endl;
    
    bit.SetAll();
    cout << "After SetAll() bit is: " << bit.ToString() << endl;
    cout << endl;

    cout << "After some different bits setting..." << endl;
    bit.Set(1, 0);
    bit.Set(3, 0);
    bit.Set(6, 0);

    bit2.Set(0, 1);
    bit2.Set(2, 1);
    bit2.Set(3, 1);
    bit2.Set(7, 1);

    cout << "bit is: " << bit.ToString() << endl;
    cout << "bit2 is: " << bit2.ToString() << endl;
    cout << endl;

    cout << "bit is equal to bit (1): "<< (bit == bit) << endl;
    cout << "bit is not equal to bit2 (0): "<< (bit == bit2) << endl;
    cout << "bit is not equal to bit2 (1): "<< (bit != bit2) << endl;
    cout << endl;

    cout << "bit[3] = (0): "<< bit[3] << endl;
    cout << "bit[4] = (1): "<< bit[4] << endl;
    bit[3] = 1;
    bit[4] = 0;
    cout << "After change:" << endl;
    cout << "bit[3] = (1): "<< bit[3] << endl;
    cout << "bit[4] = (0): "<< bit[4] << endl;
    cout << endl;

    cout << "checking the bit wise operations:   &, |, ^" << endl;
    BitArray<BITS> bit3 = bit;
    BitArray<BITS> bit4 = bit;

    bit &= bit2;
    bit3 |= bit2;
    bit4 ^= bit2;
    cout << "After \"bit &= b2\", bit is: " << bit.ToString() << endl;
    cout << "After \"bit3 &= b2\", bit3 is: " << bit3.ToString() << endl;
    cout << "After \"bit4 &= b2\", bit4 is: " << bit4.ToString() << endl;
    cout << endl;

    cout << "The number of set bits in 'bit is (3): " << bit.CountBitsOn() << endl;
    cout << endl;

    cout << "bit.Get(11) is (0): "<< bit.Get(11) << endl;
    bit.Flip(11);
    cout << "After fliping bit 3, bit.Get(11) is (1): "<< bit.Get(11) << endl;
    cout << endl;

    cout << "The number of set bits in 'bit is (5): " << bit.CountBitsOn() << endl;
    cout << endl;

    cout << "After FlipAll() on bit and bit2:" << endl;
    bit.FlipAll();
    bit2.FlipAll();
    cout << "bit is: " << bit.ToString() << endl;
    cout << "bit2 is: " << bit2.ToString() << endl;
    cout << endl;

    cout << "The number of set bits in 'bit is (8): " << bit.CountBitsOn() << endl;
    cout << endl;

    return (0);
}