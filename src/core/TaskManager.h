#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <chrono>
#include <unordered_map>
#include <time.h>

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
    static int Dt;
    static std::mutex Mutex;
    static std::unordered_map<int, Task> Tasks; // Map of all tasks

    static std::thread TaskThread; // Thead where the tasks are run on

    static void TaskHandler();

    static const int TimesPerSecond; // Number of times the tasks are run per second
  public:
    // Registers a task to be repeated and returns and id for use in removal
    static int AddTask(std::function<void(double)>);
    static void RemoveTask(int);
};
} // namespace Robust