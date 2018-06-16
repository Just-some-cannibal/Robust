#include "core/TaskManager.h"

using namespace Robust;

Task::Task(std::function<void(double)> function) : Function(function),
                                                   LastTimeExecuted(system_clock::now())
{
}

std::thread TaskManager::TaskThread(&TaskManager::TaskHandler);

const int TimesPerSecond(60);

int TaskManager::AddTask(std::function<void(double)> function)
{
    // Clock should generate unique id
    int id = clock();
    Mutex.lock();
    Task task(function);
    Tasks[id] = task;
    Mutex.unlock();
    return id;
}

void TaskManager::RemoveTask(int id)
{
    Mutex.lock();
    Tasks.erase(id);
    Mutex.unlock();
}

void TaskManager::TaskHandler()
{
    auto start = system_clock::now();
    for (const auto &pair : Tasks)
    {
        Mutex.lock();
        const Task &task = pair.second;
        double dt = duration_cast<milliseconds>(task.LastTimeExecuted-system_clock::now()).count();
        auto &func = task.Function;
        func(dt);
        Mutex.unlock();
    }
    milliseconds idealTime(1000 / TimesPerSecond);
    std::this_thread::sleep_for(idealTime - (system_clock::now() - start));
}