////////////////////////////////////////////////////////////////////////////////
// File Name: minion_protocol.hpp                                             //
// Author: Lior Cohen                                                         //
// Date 09/08/2020                                                            //
// Purpose: header file for the minion_protocol class                         //
// Code Reviewer:                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_MINION_PROTOCOL_HPP
#define ILRD_RD8586_MINION_PROTOCOL_HPP

#include <arpa/inet.h>
#include <stdint.h> // u_int64_t

#define MAX_DATA_SIZE (4096)
#define NET_BUFFSIZE(type_t) (offsetof(type_t, m_data[0]) + MAX_DATA_SIZE)

namespace ilrd
{

inline unsigned long long NtoH(unsigned long long val)
{
    return (htobe64(val));
}

// #pragma pack(push, 1)
struct Request
{
    char m_mode;
    u_int64_t m_uid;
    u_int64_t m_index;
    char m_data[1];
} __attribute__((packed));
// #pragma pack(pop)

struct Response
{
    char m_mode;
    u_int64_t m_uid;
    char m_status;
    char m_data[1];
} __attribute__((packed));

} // namespace ilrd

#endif /* ILRD_RD8586_MINION_PROTOCOL_HPP */