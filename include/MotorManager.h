#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"

class SingleMotorManager {
    private:
        MotorCmd cmd[6];
        MotorData data[6];
        SerialPort serial;
    public:
        float raw_q_motor[6];
        float raw_dq_motor[6];
        SingleMotorManager();
        ~SingleMotorManager();
        void update();
        void printMotorData();
};