#include "MotorManager.h"

int main() {
    SingleMotorManager motorManager;
    while (1) {
        motorManager.update();
        motorManager.printMotorData();
        usleep(200);
    }
}