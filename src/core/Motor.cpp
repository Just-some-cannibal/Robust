#include "core/Motor.h"

using namespace Robust;

Motor::Motor(IMotorController controller,
             double stallTorque,
             double loadlessSpeed,
             double load,
             double inertia,
             double opposingForce,
             double opposingFriction) : Controller(controller)
{
    SetStallTorque(stallTorque);
    SetLoadlessSpeed(loadlessSpeed);
    SetLoad(load);
    SetInertia(inertia);
    SetThrottle(0);
    SetOpposingForce(opposingForce);
    SetOpposingFriction(opposingFriction);
}

double Motor::GetStallTorque()
{
    return StallTorque;
}

void Motor::SetStallTorque(double stallTorque)
{
    // StallTorque is always a positive number
    StallTorque = fabs(StallTorque);
}

double Motor::GetLoadLessSpeed()
{
    return LoadlessSpeed;
}

void Motor::SetLoadlessSpeed(double loadlessSpeed)
{
    // LoadlessSpeed is always positive
    LoadlessSpeed = fabs(loadlessSpeed);
}

void Motor::SetThrottle(double throttle)
{
    // This method just forwards it to the motor controller
    Controller.SetThrottle(throttle);
}

double Motor::GetThrottle()
{
    // This method also forwards it to the motor controller
    return Controller.GetThrottle();
}

void Motor::SetSpeed(double speed)
{
    // If the speed is greater than the maxspeed, set throttle to 1
    if (fabs(speed) > GetMaxSpeed())
    {
        SetThrottle((speed > 0) ? 1 : -1);
        return;
    }
    
    double Force = OpposingFriction + OpposingForce;
    SetThrottle( speed / GetLoadLessSpeed() + Force / GetStallTorque() );
}

double Motor::GetSpeed()
{
    // Get speed is probably linked to some encoder specified by the user
    return Controller.GetSpeed();
}

double Motor::GetMaxSpeed()
{
    // As speed goes up, the amount of force able to be applied goes down
    // When there is no acceleration the net forces equal 0 therefore
    // OpposingForce + OpposingFriction = Force
    double Force = OpposingFriction + OpposingForce;

    return GetLoadLessSpeed() - Force * GetLoadLessSpeed() / GetStallTorque();
}

void Motor::SetLoad(double load)
{
    Load = fabs(load);
}

double Motor::GetLoad()
{
    return Load;
}

void Motor::SetInertia(double inertia)
{
    Inertia = fabs(inertia);
}

double Motor::GetInertia()
{
    return Inertia;
}

void Motor::SetOpposingForce(double force)
{
    OpposingForce = force;
}

double Motor::GetOpposingForce()
{
    return OpposingForce;
}

void Motor::SetOpposingFriction(double friction)
{
    OpposingFriction = fabs(friction);
}

double Motor::GetOpposingFriction()
{
    return OpposingFriction;
}