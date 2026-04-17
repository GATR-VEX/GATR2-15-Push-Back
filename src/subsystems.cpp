#include  "subsystems.hpp"
#include  "controls.hpp"


//Current Threshold for Lever
int current_threshold = 2000;

//Increment threshold when x is pressed
void incrementThreshold(){ 
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))
    {
        current_threshold += 50;
    }
}
//Piston Port Definitions
pros::adi::DigitalOut pivotPiston ('B');
pros::adi::DigitalOut wingPiston ('C');
pros::adi::DigitalOut flapPiston ('D');
pros::adi::DigitalOut scraperPiston ('E');


//Motor Definitions
pros::MotorGroup intake({-1, 2}); //Left Intake Motor is 9, Right Intake Motor is 10
pros::Motor trackingLever(7);
pros::MotorGroup lever({7, -8}); 


//Define Initial States
bool pivotInitialState = false;
bool wingInitialState = false;
bool flapInitialState = false;
bool scraperInitialState = false;

int leverState = 0;

//Set Current Variable to Initial State
bool pivotCurrent = pivotInitialState;
bool wingCurrent = wingInitialState;
bool flapCurrent = flapInitialState;
bool scraperCurrent = scraperInitialState;

//Multipliers for Slow Button
double slowTurnMultiplier = 1.00;
double slowDriveMultiplier = 1.00;
int flipVariable = 1;
int intakeSpeed = 127;

//Ensure Piston Variables Start In Initial States

void driveButtons(){
    if (master.get_digital(currentButtons(Action::SLOWBOT)))
    {
        slowTurnMultiplier = .8;
        slowDriveMultiplier = .35;
    }
    else
    {
        slowTurnMultiplier = 1.00;
        slowDriveMultiplier = 1.00;
    }
    
    if (master.get_digital(currentButtons(Action::REVERSEBOT)))
    {
        flipVariable = flipVariable*-1;
    }
}

void resetPistons(){
    pivotState(pivotInitialState);
    wingState(wingInitialState);
    flapState(flapInitialState);
    scraperState(scraperInitialState);
}

//Functions that Purely Toggle the Current Piston State
void pivotToggle(){
    pivotCurrent = !pivotCurrent;
    pivotState(pivotCurrent);
}
void wingToggle(){
    wingCurrent = !wingCurrent;
    wingState(wingCurrent);
}
void flapToggle(){
    flapCurrent = !flapCurrent;
    flapState(flapCurrent);
}
void scraperToggle(){
    scraperCurrent = !scraperCurrent;
    scraperState(scraperCurrent);
}

//Functions that Set Piston to a Specified State
void pivotState(bool state){
    pivotPiston.set_value(state);
    pivotCurrent = state;
}
void wingState(bool state){
    wingPiston.set_value(state);
    wingCurrent = state;
}
void flapState(bool state){
    flapPiston.set_value(state);
    flapCurrent = state;
}
void scraperState(bool state){
    scraperPiston.set_value(state);
    scraperCurrent = state;
}

void pistonControl(){
    if(master.get_digital_new_press(currentButtons(Action::PIVOT))){
        pivotToggle();
    }
    if(master.get_digital_new_press(currentButtons(Action::WING))){
        wingToggle();
    }
    if(master.get_digital_new_press(currentButtons(Action::FLAP))){
        flapToggle();
    }
    if(master.get_digital_new_press(currentButtons(Action::SCRAPER))){
        scraperToggle();
    }
}

void setIntakeSpeed(int speed){
    intake.move(speed);
}

void intakeControl(){
    if(master.get_digital(currentButtons(Action::INTAKE))) //Intake Forward
    {
        setIntakeSpeed(intakeSpeed);
    }
    else if(master.get_digital(currentButtons(Action::REVERSEINTAKE))) //Reverse Intake
    {
        setIntakeSpeed(-intakeSpeed);
    }
    else if(leverState == 0){
       setIntakeSpeed(0);
    }
}

void lever_Function(){ 
    while (true)
    {
        max_Lever_Function();
        slow_Lever_Function();
        reset_Lever();
        pros::delay(10);
    }
}

void max_Lever_Function(){
    lever.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    if (master.get_digital_new_press(currentButtons(Action::MAXLEVER)))
    {
        setIntakeSpeed(intakeSpeed);
        leverState = 1;
        while(trackingLever.get_current_draw() < current_threshold)
        {
            lever.move(127);
        }
        lever.move(0); 
        setIntakeSpeed(0);
        while(master.get_digital(currentButtons(Action::MAXLEVER)))
        {
            //Empty on Purpose Trust Me
        }

    
    }
}

void slow_Lever_Function(){ 
    lever.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    if (master.get_digital(currentButtons(Action::SLOWLEVER)))
    {
        setIntakeSpeed(0);
        leverState = 1;
        if(trackingLever.get_current_draw() < 900)
        {
            lever.move(50);
        }
       else
       {
            lever.move(0);
       }
    }
}

void reset_Lever(){
    if((leverState == 1 || leverState == 2) && trackingLever.get_current_draw() < 1000 && !master.get_digital(currentButtons(Action::SLOWLEVER)))
    {
        lever.move(-30);
        setIntakeSpeed(-intakeSpeed);
        leverState = 2;
    }
    else if(leverState == 2)
    {
        leverState = 0;
        lever.move(0);
        setIntakeSpeed(0);
    }
}

//Here Lies the Code from Before Worlds
/*
#include  "subsystems.hpp"


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
float stallCurrent = 1.8 * 1000;
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


void outake(int speed){
    outtakingDirection = 1;
    Outtake.move(speed);
}

void reverseOutake(int speed){
    outtakingDirection = -1;
    Outtake.move(-1 * speed);
}

void stopOutake(){
    outtakingDirection = 0;
    Outtake.move(0);
}

void intake(int speed){
    intakingDirection = 1;
    Intake.move(speed);
}

void reverseIntake(int speed){
    intakingDirection = -1;
    Intake.move(-1 * speed);
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
    printf("Attempting to set piston");
}

//Makes Wing Mirror Pivot Value
void pivotToggle(){
    currentPivot = !currentPivot;
    pivotPiston.set_value(currentPivot);
    
    wingPiston.set_value(currentPivot);
    currentWing = currentPivot;
}
*/



