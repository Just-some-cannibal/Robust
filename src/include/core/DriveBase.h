#pragma once

#include <vector>
#include "core/Motor.h"

namespace robust
{
class DriveBase
{
  public:
    // Takes groups of motors that will be assigned to left and right sidesF
    DriveBase(std::vector<Motor> LeftMotors,
              std::vector<Motor> RightMotors);
};
} // namespace robust