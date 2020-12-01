
// String with a Reference Counter - Functions Definitions

#include <iostream>
#include <string.h>

#include "reference_counter.hpp"

//#define ONE (1)

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RCString::RCString(const char* str_)
{
    m_rcs = new rcs_t;
    size_t length = strlen(str_);
    
    try
    {
        m_rcs->m_str = new char[length + 1];
    }
    catch(const std::exception& e)
    {
        delete this->m_rcs;
        std::cerr << "Allocation Failed" << '\n';
        throw std::bad_alloc();
    }
    
    memcpy(m_rcs->m_str, str_, length + 1);
    m_rcs->m_rc = ONE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RCString::RCString(const RCString& o_)
{
    this->m_rcs = o_.m_rcs;
    ++o_.m_rcs->m_rc;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RCString& RCString::operator=(const RCString& o_)
{
    this->~RCString();

    this->m_rcs = o_.m_rcs;  //Getting the current object to point at
    ++o_.m_rcs->m_rc;        //the other object struct

    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RCString::~RCString()
{
    if (1 == this->m_rcs->m_rc)   //There is only one object pointing to the
	{                             //the struct: Deleting this one
	    delete[] this->m_rcs->m_str;
        delete this->m_rcs;
    }
    else if (1 < this->m_rcs->m_rc)   //There are more than one pointing
    {                                 //lowering the counter by one
	    --this->m_rcs->m_rc;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

const char* RCString::ToCStr() const
{
    return (this->m_rcs->m_str);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

size_t RCString::Length() const
{
    return (strlen(this->m_rcs->m_str));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

char RCString::operator[](size_t idx_) const
{
    return (this->m_rcs->m_str[idx_]);
}


char& RCString::operator[](size_t idx_)
{
    if (1 != this->m_rcs->m_rc)
    {
        rcs_t *change = new rcs_t;
        size_t length = strlen(this->m_rcs->m_str);

        try
        {
            change->m_str = new char[length + 1];
        }
        catch(const std::exception& e)
        {
            delete change;
            std::cerr << "Allocation Failed" << '\n';
            throw std::bad_alloc();
        }
        
        change->m_rc = ONE;
        memcpy(change->m_str, this->m_rcs->m_str, length + 1);
        --this->m_rcs->m_rc;
        this->m_rcs = change;
    }

    return (this->m_rcs->m_str[idx_]);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

RCString& RCString::Concat(const RCString& o_)
{
    size_t length = strlen(this->m_rcs->m_str) + strlen(o_.m_rcs->m_str);
    rcs_t *change = new rcs_t;

    try
    {
        change->m_str = new char[length + 1];
    }
    catch(const std::exception& e)
    {
        delete change;
        std::cerr << "Concat Allocation Failed" << '\n';
        throw std::bad_alloc();
    }
    
    change->m_rc = ONE;
    strcpy(change->m_str, this->m_rcs->m_str);
    strcat(change->m_str, o_.m_rcs->m_str);

    if (ONE == this->m_rcs->m_rc)
    {
        delete[] this->m_rcs->m_str;
        delete this->m_rcs;
    }
    else
    {
        --this->m_rcs->m_rc;
    }
    this->m_rcs = change;

    return (*this);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool operator==(const RCString& s1, const RCString& s2)
{
    return (0 == strcmp(s1.ToCStr(), s2.ToCStr()));
}

bool operator!=(const RCString& s1, const RCString& s2)
{
    return (0 != strcmp(s1.ToCStr(), s2.ToCStr()));
}

bool operator<(const RCString& s1, const RCString& s2)
{
    return (0 > strcmp(s1.ToCStr(), s2.ToCStr()));
}

bool operator>(const RCString& s1, const RCString& s2)
{
    return (0 < strcmp(s1.ToCStr(), s2.ToCStr()));
}

std::ostream& operator<<(std::ostream& os_, const RCString& s_)
{
    return (os_ << s_.ToCStr() << std::endl);
}





