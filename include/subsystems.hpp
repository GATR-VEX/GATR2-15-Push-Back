#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
void resetPistons();
void pistonControl();
void intakeControl();
void jamControl();

void flapToggle();
void parkerToggle();
void scraperToggle();
void pivotToggle();
void wingHold();

void intake();
void reverseIntake();
void stopIntake();

void outake();
void reverseOutake();
void stopOutake();


// Your motors, sensors, etc. should go here.  Below are examples

extern pros::adi::DigitalOut flapPiston;
extern pros::adi::DigitalOut parkerPiston;
extern pros::adi::DigitalOut scraperPiston;
extern pros::adi::DigitalOut pivotPiston;
extern pros::adi::DigitalOut wingPiston;

extern pros::MotorGroup Intake;
extern pros::MotorGroup Outtake;
