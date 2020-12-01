

#include <iostream>

#include "minion.hpp"

using namespace  std;
using namespace ilrd;

int main()
{
    Minion main_minion(8080, 256, 8050);

    main_minion.Run();
    
    return (0);
}