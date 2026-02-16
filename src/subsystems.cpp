#include  "subsystems.hpp"
#include  "controls.hpp"

//Piston Port Definitions
pros::adi::DigitalOut flapPiston ('A');
pros::adi::DigitalOut parkerPiston ('B');
pros::adi::DigitalOut scraperPiston ('C');
pros::adi::DigitalOut pivotPiston ('D');
pros::adi::DigitalOut wingPiston ('E');

//Motor Port Definitions
pros::MotorGroup Intake({-14, 15});
pros::MotorGroup Outtake({-16, 17});

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

// initialize intaking direction
int intakingDirection = 0; // 0 for off, 1 for forward, -1 for backwards
int outtakingDirection = 0; // 0 for off, 1 for forward, -1 for backwards

// track whether or not we're attempting to anti jam
bool antiJamIntake = false;
bool antiJamOuttake = false;

// track when we started to run anti jam
uint32_t antiJamIntakeStartTime;
uint32_t antiJamOuttakeStartTime;

// how long anti jam run (ms)
float antiJamIntakeTime = 250;
float antiJamOuttakeTime = 250;

// approx stall current in ms (tested using terminal to find actual stall current)
float stallCurrent = 1.9 * 1000;
// number of instances it needs to see stall current consecutively to avoid one spike trigger anti jam
// in particular on motor start up current is high due to no back emf limiting current
float spikeThreshold = 25; 

float currentSpikesIntake = 0; // number of consecutive instances of stall current on intake
float currentSpikesOuttake = 0; // number of consecutive instances of stall current on outtake

int iterations = 0;

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

    iterations++;

    if (iterations % 50 == 0){
        printf("current: %.2f AND %.2f\n", double(Intake.get_current_draw(0)), double(Intake.get_current_draw(1)));
    }
    if(master.get_digital(currentButtons(Action::OUTTAKE)) && !antiJamOuttake) {
        outake(); //This Means Score Balls
    } else if (!master.get_digital(currentButtons(Action::REVERSE)) && !master.get_digital(currentButtons(Action::OUTTAKE))){
        stopOutake(); //Stop Outake Motors
    }

    if(master.get_digital(currentButtons(Action::INTAKE)) && !antiJamIntake) {
        intake(); //This Means Intake From The Bottom
    } else if (!master.get_digital(currentButtons(Action::REVERSE)) && !master.get_digital(currentButtons(Action::INTAKE))){
        stopIntake(); //Stop intake Motors
    }

    if(master.get_digital(currentButtons(Action::REVERSE)) && !(antiJamIntake || antiJamOuttake)) {
        reverseOutake();//Reverses Motors at Top of Bot
        reverseIntake();//Reverses Intake
    }
}


void jamControl(){
    // true if outtake is stalling AND it's currently outtaking and we're not already trying to anti jam (however if we get jammed while trying to unjam we're cooked)
    if (((Outtake.get_current_draw(0) > stallCurrent) || (Outtake.get_current_draw(1) > stallCurrent)) && outtakingDirection && !antiJamOuttake){
        currentSpikesOuttake ++;

        if (currentSpikesOuttake > spikeThreshold){
            antiJamOuttake = true;

            // reverses current direction
            Outtake.move(127 * outtakingDirection * -1);
            antiJamOuttakeStartTime = pros::millis();
        }
    } else {
        currentSpikesOuttake = 0;
    }


    // true if intake is stalling AND it's currently stalling
    // but if intake is stalling and we're not intending to intake we're probably cooked already 
    if (((Intake.get_current_draw(0) > stallCurrent) || (Intake.get_current_draw(1) > stallCurrent)) && intakingDirection && !antiJamIntake){
        currentSpikesIntake++;

        if (currentSpikesIntake > spikeThreshold){
            antiJamIntake = true;

            // reverses current direction
            Intake.move(127 * intakingDirection * -1);
            antiJamIntakeStartTime = pros::millis();
        }
    } else {
        currentSpikesIntake = 0;
    }

    if (antiJamOuttake){
        if ((pros::millis() - antiJamOuttakeStartTime) > antiJamOuttakeTime){
            antiJamOuttake = false;
            Outtake.move(127 * outtakingDirection); // sets back to normal direction
        }
    }

    if (antiJamIntake){
        if ((pros::millis() - antiJamIntakeStartTime) > antiJamIntakeTime){
            antiJamIntake = false;
            Intake.move(127 * intakingDirection); // sets back to normal direction
        }
    }
}


void outake(){
    outtakingDirection = 1;
    Outtake.move(127);
}

void reverseOutake(){
    outtakingDirection = -1;
    Outtake.move(-127);
}

void stopOutake(){
    outtakingDirection = 0;
    Outtake.move(0);
}

void intake(){
    intakingDirection = 1;
    Intake.move(127);
}

void reverseIntake(){
    intakingDirection = -1;
    Intake.move(-127);
}

void stopIntake(){
    intakingDirection = 0;
    Intake.move(0);
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




