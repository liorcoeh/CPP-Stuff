////////////////////////////////////////////////////////////////////////////////
// File Name: factory.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 03/08/2020                                                            //
// Purpose: header file for the factory assignemt                             //
// Code Reviewer: Yaacov Evenchik                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_FACTORY_HPP
#define ILRD_RD8586_FACTORY_HPP

#include <iostream>
#include <map>
#include "boost/core/noncopyable.hpp"

namespace ilrd
{

//Factory can be created as a singleton ,Shapes can be used for test
template<typename KEY, typename BASE, typename PARAMS, typename BUILDER = BASE* (*)(PARAMS)>
class Factory : private boost::noncopyable
{
public:
 
    // Add Function
    // Receives: key - key to the specific function to be created.
    //           creation_func - function which creates a specific object.
    // Exceptions: Throws runtime_error if function is NULL;
    //             Throws run-time exception if key already exist
    // BUILDER accepts functions which follows this declaration BASE* (*) (PARAMS) 
     
    void Add(KEY key, BUILDER creation_func);

    // Create Function
    // Receives: key - key to the specific function to be created.
    //           build_params - params that are needed for a creation function.
    // Exceptions: throws runtime_error if creation fails or key doesn't exist.

    BASE* Create(KEY key, PARAMS build_params)const;
private:
    std::map<KEY, BUILDER>m_factory_creation;
};

template<typename KEY, typename BASE, typename PARAMS, typename BUILDER>
void Factory<KEY, BASE, PARAMS, BUILDER>::Add(KEY key, BUILDER creation_func)
{
    if (!creation_func)
    {
        throw "creation func not given";
    }

    if (m_factory_creation.find(key) != m_factory_creation.end())
    {
        throw "Key already exists";
    }
    else
    {
        m_factory_creation[key] =  creation_func;
    }
}

template <class KEY, class BASE, class PARAMS, class BUILDER>
BASE *Factory<KEY, BASE, PARAMS, BUILDER>::Create(KEY key, PARAMS build_params) const
{
    typename std::map<KEY, BUILDER>::const_iterator it;

    BASE *ret = 0;

    try
    {
        it = m_factory_creation.find(key);

        if (it == m_factory_creation.end())
        {
            throw "Failed to create - Key doesn't exists";
        }

        ret = it->second(build_params);
    }
    catch(...)
    {
        throw "Failed to create";
    }

    return (ret);
}





} // namespace ilrd

#endif // ILRD_RD8586_FACTORY_HPP 