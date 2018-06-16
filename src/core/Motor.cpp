#include "core/Motor.h"

using namespace robust;

Motor::Motor(IMotorController controller,
             double stallTorque,
             double loadlessSpeed,
             double load,
             double inertia) : Controller(controller)
{
    SetStallTorque(stallTorque);
    SetLoadlessSpeed(loadlessSpeed);
    SetLoad(load);
    SetInertia(inertia);
    SetThrottle(0);
}
