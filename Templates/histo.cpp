
// Some prectice in C++ 'Histogram'

#include <iostream>
#include <map>
#include <vector>

using namespace std;

// g++ -std=c++98 -pedantic-errors -Wall -Wextra -g histo.cpp 
int main()
{
    map<string, int> word_num;
    vector<string> container;

    string input_word;

    vector<string>::iterator j;

    // Getting the input into the map and the vector
    while ("." != input_word)
    {
        getline (cin, input_word);
        ++word_num[input_word];
        
        if (1 == word_num[input_word])
        {
            container.push_back(input_word);
        }
    }
    word_num.erase(".");
    container.pop_back();

    // Printing out the information
    cout << "Histogram:" << endl;
    for (j = container.begin(); j != container.end(); ++j)
    {
        switch (word_num.at(*j))
        {
            case (1):
                cout << *j << endl;
                break;

            default:
                cout << word_num.at(*j) << " x " << *j << endl;
                break;
        }
    }

    return (0);
}