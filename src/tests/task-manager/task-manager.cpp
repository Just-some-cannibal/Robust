#include <core/TaskManager.h>
#include <iostream>
#include <util/logger.h>
#include <string>

using namespace std::chrono_literals;

void testFunc(double dt)
{
    static int i = 0;
    if (i % 20 == 0)
        Robust::log("Hello World!");
    i++;
}

int main()
{
    Robust::TaskManager tasker(60);

    int id = tasker.AddTask(&testFunc);

    Robust::log("Added task to tasker");

    std::this_thread::sleep_for(5s);

    Robust::log("Removing Task. No more should appear after");

    tasker.RemoveTask(id);

    std::this_thread::sleep_for(5s);
}