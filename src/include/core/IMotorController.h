#pragma once

namespace Robust {
    class IMotorController {
    public:
        virtual void SetThrottle(double) {}
        virtual double GetThrottle() {}
        virtual ~IMotorController() {}
    };
}