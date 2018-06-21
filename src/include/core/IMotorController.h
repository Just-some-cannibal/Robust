#pragma once

namespace Robust {
    class IMotorController {
    public:
        virtual void SetThrottle(double) {}
        virtual double GetThrottle() {return 0;}
        virtual double GetSpeed() {return 0;}
        virtual ~IMotorController() {}
    };
}