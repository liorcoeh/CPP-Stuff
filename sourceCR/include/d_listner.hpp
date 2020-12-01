////////////////////////////////////////////////////////////////////////////////
// File Name: listner.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 26/07/2020                                                            //
// Purpose: header file for the file listner (reactor) assignment             //
// Code Reviewer: Alistair Hudson                                             //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_LISTNER_HPP
#define ILRD_RD8586_LISTNER_HPP

#include <iostream>
#include "source.hpp"
#include "reactor.hpp"

namespace ilrd
{

    class DerievedListener : public IListener
    {
    public:
        VectorHM Listen(const VectorHM &v)
        {
            struct timeval tv;
            tv.tv_sec = 1;
            fd_set new_set;
            FD_ZERO(&new_set);
            VectorHM retV;

            for (uint64_t i = 0; i < v.size(); ++i)
            {
                FD_SET(v[i].first, &new_set);
            }

            std::cout << "Listen()" << std::endl;

            if ((select(FD_SETSIZE, &new_set, NULL, NULL, &tv)) == 0)
            {
                std::cout << "Waiting..." << std::endl;
            }

            for (uint64_t i = 0; i < v.size(); ++i)
            {
                if (FD_ISSET(v[i].first, &new_set))
                {
                    std::cout << "Inside FD_SET after select: " << v[i].first << std::endl;
                    HandleAndMode new_pair(v[i].first, v[i].second);
                    retV.push_back(new_pair);
                }
            }

            return (retV);
        }
    };

} // namespace ilrd

#endif //ILRD_RD8586_LISTNER_HPP