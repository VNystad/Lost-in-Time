#include <iostream>
#include "teststate.h"
#include "../app.h"


void TestState::GoNext(Machine &machine)
{
    TestApp testapp;

    while(testapp.Tick());
}