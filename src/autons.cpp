#include "main.h"
#include "controls.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int SLOW_DRIVE_SPEED = 50;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void XDriveAutonTest(){
  xdriveChassis.ZeroAutonInput();
  xdriveChassis.ZeroDriverInput();

  xdriveChassis.Move_Set(5, 0, 0);
  xdriveChassis.AutonExecute();
}





void skillsAutonRightConstants(){
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.5, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void clearParkingConstants() {
  // --- PID (slightly more aggressive + more damping) ---
  chassis.pid_drive_constants_set(22.0, 0.0, 115.0);      // was (20,0,100)
  chassis.pid_heading_constants_set(13.0, 0.0, 24.0);     // was (11,0,20)

  // Turns: a bit more P/D, way less I so it doesn't "creep" / overshoot late
  chassis.pid_turn_constants_set(3.6, 0.01, 26.0, 10.0);  // was (3,0.05,20,15)
  chassis.pid_swing_constants_set(6.5, 0.0, 70.0);        // was (6,0,65)

  // Odom angular: more D helps it stop “right now” instead of drifting into heading
  chassis.pid_odom_angular_constants_set(7.2, 0.0, 60.0);     // was (6.5,0,52.5)
  chassis.pid_odom_boomerang_constants_set(6.2, 0.0, 38.0);   // was (5.8,0,32.5)

  // --- Exit conditions (tighter, but not slow) ---
  // Params are: time-in-small-window, small-window, time-in-big-window, big-window, still-time, max-amps-time :contentReference[oaicite:3]{index=3}
  chassis.pid_turn_exit_condition_set(70_ms, 2_deg, 200_ms, 5_deg, 350_ms, 450_ms);
  chassis.pid_swing_exit_condition_set(70_ms, 2_deg, 200_ms, 5_deg, 350_ms, 450_ms);

  chassis.pid_drive_exit_condition_set(70_ms, 0.5_in, 200_ms, 1.5_in, 350_ms, 450_ms);
  chassis.pid_odom_turn_exit_condition_set(70_ms, 2_deg, 200_ms, 5_deg, 350_ms, 550_ms);
  chassis.pid_odom_drive_exit_condition_set(70_ms, 0.5_in, 200_ms, 1.5_in, 350_ms, 550_ms);

  // --- Chaining (if you use quick_chain anywhere near precision, keep it tiny) ---
  chassis.pid_turn_chain_constant_set(1.5_deg);
  chassis.pid_swing_chain_constant_set(2.5_deg);
  chassis.pid_drive_chain_constant_set(1_in);

  // --- Slew (tiny ramp so you don’t slip on micro-moves) ---
  // Slew limits the max PID output early in the move to reduce slip/tip :contentReference[oaicite:4]{index=4}
  chassis.slew_turn_constants_set(2_deg, 60);
  chassis.slew_drive_constants_set(2_in, 70);
  chassis.slew_swing_constants_set(2_in, 70);

  // With tracking wheels you can bias turning more in odom (up to 1.0)
  chassis.odom_turn_bias_set(0.95);

  chassis.pid_angle_behavior_set(ez::shortest);
}

void matchAutonLeft(){
  currentButtons = WillScheme;
}

void matchAutonRight(){
  skillsAutonRightConstants();
  currentButtons = DavidScheme;

  chassis.pid_turn_set(90, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(90, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(90, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(90, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
}

//SKILLS AUTON RIGHT
void skillsAutonRight(){
  skillsAutonRightConstants();

  pivotPiston.set_value(true);

  
  // initial straight line towards match loader
  chassis.pid_odom_set(26.5_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();

  // enable scraper for match loader
  scraperToggle();

  // align bot intake with match loader
  chassis.pid_turn_set(90, DRIVE_SPEED, true);
  chassis.pid_wait_quick();

  // turn intake/outtake on
  intake();
  outake();

  // go towards match loader
  chassis.pid_odom_set(8_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //pros::delay(10000);
  
  // cracking the match loader
  for (int i = 0; i < 4; i++){
      chassis.pid_odom_set(-3_in, DRIVE_SPEED, false);
      chassis.pid_wait();
      chassis.pid_odom_set(3.5_in, DRIVE_SPEED, false);
      chassis.pid_wait();

      // once balls fill up more of the top stop running outtake 
      //if (i == 1){
        //outake(127);
     // }
    }

    // go backwards from matchloader
    chassis.pid_odom_set(-8.5_in, DRIVE_SPEED, true);
    chassis.pid_wait_quick();

    // pulll scraper back in
    scraperToggle();

    // align with balls on the wall
    chassis.pid_turn_set(0, DRIVE_SPEED, true);
    chassis.pid_wait_quick();

    // go towards ball on wall
    chassis.pid_odom_set(14_in, DRIVE_SPEED, false);
    chassis.pid_wait_quick();

    // back up from balls on wall
    chassis.pid_odom_set(-2_in, DRIVE_SPEED, false);
    chassis.pid_wait_quick();

    // small delay
    pros::delay(500);
    chassis.pid_turn_set(270, DRIVE_SPEED, true);
    chassis.pid_wait();

    // drive towards end of long goal
    chassis.pid_odom_set(84_in, DRIVE_SPEED, true);

    // optional if you want to stop running intake in the middle
    chassis.pid_wait_until(40_in);
    stopIntake();
    stopOutake();
    chassis.pid_wait();

    // aligining with long goal
    chassis.pid_turn_set(180, DRIVE_SPEED, true);
    chassis.pid_wait();

    // drive forward
    chassis.pid_odom_set(13_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // align with long goal
    chassis.pid_turn_set(90, DRIVE_SPEED, true);
    chassis.pid_wait();

    // drive towards long goal
    chassis.pid_odom_set(8.5_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //drive ever so slightly away
    chassis.pid_odom_set(-1_in, DRIVE_SPEED, false);
    chassis.pid_wait();

    // intake/outake
    /*outake(-127);
    intake(-127);
    pros::delay(500); */

    outake();
    intake();
    flapToggle();
    
    // wait for balls
    pros::delay(5000);

    stopIntake();
    stopOutake();
    flapToggle();
    

    chassis.pid_odom_set(-5_in, DRIVE_SPEED, false);
    chassis.pid_wait();
    chassis.pid_turn_set(270, DRIVE_SPEED/2, true);
    chassis.pid_wait();
    flapToggle();
    flapToggle();
    scraperToggle();
    intake();
    outake();
    chassis.pid_odom_set(22_in, DRIVE_SPEED/1.5, true);
    chassis.pid_wait();

    for (int i = 0; i < 5; i++){
      chassis.pid_odom_set(-3_in, DRIVE_SPEED, false);
      chassis.pid_wait();
      chassis.pid_odom_set(3.5_in, DRIVE_SPEED, false);
      chassis.pid_wait();

      // once balls fill up more of the top stop running outtake 
      // if (i == 1){
      //   outake(80);
      // }
    }

    stopOutake();
    chassis.pid_odom_set(-6_in, DRIVE_SPEED, false);
    chassis.pid_wait();
    scraperToggle();
    
    chassis.pid_turn_set(95, -DRIVE_SPEED/2, true);
    chassis.pid_wait();
    chassis.pid_odom_set(21_in, DRIVE_SPEED/2, true);
    chassis.pid_wait();

    

     //drive ever so slightly away
    chassis.pid_odom_set(-1.5_in, DRIVE_SPEED, false);
    chassis.pid_wait();

    

    /* outake(-127);
    intake(-127);

    pros::delay(500); */
    
    flapToggle();
    outake();
    intake();

    
    pros::delay(5000);
    flapToggle();
    stopIntake();
    stopOutake();

    secondPart();
}

void secondPart(){
  clearParkingConstants();



  chassis.pid_odom_set(-5_in, DRIVE_SPEED/1.5, false);
  chassis.pid_wait();
  chassis.pid_turn_set(180, DRIVE_SPEED/2, true);
  chassis.pid_wait();
  chassis.pid_odom_set(48_in, DRIVE_SPEED/2, true);
  chassis.pid_wait();
  chassis.pid_turn_set(270, DRIVE_SPEED/2, true);
  chassis.pid_wait();
  chassis.pid_odom_set(16.5_in, DRIVE_SPEED/3, true);
  chassis.pid_wait_quick();
  scraperToggle();
  pros::delay(500);
  chassis.pid_odom_set(-9_in, DRIVE_SPEED/2, true);
  chassis.pid_wait();
  scraperToggle();
  chassis.pid_turn_set(0, DRIVE_SPEED/2, true);
  chassis.pid_wait();
  chassis.pid_odom_set(28_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  flapToggle();
  flapToggle();
  chassis.pid_turn_set(90, DRIVE_SPEED/2, true);
  chassis.pid_wait();
  intake();
  outake(60);
  chassis.pid_odom_set(96_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_turn_set(160, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  chassis.pid_odom_set(14_in, DRIVE_SPEED, true);
  chassis.pid_wait_quick();
  stopIntake();
  stopOutake();
  
  //Comment out flapToggle once park pneumatics are set up
  parkerToggle();
}




void skillsAutonLeft(){
  skillsAutonRightConstants();
  
  chassis.pid_odom_set(-9_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(90, DRIVE_SPEED, true);
  chassis.pid_wait();
  scraperToggle();
  chassis.pid_odom_set(45_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(0, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_odom_set(15_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  //rest of rightAuton code
   pivotPiston.set_value(true);
  
  // cracking the match loader
  for (int i = 0; i < 4; i++){
      chassis.pid_odom_set(-3_in, DRIVE_SPEED, false);
      chassis.pid_wait();
      chassis.pid_odom_set(3.5_in, DRIVE_SPEED, false);
      chassis.pid_wait();

      // once balls fill up more of the top stop running outtake 
      //if (i == 1){
        //outake(127);
     // }
    }

    // go backwards from matchloader
    chassis.pid_odom_set(-8.5_in, DRIVE_SPEED, true);
    chassis.pid_wait_quick();

    // pulll scraper back in
    scraperToggle();

    // align with balls on the wall
    chassis.pid_turn_set(90, DRIVE_SPEED, true);
    chassis.pid_wait_quick();

    // go towards ball on wall
    chassis.pid_odom_set(14_in, DRIVE_SPEED/2, false);
    chassis.pid_wait_quick();

    // back up from balls on wall
    chassis.pid_odom_set(-2_in, DRIVE_SPEED, false);
    chassis.pid_wait_quick();

    // small delay
    pros::delay(500);
    chassis.pid_turn_set(180, DRIVE_SPEED, true);
    chassis.pid_wait();

    // drive towards end of long goal
    chassis.pid_odom_set(84_in, DRIVE_SPEED, true);

    // optional if you want to stop running intake in the middle
    chassis.pid_wait_until(40_in);
    stopIntake();
    stopOutake();
    chassis.pid_wait();

    // aligining with long goal
    chassis.pid_turn_set(270, DRIVE_SPEED, true);
    chassis.pid_wait();

    // drive forward
    chassis.pid_odom_set(11_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    // align with long goal
    chassis.pid_turn_set(0, DRIVE_SPEED, true);
    chassis.pid_wait();

    // drive towards long goal
    chassis.pid_odom_set(8.5_in, DRIVE_SPEED, true);
    chassis.pid_wait();

    //drive ever so slightly away
    chassis.pid_odom_set(-1_in, DRIVE_SPEED, false);
    chassis.pid_wait();

    // intake/outake
    outake(-127);
    intake(-127);
    pros::delay(500);
    outake();
    intake();
    flapToggle();
    
    // wait for balls
    pros::delay(5000);

    stopIntake();
    stopOutake();
    flapToggle();

    chassis.pid_odom_set(-5_in, DRIVE_SPEED, false);
    chassis.pid_wait();
    chassis.pid_turn_set(180, DRIVE_SPEED/2, true);
    chassis.pid_wait();
    scraperToggle();
    intake();
    outake();
    chassis.pid_odom_set(22_in, DRIVE_SPEED/1.5, true);
    chassis.pid_wait();

    for (int i = 0; i < 5; i++){
      chassis.pid_odom_set(-3_in, DRIVE_SPEED, false);
      chassis.pid_wait();
      chassis.pid_odom_set(3.5_in, DRIVE_SPEED, false);
      chassis.pid_wait();

      // once balls fill up more of the top stop running outtake 
      // if (i == 1){
      //   outake(80);
      // }
    }

    stopOutake();
    chassis.pid_odom_set(-6_in, DRIVE_SPEED, false);
    chassis.pid_wait();
    scraperToggle();
    chassis.pid_turn_set(110, -DRIVE_SPEED/2, true);
    chassis.pid_wait();
    chassis.pid_odom_set(5_in, DRIVE_SPEED/2, true);
    chassis.pid_wait();
    chassis.pid_turn_set(90, -DRIVE_SPEED/2, true);
    chassis.pid_wait();
    chassis.pid_odom_set(16_in, DRIVE_SPEED/2, true);
    chassis.pid_wait();

     //drive ever so slightly away
    chassis.pid_odom_set(-1_in, DRIVE_SPEED, false);
    chassis.pid_wait();

    outake(-127);
    intake(-127);
    pros::delay(500);
    outake();
    intake();

    flapToggle();
    pros::delay(5000);
    flapToggle();
    stopIntake();
    stopOutake();

    clearParkingConstants();

    chassis.pid_odom_set(-5_in, DRIVE_SPEED/1.5, false);
    chassis.pid_wait();
    chassis.pid_turn_set(270, DRIVE_SPEED/2, true);
    chassis.pid_wait();
    chassis.pid_odom_set(19.5_in, DRIVE_SPEED/2, true);
    chassis.pid_wait();
    chassis.pid_turn_set(0, DRIVE_SPEED/2, true);
    chassis.pid_wait();
    intake();
    outake(60);
    chassis.pid_odom_set(88_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    chassis.pid_turn_set(340, DRIVE_SPEED, true);
    chassis.pid_wait_quick();
    chassis.pid_odom_set(14_in, DRIVE_SPEED, true);
    chassis.pid_wait();
    stopIntake();
    stopOutake();
  
  //Comment out flapToggle once park pneumatics are set up
  flapToggle();
  parkerToggle();
}





///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  // chassis.pid_drive_set(10_in, DRIVE_SPEED, true);
  // chassis.pid_wait();

  chassis.pid_turn_set(180_deg,TURN_SPEED/2);
  chassis.pid_wait();

  // chassis.pid_turn_set(360_deg,TURN_SPEED/2);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-1_in, DRIVE_SPEED, true);
  // chassis.pid_wait();

  // chassis.pid_odom_set({{0_in, 24_in}, rev, DRIVE_SPEED},true);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-24_in, DRIVE_SPEED);
  // chassis.pid_wait();
  

  // chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
  //                      true);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  // chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Odom Drive PID
///
void odom_drive_example() {
  // This works the same as pid_drive_set, but it uses odom instead!
  // You can replace pid_drive_set with pid_odom_set and your robot will
  // have better error correction.

  chassis.pid_odom_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_odom_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit
///
void odom_pure_pursuit_example() {
  // Drive to 0, 30 and pass through 6, 10 and 0, 20 on the way, with slew
  chassis.pid_odom_set({{{6_in, 10_in}, fwd, DRIVE_SPEED},
                        {{0_in, 20_in}, fwd, DRIVE_SPEED},
                        {{0_in, 30_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  // Drive to 0, 0 backwards
  chassis.pid_odom_set({{0_in, 0_in}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Pure Pursuit Wait Until
///
void odom_pure_pursuit_wait_until_example() {
  chassis.pid_odom_set({{{0_in, 24_in}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait_until_index(1);  // Waits until the robot passes 12, 24
  // Intake.move(127);  // Set your intake to start moving once it passes through the second point in the index
  chassis.pid_wait();
  // Intake.move(0);  // Turn the intake off
}

///
// Odom Boomerang
///
void odom_boomerang_example() {
  chassis.pid_odom_set({{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Odom Boomerang Injected Pure Pursuit
///
void odom_boomerang_injected_pure_pursuit_example() {
  chassis.pid_odom_set({{{0_in, 24_in, 45_deg}, fwd, DRIVE_SPEED},
                        {{12_in, 24_in}, fwd, DRIVE_SPEED},
                        {{24_in, 24_in}, fwd, DRIVE_SPEED}},
                       true);
  chassis.pid_wait();

  chassis.pid_odom_set({{0_in, 0_in, 0_deg}, rev, DRIVE_SPEED},
                       true);
  chassis.pid_wait();
}

///
// Calculate the offsets of your tracking wheels
///
void measure_offsets() {
  // Number of times to test
  int iterations = 50;

  // Our final offsets
  double l_offset = 0.0, r_offset = 0.0, b_offset = 0.0, f_offset = 0.0;

  // Reset all trackers if they exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->reset();
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->reset();
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->reset();
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->reset();
  
  for (int i = 0; i < iterations; i++) {
    // Reset pid targets and get ready for running an auton
    chassis.pid_targets_reset();
    chassis.drive_imu_reset();
    chassis.drive_sensor_reset();
    chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
    chassis.odom_xyt_set(0_in, 0_in, 0_deg);
    double imu_start = chassis.odom_theta_get();
    double target = i % 2 == 0 ? 90 : 270;  // Switch the turn target every run from 270 to 90

    // Turn to target at half power
    chassis.pid_turn_set(target, 63, ez::raw);
    chassis.pid_wait();
    pros::delay(250);

    // Calculate delta in angle
    double t_delta = util::to_rad(fabs(util::wrap_angle(chassis.odom_theta_get() - imu_start)));

    // Calculate delta in sensor values that exist
    double l_delta = chassis.odom_tracker_left != nullptr ? chassis.odom_tracker_left->get() : 0.0;
    double r_delta = chassis.odom_tracker_right != nullptr ? chassis.odom_tracker_right->get() : 0.0;
    double b_delta = chassis.odom_tracker_back != nullptr ? chassis.odom_tracker_back->get() : 0.0;
    double f_delta = chassis.odom_tracker_front != nullptr ? chassis.odom_tracker_front->get() : 0.0;

    // Calculate the radius that the robot traveled
    l_offset += l_delta / t_delta;
    r_offset += r_delta / t_delta;
    b_offset += b_delta / t_delta;
    f_offset += f_delta / t_delta;
  }

  // Average all offsets
  l_offset /= iterations;
  r_offset /= iterations;
  b_offset /= iterations;
  f_offset /= iterations;

  // Set new offsets to trackers that exist
  if (chassis.odom_tracker_left != nullptr) chassis.odom_tracker_left->distance_to_center_set(l_offset);
  if (chassis.odom_tracker_right != nullptr) chassis.odom_tracker_right->distance_to_center_set(r_offset);
  if (chassis.odom_tracker_back != nullptr) chassis.odom_tracker_back->distance_to_center_set(b_offset);
  if (chassis.odom_tracker_front != nullptr) chassis.odom_tracker_front->distance_to_center_set(f_offset);
}

// . . .
// Make your own autonomous functions here!
// . . .