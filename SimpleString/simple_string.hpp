
// Simple String

#ifndef SIMPLE_STRING_HPP
#define SIMPLE_STRING_HPP

#include <iostream>
#include <string.h>

class String
{
public:
    //String();
    String(const char *m_);
    String(const String& other_);
    
    ~String();

    String& operator=(const String& other_);
    String operator=(const char *str);

    inline int Length() const
    {
        return (strlen(m_str));
    }

    inline char *Cstr() const
    {
        return (this->m_str);
    }

private:
    char *m_str;
    int length;
};


bool operator==(const String& first_, const String& second_);

bool operator==(const char* str, const String& object_);

bool operator<(const String& first_, const String& second_);

bool operator>(const String& first_, const String& second_);


#endif // SIMPLE_STRING_HPP