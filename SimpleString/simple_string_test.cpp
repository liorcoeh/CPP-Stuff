
// Simple String - Test File

#include <iostream>

#include "simple_string.hpp"

using namespace std;

// Utilty Function To Print
static ostream& operator<<(ostream& os_, const String& str_);


///////////////////////////////////////////////////////////////////////////////
//                                  MAIN                                     //
///////////////////////////////////////////////////////////////////////////////

int main()
{
    int check = 5;
    //system("clear");
    String s1("hello");
    cout << s1;

    int length = s1.Length();
    cout << "And it's length is " << length << "\n" << endl;

    String s2(s1);
    cout << s2;

    check = s1 == s2;
    cout << check << endl;

    String s3("WOW");
    check = s1 < s3;
    cout << check << endl;

    check = s1 > s3;
    cout << check << endl;

    String s4("123");
    s1 = s4;
    cout << "s1 is now " << s1 << endl;

    cout << "The length of s1 now is " << s1.Length() << endl;
    cout << "and the length of s2 is still " << s2.Length() << "\n" << endl;

    check = "123" == s1;
    cout << check << endl;

    String s5 = "Hello world";
    s5;
    

    String s6 = s5;
    cout << s5 << endl;


    return (0);
}

///////////////////////////////////////////////////////////////////////////////
//                            UTILITY FUNCTIONS                              //
///////////////////////////////////////////////////////////////////////////////

static ostream& operator<<(ostream& os_, const String& str_)
{
    return (os_ << str_.Cstr() << endl);
}

