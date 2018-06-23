#pragma once

#include <vector>

#include "core/Motor.h"

namespace Robust
{
class MotorGroup
{
  public:
    std::vector<Motor> Motors;

    MotorGroup(std::vector<Motor> motors);
    ~MotorGroup();

    void SetThrottle(double throttle);

    void SetSpeed(double speed);
    // Getters are impossible because motors can still be individually set
    double GetAverageSpeed();
};
} // namespace Robust