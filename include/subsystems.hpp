#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
extern pros::MotorGroup intake;
extern pros::MotorGroup lever;
extern pros::Motor trackingLever;
extern pros::adi::DigitalOut outtakePiston;
extern pros::adi::DigitalOut wingPiston;
extern pros::adi::DigitalOut gatePiston;
extern int current_threshold;
//extern pros::adi::DigitalOut outtakePiston;

void resetPistons();
void pistonControl();
void incrementThreshold();

void intakeControl();
void setIntakeSpeed(int speed);

void driveButtons();
extern double slowTurnMultiplier;
extern double slowDriveMultiplier;
extern int flipVariable;



void lever_Function();
void slow_Lever_Function();
void max_Lever_Function();
void reset_Lever();
void pivotToggle();
void wingToggle();
void flapToggle();
void scraperToggle();
void pivotState(bool state);
void wingState(bool state);
void flapState(bool state);
void scraperState(bool state);

void intakeToggle();
void reverseIntakeToggle();
void middleLowReverseIntakeToggle();

void auton_lever();
void auton_middle_lever();


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
