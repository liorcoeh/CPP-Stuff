
// Shared Pointer
// Since all the classes are templates, this is also the functions definitions
// file

#ifndef SHARED_POINTER_HPP
#define SHARED_POINTER_HPP

#include <iostream>

template<class T>
class SharedPointer
{
public:    
    explicit SharedPointer(T *ptr_);
    SharedPointer(const SharedPointer<T>& other_);
    ~SharedPointer();

    SharedPointer& operator=(const SharedPointer& other_);

    template<class C> friend class SharedPointer;
    
    template<class C>
    SharedPointer(const SharedPointer<C>& other_);

    template<class C>
    SharedPointer& operator=(const SharedPointer<C>& other_);

    T* operator->() const;

    T& operator*() const;
    

private:
    T *m_ptr;
    size_t *m_counter;
};

template<class T>
SharedPointer<T>::SharedPointer(T *ptr_) : m_ptr(ptr_)
{
    m_counter = new size_t;
    *m_counter = 1;
}

template<class T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& other_) : 
    m_ptr(other_.m_ptr), m_counter(other_.m_counter)
{
    ++(*m_counter);
}

template<class T>
template<class C>
SharedPointer<T>::SharedPointer(const SharedPointer<C>& other_) :
                            m_ptr(&(*other_)), m_counter(other_.m_counter)
{
    ++(*m_counter);
}


template<class T>
template<class C>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<C>& other_)
{
    if (m_ptr == other_.m_ptr)
    {
        return *this;
    }

    --(*m_counter);

    if (0 == *m_counter)
    {
        delete m_counter;
        delete m_ptr;
    }

    m_ptr = other_.m_ptr;
    m_counter = other_.m_counter;
    ++(*m_counter);

    return *this;
}

template<class T>
SharedPointer<T>::~SharedPointer()
{
    --(*m_counter);

    if (0 == *m_counter)
    {
        delete m_counter;
        delete m_ptr;
    }
}

template<class T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer<T>& other_)
{
    if (m_ptr == other_.m_ptr)
    {
        return *this;
    }

    --(*m_counter);

    if (0 == *m_counter)
    {
        delete m_counter;
        delete m_ptr;
    }

    m_ptr = other_.m_ptr;
    m_counter = other_.m_counter;
    ++(*m_counter);

    return *this;
}

template<class T>
T* SharedPointer<T>::operator->() const
{
    return (m_ptr);
}

template<class T>
T& SharedPointer<T>::operator*() const
{
    return (*m_ptr);
}

#endif // SHARED_POINTER_HPP
