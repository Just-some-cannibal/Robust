#pragma once

namespace robust {
    class IMotorController {
    public:
        virtual void SetThrottle(double);
        virtual double GetThrottle();
        virtual ~IMotorController();
    };
}