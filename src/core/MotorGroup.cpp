#include "core/MotorGroup.h"

using namespace Robust;

MotorGroup::MotorGroup(std::vector<Motor> motors) : Motors(motors)
{
}

MotorGroup::~MotorGroup()
{
}

void MotorGroup::SetThrottle(double throttle)
{
    for (Motor &motor : Motors)
        motor.SetThrottle(throttle);
}

void MotorGroup::SetSpeed(double speed)
{
    for (Motor &motor : Motors)
        motor.SetSpeed(speed);
}

double MotorGroup::GetAverageSpeed()
{
    double sum;
    for (Motor &motor : Motors)
        sum += motor.GetSpeed();
        
    return sum / Motors.size();
}