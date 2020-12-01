
// Simple String - Functions Definitions

#include <iostream>
#include <string.h>

#include "simple_string.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// String::String()
// {
//     length = 5;
//     m_str = new char[length + 1];
//     memcpy(this->m_str, "hello", length + 1);
// }


String::String(const char *m_)
{
    length = strlen(m_);
    m_str = new char[length + 1];
    memcpy(this->m_str, m_, length + 1);
}

///////////////////////////////////////////////////////////////////////////////

String::String(const String& other_)
{
    length = other_.length;
    m_str = new char[length + 1];
    memcpy(this->m_str, other_.Cstr(), length + 1);
}

///////////////////////////////////////////////////////////////////////////////

String::~String()
{
    if (this->m_str);
    {
        delete[] m_str;
    }
    this->m_str = 0;
}

///////////////////////////////////////////////////////////////////////////////

String &String::operator=(const String &other_)
{
    char *temp = new char[strlen(other_.m_str) + 1];
    memcpy(temp, other_.m_str, (strlen(other_.m_str) + 1));

    delete[] this->m_str;
    this->m_str = temp;

    return (*this);
}

String String::operator=(const char *str)
{
    char *temp = new char[strlen(str) + 1];
    memcpy(temp, str, (strlen(str) + 1));

    delete[] this->m_str;
    this->m_str = temp;

    return (*this);
}

///////////////////////////////////////////////////////////////////////////////

bool operator==(const String& first_, const String& second_)
{
    return (0 == strcmp(first_.Cstr(), second_.Cstr()));
}

///////////////////////////////////////////////////////////////////////////////

bool operator==(const char *str, const String& object_)
{
    return (0 == strcmp(str, object_.Cstr()));
}

///////////////////////////////////////////////////////////////////////////////

bool operator<(const String& first_, const String& second_)
{
    return (0 > strcmp(first_.Cstr(), second_.Cstr()));
}

///////////////////////////////////////////////////////////////////////////////

bool operator>(const String& first_, const String& second_)
{
    return (0 < strcmp(first_.Cstr(), second_.Cstr()));
}

///////////////////////////////////////////////////////////////////////////////


