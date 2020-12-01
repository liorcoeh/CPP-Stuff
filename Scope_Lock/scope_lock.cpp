
// Scope Lock - Test File

#include "scope_lock.hpp"

using namespace std;

#define SIZE (100)

int g_nTest = 0;
int g_array[SIZE] = {0};
std::mutex g_mutex;

// Function to add 1 to each cell in the g_array
void *ProducerFunc(void *unused);

// Function to print the g_array
void *ConsumerFunc(void *unused);

////////////////////////////////////////////////////////////////////////////////
//                                 Main:                                      //
////////////////////////////////////////////////////////////////////////////////

int main()
{
    pthread_t producer;
    pthread_t consumer;
    int counter = 5;

    for (int i = 0; i < counter; ++i)
    {
        if (pthread_create(&producer, NULL, &ProducerFunc, NULL))
        {
            cout << "ERROR in pthread_create (producer)" << endl;
            return (1);
        }

        if (pthread_create(&consumer, NULL, &ConsumerFunc, NULL))
        {
            cout << "ERROR in pthread_create (producer)" << endl;
            return (1);
        }

        pthread_join(producer, NULL);
        pthread_join(consumer, NULL);
    }

    return (0);
}

////////////////////////////////////////////////////////////////////////////////
//                            UTILITY FUNCTIONS                               //
////////////////////////////////////////////////////////////////////////////////

void *ProducerFunc(void *unused)
{
    unused = unused;

    cout << "Entered ProducerFunc" << endl;
    
    ScopeLock<mutex> critical_section(g_mutex);
    for (int i = 0; i < SIZE; ++i)
    {
        ++g_array[i];
    }
    cout << endl;

    return (NULL);
}

void *ConsumerFunc(void *unused)
{
    unused = unused;

    cout << "Entered ConsumerFunc" << endl;
    
    ScopeLock<mutex> critical_section(g_mutex);
    for (int i = 0; i < SIZE; ++i)
    {
        cout << g_array[i] << "->";
    }
    cout << endl;

    return (NULL);
}
