#include <iostream>
#include "state/machine.h"

int main()
{
    // Create Machine
    Machine machine;

    // run until running flag is false
    while(machine.GetRunning())
        machine.GoNext();

    return 0;
}