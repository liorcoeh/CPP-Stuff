
// Scope Lock
// Since the class is a template, this file is also the functions definitions
// file

#include <iostream>  // cout, cin, cerr
#include <pthread.h> // ptherad_mutex functions andd variables
#include <mutex>     // Mutex

template <typename T>
class ScopeLock
{
public:
    ScopeLock(T &lock);

    ~ScopeLock();

    // Cctor and assignment operator costructor are private so
    // the class is noncopyable
private:
    ScopeLock(const ScopeLock &other);
    ScopeLock &operator=(const ScopeLock &other);

    T &lock;
};

template <typename T>
ScopeLock<T>::ScopeLock(T &lock) : lock(lock)
{
    cout << "Locking mutex 'lock'" << endl;
    lock.lock();
}

template <typename T>
ScopeLock<T>::~ScopeLock()
{
    cout << "Unlocking mutex 'lock'\n" << endl;
    this->lock.unlock();
}