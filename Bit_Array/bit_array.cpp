
// Bit Array - Functions Definitions

#include "bit_array.hpp"


//////////////////////////// BitProxy Class ////////////////////////////////////

BitProxy &BitProxy::operator=(const BitProxy& rhs)
{
    return (*this = (bool)rhs);
}

BitProxy &BitProxy::operator=(bool val)
{
    char mask = 1;
    mask <<= (m_index % BITS_IN_BYTE);

    if (val)
    {
        m_byte |= mask;
    }
    else
    {
        m_byte &= ~(mask);
    }

    return (*this);
}

BitProxy::operator bool() const
{
    return (m_byte & (1ul << m_index));
}

bool BitProxy::operator!() const
{
    return (!(m_byte & (1ul << m_index)));
}


/////////////////////////// ShiftRight Class ///////////////////////////////////

ShiftRight::ShiftRight(size_t shmnt):
            m_shmntR(shmnt), m_shmntL(CHAR_BIT - shmnt)
{}

unsigned char ShiftRight::operator()(unsigned char b1, unsigned char b2)
{
    return ((b2 >> m_shmntR) | (b1 << m_shmntL));
}

/////////////////////////// ShiftLeft Class ///////////////////////////////////

ShiftLeft::ShiftLeft(size_t shmnt):
            m_shmntR(CHAR_BIT - shmnt), m_shmntL(shmnt), m_prev(0)
{}

unsigned char ShiftLeft::operator()(unsigned char b1)
{
    unsigned char res = (b1 << m_shmntL) | (m_prev >> m_shmntR);

    m_prev = b1;

    return (res);
}


////////////////////////// NumBitsInByte Class /////////////////////////////////

int NumBitsInByte::operator()(int sum , unsigned char byte) const
{ 
    unsigned char lut[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 
    4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 
    4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
    6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 
    5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
    6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 
    4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
    6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 
    6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 
    6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 
    6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 
    8, };
    return (sum + lut[byte]);
}


////////////////////////// BytesToString Class /////////////////////////////////

BytesToString::BytesToString(const unsigned char *bit_array, size_t bits_num):
        m_bit_array(bit_array), m_bits_num(bits_num)
{}

char BytesToString::operator()(char byte)
{
    (void)byte;

    --m_bits_num;

    // If the bits are outside of the bits number they wont be
    bool val = m_bit_array[m_bits_num / CHAR_BIT] &
                                (1ul << (m_bits_num % CHAR_BIT));

    return (val ? '1' : '0');
}


///////////////////////////// FlipByte Class ///////////////////////////////////

char FlipByte::operator()(char byte)
{
    return (~(byte));
}


/////////////////////// AndBit OrBit XorBit Classes ////////////////////////////

char AndBit::operator()(char byte, char o_)
{
    return (byte &= o_);
}

char OrBit::operator()(char byte, char o_)
{
    return (byte |= o_);
}

char XorBit::operator()(char byte, char o_)
{
    return (byte ^= o_);
}

////////////////////////////////////////////////////////////////////////////////
//                        UTILITY FUNCTIONS DEFINITIONS                       //
////////////////////////////////////////////////////////////////////////////////

void ShiftRightOp(unsigned char *bit_array, size_t bits_num, size_t shift)
{
    size_t bit_array_length = ((bits_num - 1) / CHAR_BIT) + 1;
    size_t in_arr_byte_index = shift / CHAR_BIT;
    size_t in_byte_bit_index = shift % CHAR_BIT;

    if (shift >= bits_num) 
    {
        in_arr_byte_index = bit_array_length;
    }

    if (((in_arr_byte_index + 1) < bit_array_length) &&
                                            (0 != in_byte_bit_index)) 
    {
        std::transform(bit_array + in_arr_byte_index + 1,
                       bit_array + bit_array_length,
                       bit_array + in_arr_byte_index,
                       bit_array + in_arr_byte_index,
                       ShiftRight(in_byte_bit_index));
    }

    bit_array[bit_array_length - 1] >>= in_byte_bit_index;

    if (0 != in_arr_byte_index) 
    {
        std::copy(bit_array + in_arr_byte_index, bit_array + bit_array_length,
                        bit_array);
    }

    std::fill(bit_array + (bit_array_length - in_arr_byte_index),
                        bit_array + bit_array_length, 0);
}


void ShiftLeftOp(unsigned char *bit_array, size_t bits_num, size_t shift)
{
    size_t bit_array_length = ((bits_num - 1) / CHAR_BIT) + 1;
    size_t in_arr_byte_index = shift / CHAR_BIT;
    size_t in_byte_bit_index = shift % CHAR_BIT;

    if (shift >= bits_num) 
    {
        in_arr_byte_index = bit_array_length;
    }

    if (0 != in_arr_byte_index) 
    {
        std::copy_backward(bit_array,
                           bit_array + (bit_array_length - in_arr_byte_index),
                           bit_array + bit_array_length);
    }

    if (((in_arr_byte_index + 1) < bit_array_length) &&
                                                (0 != in_byte_bit_index)) 
    {
        std::transform(bit_array + in_arr_byte_index,
                       bit_array + bit_array_length,
                       bit_array + in_arr_byte_index,
                       ShiftLeft(in_byte_bit_index));
    }

    ZeroUnusedBits(bit_array + bit_array_length - 1, bits_num);

    std::fill(bit_array, bit_array + in_arr_byte_index, 0);
}

void ZeroUnusedBits(unsigned char *bit_array_end, size_t bits_num)
{
    size_t unused_bits = (CHAR_BIT - bits_num) % CHAR_BIT;
    *bit_array_end &= full_byte >> unused_bits;
}