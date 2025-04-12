#include <unistd.h>
#include "serialPort/SerialPort.h"
#include "unitreeMotor/unitreeMotor.h"


int main() {
  float kp_des = 0.05;
  float max_torque = 0.1;
  SerialPort  serial("/dev/ttyUSB0");
  MotorCmd    cmd;
  MotorData   data;
  int c = 0;
  while(true) 
  {
    cmd.motorType = MotorType::GO_M8010_6;
    data.motorType = MotorType::GO_M8010_6;
    cmd.mode = queryMotorMode(MotorType::GO_M8010_6,MotorMode::FOC);
    cmd.id   = 0;
    cmd.tau = 1.0;
    float delta = cmd.q - data.q;
    float torque = delta * kp_des;
    if ((torque > max_torque)) {
      cmd.kp = 0.0;
      //cmd.tau = max_torque;
    }
    else if ((torque < -1 * max_torque)) {
      cmd.kp = 0.0;
      //cmd.tau = -1 * max_torque;
    }
    else {
      cmd.kp = kp_des;
    }
    cmd.kd = 0.0;
    cmd.dq = 0.0*queryGearRatio(MotorType::GO_M8010_6);
    //cmd.tau  = 0.0;
    serial.sendRecv(&cmd,&data);

    std::cout <<  std::endl;
    std::cout <<  "motor.q: "    << data.q    <<  std::endl;
    std::cout <<  "motor.temp: "   << data.temp   <<  std::endl;
    std::cout <<  "motor.W: "      << data.dq      <<  std::endl;
    std::cout <<  "motor.merror: " << data.merror <<  std::endl;
    std::cout <<  "motor.kp: " << cmd.kp <<  std::endl;
    std::cout <<  "motor.q: " << cmd.q <<  std::endl;
    std::cout <<  std::endl;
    c++;
    usleep(200);
  }

}
