#include <iostream>
#include "teststate.h"
#include "../testapp.h"


void TestState::GoNext(Machine &machine)
{
    TestApp testapp;

    while(testapp.Tick());
}