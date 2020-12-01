
// Bit Array

#include <iostream>  // cout, cin, cerr
#include <stddef.h>  // size_t
#include <algorithm> // for_each()
#include <numeric>   // accumulate()
#include <string.h>  // strcmp()
#include <climits>   // CHAR_BIT

using namespace std;

typedef unsigned char BYTE;
#define ON (1)
#define BITS_IN_BYTE (8)
#define FULL_BYTE (255)
#define BIT_CHAR(bit) ((bit) / BITS_IN_BYTE)

const unsigned char full_byte = 255;

////////////////////////////////////////////////////////////////////////////////
//                           CLASSES DECLARATIONS                             //
////////////////////////////////////////////////////////////////////////////////

class BitProxy
{
public:
    BitProxy(unsigned char &byte, BYTE index) : m_byte(byte), m_index(index % 8)
    {}
    BitProxy &operator=(const BitProxy& rhs);
    BitProxy &operator=(bool val);
    operator bool() const;
    bool operator!() const;

private:
    BYTE &m_byte;
    unsigned char m_index;
};

////////////////////////////////////////////////////////////////////////////////

class ShiftRight
{
public:
    ShiftRight(size_t shmnt);

    unsigned char operator()(unsigned char b1, unsigned char b2);

private:
    size_t m_shmntR;
    size_t m_shmntL;
};

////////////////////////////////////////////////////////////////////////////////

class ShiftLeft
{
public:
    ShiftLeft(size_t shmnt);

    unsigned char operator()(unsigned char b1);

private:
    size_t m_shmntR;
    size_t m_shmntL;
    unsigned char m_prev;
};
 
////////////////////////////////////////////////////////////////////////////////

class NumBitsInByte
{
public:
	int operator()(int sum , unsigned char byte) const;
};

////////////////////////////////////////////////////////////////////////////////

class BytesToString
{
public:
    BytesToString(const unsigned char *bit_array, size_t bits_num);

    char operator()(char byte);

private:
    const unsigned char *m_bit_array;
    size_t m_bits_num;
};

////////////////////////////////////////////////////////////////////////////////

class FlipByte
{
public:
    char operator()(char byte);
};

////////////////////////////////////////////////////////////////////////////////

class AndBit
{
public:
    char operator()(char byte, char o_);
};

class OrBit
{
public:
    char operator()(char byte, char o_);
};

class XorBit
{
public:
    char operator()(char byte, char o_);
};

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
class BitArray
{
public:
    BitArray() : m_array(), m_size((((Size - 1) / 8) + 1))
    {}

    inline BitArray &SetAll()
    {
        fill(m_array, m_array + m_size, full_byte);
        ZeroUnusedBits(m_array + m_size - 1, Size);
        return (*this);
    }
    BitArray &Set(const size_t pos, const bool val);

    bool Get(size_t pos) const;

    inline BitArray &FlipAll()
    {
        transform(m_array, m_array + m_size, m_array, FlipByte());
        ZeroUnusedBits(m_array + m_size - 1, Size);
        return (*this);
    }
    BitArray &Flip(size_t pos);
    
    bool operator[](size_t pos) const;
    BitProxy operator[](size_t pos);

    bool operator==(const BitArray &o_) const;
    bool operator!=(const BitArray &o_) const;

    BitArray &operator&=(const BitArray &o_);
    BitArray &operator|=(const BitArray &o_);
    BitArray &operator^=(const BitArray &o_);

    BitArray &operator<<=(size_t shift);
    BitArray &operator>>=(size_t shift);

    string ToString() const;
    size_t CountBitsOn() const;

private:
    unsigned char m_array[((Size - 1) / 8) + 1];
    int m_size;
};

////////////////////////////////////////////////////////////////////////////////
//          BitArray Class - Functions Definitions - template class           //
////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::Set(const size_t pos, const bool val)
{
    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);

    if (val)
    {
        (m_array[BIT_CHAR(pos)] |= mask);
    }
    else
    {
        m_array[BIT_CHAR(pos)] &= ~(mask);
    }

    return (*this);
}

template <size_t Size>
bool BitArray<Size>::Get(size_t pos) const
{
    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);
    char temp = m_array[BIT_CHAR(pos)];

    return (temp &= mask);
}

template <size_t Size>
BitArray<Size> &BitArray<Size>::Flip(const size_t pos)
{
    char mask = 1;
    mask <<= (pos % BITS_IN_BYTE);
    m_array[BIT_CHAR(pos)] ^= mask;

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
bool BitArray<Size>::operator[](size_t pos) const
{
    return (this->Get(pos));
}

template <size_t Size>
BitProxy BitArray<Size>::operator[](size_t pos)
{
    size_t arr_index = pos / CHAR_BIT;
    unsigned char bit_index = pos % CHAR_BIT;

    return (BitProxy(m_array[arr_index], bit_index));
}

////////////////////////////////////////////////////////////////////////////////

// Return 1 if equal, 0 if not equal
template <size_t Size>
bool BitArray<Size>::operator==(const BitArray &o_) const
{
    return (equal(m_array, m_array + m_size, o_.m_array));
}

// Return 1 if not equal, 0 if equal
template <size_t Size>
bool BitArray<Size>::operator!=(const BitArray &o_) const
{
    return (!equal(m_array, m_array + m_size, o_.m_array));
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator&=(const BitArray &o_)
{
    transform(m_array, m_array + m_size, o_.m_array, m_array, AndBit());
    return (*this);
}

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator|=(const BitArray &o_)
{
    transform(m_array, m_array + m_size, o_.m_array, m_array, OrBit());
    return (*this);

}

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator^=(const BitArray &o_)
{
    transform(m_array, m_array + m_size, o_.m_array, m_array, XorBit());
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
BitArray<Size> &BitArray<Size>::operator<<=(size_t shift)
{
    ShiftLeftOp(m_array, Size, shift);

    return (*this);
}


template <size_t Size>
BitArray<Size> &BitArray<Size>::operator>>=(size_t shift)
{
    ShiftRightOp(m_array, Size, shift);

    return (*this);
}

////////////////////////////////////////////////////////////////////////////////

template < size_t Size >
inline std::string BitArray<Size>::ToString() const
{
    std::string str(Size, 0);
    std::transform(str.begin(), str.end(), str.begin(), 
                                        BytesToString(m_array, Size));

    return (str);
}

////////////////////////////////////////////////////////////////////////////////

template <size_t Size>
size_t BitArray<Size>::CountBitsOn() const
{
    return (accumulate(m_array, m_array + m_size, 0, NumBitsInByte()));
}

////////////////////////////////////////////////////////////////////////////////
//                     UTILITY FUNCTIONS DECLERATIONS                         //
////////////////////////////////////////////////////////////////////////////////

void ShiftRightOp(unsigned char *bit_array, size_t bits_num, size_t shift);
void ShiftLeftOp(unsigned char *bit_array, size_t bits_num, size_t shift);
void ZeroUnusedBits(unsigned char *bit_array_end, size_t bits_num);