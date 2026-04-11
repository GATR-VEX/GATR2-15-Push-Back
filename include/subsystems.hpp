#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
extern pros::MotorGroup intake;
extern pros::MotorGroup lever;
extern pros::Motor trackingLever;

void resetPistons();
void pistonControl();

void intakeControl();
void setIntakeSpeed(int speed);

void slowButton();
extern double slowTurnMultiplier;
extern double slowDriveMultiplier;

void lever_Function();
void testToggle();
void testState(bool state);
extern pros::adi::DigitalOut pistonTest;

//Here Lies the Code from Before Worlds
/*

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

void intake(int speed = 127.);
void reverseIntake(int speed = 127);
void stopIntake();

void outake(int speed = 127);
void reverseOutake(int speed = 127);
void stopOutake();


// Your motors, sensors, etc. should go here.  Below are examples

extern pros::adi::DigitalOut flapPiston;
extern pros::adi::DigitalOut parkerPiston;
extern pros::adi::DigitalOut scraperPiston;
extern pros::adi::DigitalOut pivotPiston;
extern pros::adi::DigitalOut wingPiston;

extern pros::MotorGroup Intake;
extern pros::MotorGroup Outtake; */
