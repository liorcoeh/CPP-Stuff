////////////////////////////////////////////////////////////////////////////////
// File Name: serializer_test.hpp                                             //
// Author: Lior Cohen                                                         //
// Date 26/07/2020                                                            //
// Purpose: test file for the serializer class                                //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ostream>
#include <istream>
#include <fstream>
#include <cstdlib>

#include "serializer.hpp"

using namespace ilrd;

class Base
{
public:
    Base(){};
    virtual ~Base(){};
    virtual std::string& Get(){}
    virtual std::ostream& operator<<(std::ostream& os) const{ return os;}
    virtual std::istream& operator>>(std::istream& is) { return is;}
};

class Derived: public Base
{
public:
    Derived(){}

    void Set(const std::string& str)
    {
        m_str = str;
    }

    std::string& Get()
    {
        return m_str;
    }
    
    virtual std::ostream& operator<<(std::ostream& os) const
    {
        os << m_str;
        return os;
    }
    virtual std::istream& operator>>(std::istream& is) 
    {
        is >> m_str;
        return is;  
    }

private:
    std::string m_str;
};

int main() 
{
    system("clear");

    std::cout << "\nMain Test:\n" << std::endl;

    Serializer<Base> main_serializer;
    main_serializer.Add<Derived>();

    Derived c_deriverd;

    c_deriverd.Set("Hello_World");

    std::ofstream of_main_file;
    of_main_file.open ("test.txt");
    main_serializer.Serialize(c_deriverd, of_main_file);
    of_main_file.close();

    std::ifstream if_main_file;
    if_main_file.open ("test.txt");
    boost::shared_ptr<Base> base = main_serializer.Deserialize(if_main_file);
    if_main_file.close();

    std::cout << base->Get() << std::endl;

    return 0;
}