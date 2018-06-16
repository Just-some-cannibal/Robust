#pragma once

#include <exception>
#include <thread>
#include "core/IMotorController.h"

namespace robust
{

class Motor
{
  double StallTorque;          // Max torque without slippage
  double LoadlessSpeed;        // Max Speed with no load
  double Throttle;             // Voltages are handled by IMotorControllers
  double Load;                 // Current load in newton meters: Does not include gearbox
  double Inertia;              // Inertia of gearbox
  IMotorController Controller; // The low level interface to the motor
public:
  // The only required parameter is the controller. The rest default to zero if not set
  Motor(IMotorController controller,
        double stallTorque,
        double loadlessSpeed,
        double load,
        double inertia);

  double GetStallTorque();
  void SetStallTorque(double);

  double GetLoadLessSpeed();
  void SetLoadlessSpeed(double);

  // Value is between -1 and 1
  // Does not throw error and instead uses -1 or 1 if out of bounds
  void SetThrottle(double);
  double GetThrottle();

  // High level function that sets the throttle based on
  // the stall torque, loadless speed and opposing friction
  // Speed is in meters per second
  // Note: If a speed is given that is higher than the max speed, it will throw std::exception
  void SetSpeed(double);
  double GetSpeed();

  // Predicts the absolute maximum speed that can be given with current set up
  double GetMaxSpeed();

  void SetLoad(double);
  double GetLoad(double);

  void SetInertia(double); // Probably won't (and shouldn't) change
  double GetInertia(double);
};

} // namespace robust
