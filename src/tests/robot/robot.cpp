#include <atomic>

#include "core/Motor.h"
#include "core/Robot.h"
#include "core/ISocketClient.h"
#include "core/ISocketServer.h"
#include "core/TaskManager.h"

using namespace Robust;
using std::to_string;

// Note: Requires pi blaster to work

// TODO: find better way to communicate Robot Client with robot
std::atomic_int throttle;

// Class is designed for dual hbridge
class MotorController : public IMotorController
{
    int Pin1, Pin2;
    double Throttle;

  public:
    MotorController(int pin1, int pin2) : Pin1(pin1),
                                          Pin2(pin2)
    {
    }

    double GetThrottle()
    {
        return Throttle;
    }

    void SetThrottle(double value)
    {
        // Checks if the value is out of range
        if (value == Throttle) return;
        if (value > 1)
            value = 1;
        if (value < -1)
            value = -1;
        Throttle = value;
        int val1, val2;

        if (value > 0)
        {
            val1 = value;
            val2 = 0;
        }
        else
        {
            val1 = 0;
            val2 = value;
        }

        // System command that sets gpio;
        system(("echo " + to_string(Pin1) + "=" + to_string(val1) + " " +
                to_string(Pin2) + "=" + to_string(val2) + " > /dev/pi-blaster")
                   .c_str());
    }
};

class RobotClient : public ISocketClient
{
  public:
    RobotClient(int socket) : ISocketClient(socket)
    {
    }

    void Run()
    {
        std::string received;
        do
        {
            try
            {
                received = ReceiveData();
                // Janky way to get a throttle
                switch (received[0])
                {
                case '-':
                    throttle = -1;
                    break;
                case '0':
                    throttle = 0;
                    break;
                case '1':
                    throttle = 1;
                    break;
                }
            }
            catch (...)
            {
                Robust::err("An error has occured. Closing socket");
            }
        } while (received.size() > 0);
        close(Socket);
    }
};

class RobotServer : public ISocketServer
{
  public:
    RobotServer() : ISocketServer(20000)
    {
    }

  private:
    void HandleRequest(int port)
    {
        RobotClient socket(port);
        socket.Run();
    }
};

class TestRobot
{
    TaskManager Tasker;
    RobotServer SocketServer;
    MotorController LeftMotor, RightMotor;
    void UpdateMotors() {
        LeftMotor.SetThrottle(throttle);
        RightMotor.SetThrottle(throttle);
    }
public:
    TestRobot() : LeftMotor(27, 22), RightMotor(23, 24), Tasker(60)
    {
    }
    void Run() {
        Tasker.AddTask(std::bind(&TestRobot::UpdateMotors, this));
        SocketServer.Join();
    }
};

int main()
{
    TestRobot robot;
    robot.Run();
}