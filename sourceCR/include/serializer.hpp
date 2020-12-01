////////////////////////////////////////////////////////////////////////////////
// File Name: serializer.hpp                                                  //
// Author: Lior Cohen                                                         //
// Date 26/07/2020                                                            //
// Purpose: header file for the serializer class                              //
// Code Reviewer:                                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_SERIALIZER_HPP
#define ILRD_RD8586_SERIALIZER_HPP

#include <iostream>
#include <typeinfo>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

#include "factory.hpp"

namespace ilrd
{

template < class BASE >
class Serializer: boost::noncopyable
{
public:
    template <class DERIVED>
    void Add(); // DERIVED should have default ctor
    void Serialize(const BASE& obj, std::ostream& os) const;
    boost::shared_ptr<BASE> Deserialize(std::istream& is) const;
private:
    template <class DERIVED>
    static BASE* Creator(std::istream& is);
    Factory<std::string, BASE, std::istream&> m_factory;
};

template<class BASE> 
template<class DERIVED> 
void Serializer<BASE>::Add()
{
    m_factory.Add(typeid(DERIVED).name(), &Creator<DERIVED>);
}

template<class BASE> 
void Serializer<BASE>::Serialize(const BASE &obj, std::ostream &os) const
{
    os << typeid(obj).name() << ' ';
    obj << os;
}   

template<class BASE> 
boost::shared_ptr<BASE> Serializer<BASE>::Deserialize(std::istream &is) const
{
    std::string key;
    is >> key;

    boost::shared_ptr<BASE> obj(m_factory.Create(key, is));

    return obj;
}

template<class BASE> 
template<class DERIVED> 
BASE *Serializer<BASE>::Creator(std::istream &is)
{
    BASE *derived = new DERIVED;
    *derived >> is;

    return derived;
}

} // namespace ilrd

#endif // ILRD_RD8586_SERIALIZER_HPP