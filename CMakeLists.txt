cmake_minimum_required(VERSION 3.1.0)
project(unitree_actuator_sdk)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(include)
include_directories(include/)
link_directories(lib)

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64") 
    set(EXTRA_LIBS libUnitreeMotorSDK_Arm64.so)
else()
    set(EXTRA_LIBS libUnitreeMotorSDK_Linux64.so)
endif()

#example

add_executable(example_goM8010_6_motor motor_scripts/example_goM8010_6_motor.cpp)
target_link_libraries(example_goM8010_6_motor ${EXTRA_LIBS})

add_executable(changeID motor_scripts/changeID.cpp)
target_link_libraries(changeID ${EXTRA_LIBS})

# Add motor_manager target
add_library(motor_manager STATIC motor_scripts/MotorManager.cpp)
target_link_libraries(motor_manager ${EXTRA_LIBS})

add_executable(test_single_mm motor_scripts/test_single_mm.cpp)
target_link_libraries(test_single_mm PUBLIC
    ${EXTRA_LIBS}
    motor_manager)

