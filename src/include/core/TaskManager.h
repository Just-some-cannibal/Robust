#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <chrono>
#include <unordered_map>
#include <time.h>
#include "util/logger.h"

using namespace std::chrono;

namespace Robust
{
class Task
{
  public:
    // Takes in a function that receives delta time when called
    // IMPORTANT!: Bind method to its object to get rid of its first argument
    // Eg. std::bind (&Foo::bar, &foo)
    Task();
    Task(std::function<void(double)>);
    std::function<void(double)> Function;
    time_point<system_clock> LastTimeExecuted;
};

class TaskManager
{
    int Dt;
    std::mutex Mutex;
    std::unordered_map<int, Task> Tasks; // Map of all tasks

    std::thread TaskThread; // Thead where the tasks are run on

    void TaskHandler();

    const int TimesPerSecond; // Number of times the tasks are run per second
  public:
    TaskManager(int);
    // Registers a task to be repeated and returns and id for use in removal
    int AddTask(std::function<void(double)>);
    void RemoveTask(int);
};

} // namespace Robust