#include <filesystem>
#include <unistd.h>
#include "MotorManager.h"
#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"

SingleMotorManager::SingleMotorManager():
    serial("/dev/ttyUSB0")
{
    for (int i = 0; i < 6; i++) {
        raw_q_motor[i] = 0.0;
        raw_dq_motor[i] = 0.0;
        cmd[i].motorType = MotorType::GO_M8010_6;
        data[i].motorType = MotorType::GO_M8010_6;
        cmd[i].mode = queryMotorMode(MotorType::GO_M8010_6,MotorMode::FOC);
        cmd[i].id   = i;
        cmd[i].kp   = 0.0;
        cmd[i].kd   = 0.0;
        cmd[i].tau = 0.0;
    }
}

void SingleMotorManager::update() {
    for (int i = 0; i < 6; i++) {
        serial.sendRecv(&cmd[i], &data[i]);
        raw_q_motor[i] = data[i].q;
        raw_dq_motor[i] = data[i].dq;
    }
}

void SingleMotorManager::printMotorData() {
    std::cout << "==================================================" << std::endl;
    for (int i = 0; i < 6; i++) {
        std::cout << "Motor " << i << ": " << std::endl;
        std::cout << "  q: " << data[i].q << std::endl;
        std::cout << "  dq: " << data[i].dq << std::endl;
        std::cout << "  temp: " << data[i].temp << std::endl;
        std::cout << "  merror: " << data[i].merror << std::endl;
    }
}

SingleMotorManager::~SingleMotorManager() {
}