#include "util/logger.h"
using namespace std::chrono;

void Robust::log (std::string log) {
  std::time_t t = system_clock::to_time_t(system_clock::now());
  std::cerr << std::put_time(std::localtime(&t), " [ %FT%T%z ] [LOG]") << log << std::endl;
}

void Robust::err (std::string log) {
  std::time_t t = system_clock::to_time_t(system_clock::now());
  std::cerr << std::put_time(std::localtime(&t), " [ %FT%T%z ] [ERROR]") << log << std::endl;
}