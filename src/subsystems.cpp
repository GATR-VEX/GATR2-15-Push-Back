#include  "subsystems.hpp"
#include  "controls.hpp"

//Piston Port Definitions
pros::adi::DigitalOut flapPiston ('A');
pros::adi::DigitalOut parkerPiston ('B');
pros::adi::DigitalOut scraperPiston ('C');
pros::adi::DigitalOut pivotPiston ('D');
pros::adi::DigitalOut wingPiston ('E');

//Motor Port Definitions
pros::Motor IntakeLeft(-14, pros::MotorGearset::blue);
pros::Motor IntakeRight(15, pros::MotorGearset::blue);
pros::Motor OutakeLeft(-16, pros::MotorGearset::blue);
pros::Motor OutakeRight(17, pros::MotorGearset::blue);

//Define Initial States
bool initialFlap = false;
bool initialParker = false;
bool initialScraper = false;
bool initialPivot = false;
bool initialWing = false;

//Initialize In Case resetPiston() doesnt run
bool currentFlap = initialFlap;
bool currentParker = initialParker;
bool currentScraper = initialScraper;
bool currentPivot = initialPivot;
bool currentWing = initialWing;

//Run At Beginning of OPControl incase Auton Messed Anything Up
void resetPistons(){
    flapPiston.set_value(initialFlap);
    parkerPiston.set_value(initialParker);
    scraperPiston.set_value(initialScraper);
    pivotPiston.set_value(initialPivot);
    wingPiston.set_value(initialWing);
    
    currentFlap = initialFlap;
    currentParker = initialParker;
    currentScraper = initialScraper;
    currentPivot = initialPivot;
    currentWing = initialWing;
}

//Repeats During OPControl and Handles All Intake/Outake Motors
void intakeControl(){


    if(master.get_digital(currentButtons(Action::OUTTAKE)))
    {
        outake(); //This Means Score Balls
    }
    else{
        stopOutake(); //Stop Outake Motors
    }

    if(master.get_digital(currentButtons(Action::INTAKE)))
    {
        intake(); //This Means Intake From The Bottom
    }
    else{
        stopIntake(); //Stop Intaking
    }
    // Outake controls
    if(master.get_digital(currentButtons(Action::REVERSE)))
    {
        reverseOutake();//Reverses Motors at Top of Bot
        reverseIntake();//Reverses Intake
    }
}

void outake(){
    OutakeLeft.move(127);
    OutakeRight.move(127);
}

void reverseOutake(){
    OutakeLeft.move(-127);
    OutakeRight.move(-127);
}

void stopOutake(){
    OutakeLeft.move(0);
    OutakeRight.move(0);
}

void intake(){
    IntakeLeft.move(127);
    IntakeRight.move(127);
}

void reverseIntake(){
    IntakeLeft.move(-127);
    IntakeRight.move(-127);
}

void stopIntake(){
    IntakeLeft.move(0);
    IntakeRight.move(0);
}
//Repeats During OPControl and Handles All Pistons
void pistonControl(){

if (master.get_digital_new_press(currentButtons(Action::FLAP))) 
    {
        flapToggle();
    }

if (master.get_digital_new_press(currentButtons(Action::PARK))) 
    {
        parkerToggle();
    }

if (master.get_digital_new_press(currentButtons(Action::SCRAPER))) 
    {
        scraperToggle();
    }

if (master.get_digital_new_press(currentButtons(Action::PIVOT))) 
    {
        pivotToggle();
    }

if (master.get_digital(currentButtons(Action::WING)) && currentPivot) {
        wingPiston.set_value(false);
    }
else if(currentPivot){
        wingPiston.set_value(true);
    }

}

//There are Toggle Functions Seperate from the pistonControl function so that Auton can Call Them
//However, there is no WingToggle As it is Tied to the Pivot and Must be Manually Set to Positions in Auton
void flapToggle(){
    currentFlap = !currentFlap;
    flapPiston.set_value(currentFlap);
}

void parkerToggle(){
    currentParker = !currentParker;
    parkerPiston.set_value(currentParker); 
}

void scraperToggle(){
    currentScraper = !currentScraper;
    scraperPiston.set_value(currentScraper);
}

//Makes Wing Mirror Pivot Value
void pivotToggle(){
    currentPivot = !currentPivot;
    pivotPiston.set_value(currentPivot);
    
    wingPiston.set_value(currentPivot);
    currentWing = currentPivot;
}




