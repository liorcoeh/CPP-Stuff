
// Shared Pointer - Test File

#include <iostream>
#include <cassert>

#include "shared_pointer.hpp"

using namespace std;

struct Test
{
   Test(): m_c('A'), m_i(10) {}
   char m_c;
   int m_i;
};
 
struct TestDerived : public Test
{
   TestDerived(): Test(),m_f(1.5) {}
   float m_f;
};

void foo(SharedPointer<int> &obj)
{
    cout << "foo " << *obj << endl;
}


//Not allow 

// SharedPointer<int>& foo2(void)
// {
//     //SharedPointer<int> *ptr = new SharedPointer<int>((new int(100)));
//     //return *ptr;
// }

int main()
{
    system("clear");
    
    SharedPointer<Test> test_SP(new Test());
    SharedPointer<int> int_SP(new int(100));
    cout << *int_SP << endl;
    cout << test_SP->m_c << endl;
    cout << test_SP->m_i << endl;


    // Notice: Besides initialization, usage of the pointers is with the usual
    // syntax. Except one thing: User does not need to ever delete.
    // i.e, support operator=, cctor, ->, * 
    test_SP->m_c = 'B';
    test_SP->m_i = 11;
    *int_SP = 111;
    cout << *int_SP << endl;
    cout << test_SP->m_c << endl;
    cout << test_SP->m_i << endl;

    SharedPointer<int> another_int_SP(new int(200));
    another_int_SP = int_SP;
    cout << *another_int_SP << endl;


    foo(int_SP);
    //another_int_SP = foo2();
    //delete (*another_int_SP);

    // Implicit upcast work (as it is while using regular pointers):
    SharedPointer<TestDerived> test_sp_Derived(new TestDerived());
    SharedPointer<TestDerived> test_sp_Derived2(test_sp_Derived);

    SharedPointer<Test> test_SP_implicit_conversion(test_sp_Derived);
    SharedPointer<Test> test_SP_implicit_conversion2(NULL);
    test_SP_implicit_conversion2 = test_sp_Derived;
    test_SP_implicit_conversion2->m_c = 'C';
    assert (test_SP_implicit_conversion->m_c == 'C');
    assert (test_SP_implicit_conversion2->m_c == 'C');
    assert (test_sp_Derived->m_c == 'C');
    test_sp_Derived = test_sp_Derived;
    assert (test_sp_Derived->m_c == 'C');

    // Implicit downcast does NOT work (as it is while using regular pointers):
    // SharedPointer<Test> test_SP_implicit_conversion_again(new Test());
    // This line need to not compile (think why):
    // SharedPointer<TestDerived> test_SP_Derived_again
    // (test_SP_implicit_conversion_again);  
    // SharedPointer<int> *ptr = new SharedPointer<int>((new int(100)));

    // Notice - no delete required.
 
   return 0;
}