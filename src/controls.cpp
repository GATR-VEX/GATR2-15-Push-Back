#include "controls.hpp"

pros::controller_digital_e_t WillScheme(Action action){
    switch (action){
    case Action::REVERSE:
        return pros::E_CONTROLLER_DIGITAL_R2;
    case Action::FLAP:
        return pros::E_CONTROLLER_DIGITAL_A;
    case Action::PIVOT:
        return pros::E_CONTROLLER_DIGITAL_L2;
    case Action::SCRAPER:
        return pros::E_CONTROLLER_DIGITAL_X;
    case Action::INTAKE:
        return pros::E_CONTROLLER_DIGITAL_R1;
    case Action::WING:
        return pros::E_CONTROLLER_DIGITAL_L1;
    case Action::PARK:
        return pros::E_CONTROLLER_DIGITAL_B;
    case Action::SNAPUP:
        return pros::E_CONTROLLER_DIGITAL_UP;
    case Action::SNAPDOWN:
        return pros::E_CONTROLLER_DIGITAL_DOWN;
    case Action::SNAPLEFT:
        return pros::E_CONTROLLER_DIGITAL_LEFT;
    case Action::SNAPRIGHT:
        return pros::E_CONTROLLER_DIGITAL_RIGHT;
   
    default:
        return NO_BUTTON;
    }
}

pros::controller_digital_e_t DavidScheme(Action action){
    switch (action){
    case Action::REVERSE:
        return pros::E_CONTROLLER_DIGITAL_L2;
    case Action::FLAP:
        return pros::E_CONTROLLER_DIGITAL_Y;
    case Action::PIVOT:
        return pros::E_CONTROLLER_DIGITAL_B;
    case Action::SCRAPER:
        return pros::E_CONTROLLER_DIGITAL_A;
    case Action::INTAKE:
        return pros::E_CONTROLLER_DIGITAL_R1;
    case Action::WING:
        return pros::E_CONTROLLER_DIGITAL_RIGHT;
    case Action::PARK:
        return pros::E_CONTROLLER_DIGITAL_UP;
    case Action::SNAPUP:
        return pros::E_CONTROLLER_DIGITAL_UP;
    case Action::SNAPDOWN:
        return pros::E_CONTROLLER_DIGITAL_DOWN;
    case Action::SLOWBOT:
        return pros::E_CONTROLLER_DIGITAL_L1;
    case Action::REVIVE:
        return pros::E_CONTROLLER_DIGITAL_LEFT;
    default:
        return NO_BUTTON;
    //Only Run Lower Half Intake Reverse Down Arrow
    }
}


//This is the Current Default Value
pros::controller_digital_e_t (*currentButtons )(Action) = WillScheme;

//When Determining Driver in Auton, use the sytnax currentButtons = DavidScheme or currentButtons = WillScheme