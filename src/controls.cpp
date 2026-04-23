#include "controls.hpp"

pros::controller_digital_e_t WillScheme(Action action){
    switch (action){
    case Action::REVERSEINTAKE: 
        return pros::E_CONTROLLER_DIGITAL_R2; 
    case Action::SCRAPER: 
        return pros::E_CONTROLLER_DIGITAL_B;
    case Action::INTAKE: 
        return pros::E_CONTROLLER_DIGITAL_R1;
    case Action::WING:
        return pros::E_CONTROLLER_DIGITAL_Y;
    case Action::PIVOT:
        return pros::E_CONTROLLER_DIGITAL_L1;
    //case Action::SNAPUP:
    //    return pros::E_CONTROLLER_DIGITAL_UP;
    //case Action::SNAPDOWN:
    //    return pros::E_CONTROLLER_DIGITAL_DOWN;
    case Action::MAXLEVER:  
        return pros::E_CONTROLLER_DIGITAL_A;
    case Action::SLOWLEVER: 
        return pros::E_CONTROLLER_DIGITAL_X;
    case Action::SLOWBOT:
        return pros::E_CONTROLLER_DIGITAL_DOWN;
    case Action::REVERSEBOT:
        return pros::E_CONTROLLER_DIGITAL_L2;

    default:
        return NO_BUTTON;
    }
}

pros::controller_digital_e_t DavidScheme(Action action){
    switch (action){
    case Action::REVERSEINTAKE:
        return pros::E_CONTROLLER_DIGITAL_B;
    case Action::SCRAPER:
        return pros::E_CONTROLLER_DIGITAL_DOWN;
    case Action::INTAKE:
        return pros::E_CONTROLLER_DIGITAL_R1;
    case Action::WING:
        return pros::E_CONTROLLER_DIGITAL_L1;
    case Action::PIVOT:
        return pros::E_CONTROLLER_DIGITAL_RIGHT;
    //case Action::SNAPUP:
    //    return pros::E_CONTROLLER_DIGITAL_UP;
    //case Action::SNAPDOWN:
    //    return pros::E_CONTROLLER_DIGITAL_DOWN;
    case Action::SLOWBOT:
        return pros::E_CONTROLLER_DIGITAL_L2;
    case Action::MAXLEVER:
        return pros::E_CONTROLLER_DIGITAL_R2;
    case Action::SLOWLEVER:
        return pros::E_CONTROLLER_DIGITAL_Y;
    default:
        return NO_BUTTON;
    }
}

                     
//This is the Current Default Value
pros::controller_digital_e_t (*currentButtons )(Action) = DavidScheme;

//When Determining Driver in Auton, use the sytnax currentButtons = DavidScheme or currentButtons = WillScheme