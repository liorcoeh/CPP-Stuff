////////////////////////////////////////////////////////////////////////////////
// File Name: storage.hpp                                                     //
// Author: Lior Cohen                                                         //
// Date 05/08/2020                                                            //
// Purpose: header file for the storage class                                 //
//          Writes to and reads from the memeory device                       //
// Code Reviewer:                                              //
////////////////////////////////////////////////////////////////////////////////

#ifndef ILRD_RD8586_STORAGE_HPP
#define ILRD_RD8586_STORAGE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <boost/core/noncopyable.hpp>

using namespace std;

namespace ilrd
{

template <size_t BLOCK_SIZE>
class Storage:private boost::noncopyable
{
public:
    // Possible return status: 0 == SUCCESS, 1 == FAILED TO OPEN, 2 == FAILED TO WRITE, 3 == FAILED TO READ, 4 == OUT OF RANGE 
    explicit Storage(size_t num_of_blocks);
    // Write Function
    // Receives: index where to write data, pointer to source.
    // Returns: status of operation        
    void Write(size_t index, const void *src);
    // Read Function
    // Receives: index from where to read, pointer to store read data .
    // Returns: status of operation
    void Read(size_t index, void *dest) const;

    // GetCapacity Function
    // Receives: nothing.
    // Return: size_t number of blocks     
    inline size_t GetCapacity() const { return m_capacity; }
private:
    size_t m_capacity;
    string m_file_name;
};

template<size_t BLOCK_SIZE>
Storage<BLOCK_SIZE>::Storage(size_t num_of_blocks)
{
    this->m_capacity = num_of_blocks;
    m_file_name = "root_dir";
    ofstream file;
    file.open(m_file_name.c_str(), fstream::app);
    file.close();
}

template<size_t BLOCK_SIZE>
void Storage<BLOCK_SIZE>::Write(size_t index, const void *src)
{
    assert(index <= m_capacity);

    size_t offset = BLOCK_SIZE * index;
    fstream file;
    file.open(m_file_name.c_str());
    file.seekp(offset, ios_base::beg);
    file.write((char *)src, BLOCK_SIZE);
    file.close();
}

template<size_t BLOCK_SIZE>
void Storage<BLOCK_SIZE>::Read(size_t index, void *dest) const
{
    assert(index <= m_capacity);

    size_t offset = BLOCK_SIZE * index;
    fstream file;
    file.open(m_file_name.c_str());
    file.seekg(offset, ios_base::beg);
    file.read((char *)dest, BLOCK_SIZE);
    file.close();
}


} // namespace ilrd

#endif // ILRD_RD8586_STORAGE_HPP