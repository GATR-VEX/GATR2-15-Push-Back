#include "xDrive.hpp"

void XDrive::DriverControl(){
    // Input Catching
    double INPUT_Right_X = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)/127.0;
    double INPUT_Left_X = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)/127.0;
    double INPUT_Left_Y = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)/127.0;

    // PROCESSOR: Driver Control Deadband
    // | Help the bot stay still when not touching the sticks
    double DEADBAND_LIMIT = 0.1;
    if (abs(INPUT_Right_X) < DEADBAND_LIMIT) INPUT_Right_X = 0;
    if (abs(INPUT_Left_X) < DEADBAND_LIMIT) INPUT_Left_X = 0;
    if (abs(INPUT_Left_Y) < DEADBAND_LIMIT) INPUT_Left_Y = 0;

    // PROCESSOR: Input Smoothing
    // | Smooths out inputs and dedicates more of the stick to lower velocities, improving accuracy
    double SMOOTHING_FACTOR = 3; // Higher values dedicate more stick space to fine low speeds
    INPUT_Right_X = pow(INPUT_Right_X, SMOOTHING_FACTOR);
    INPUT_Left_X = pow(INPUT_Left_X, SMOOTHING_FACTOR);
    INPUT_Left_Y = pow(INPUT_Left_Y, SMOOTHING_FACTOR);

    // Building the movement components  
    DRIVER_Turn = INPUT_Right_X;        
    DRIVER_Strafe = INPUT_Left_X;
    DRIVER_Forward = INPUT_Left_Y;    
}

void XDrive::XDriveMove(){
    // Build the Combined Movements
    double forward = DRIVER_Forward + AUTON_Forward;
    double strafe = DRIVER_Strafe + AUTON_Strafe;
    double turn = DRIVER_Turn + AUTON_Turn;

    // PROCESSOR: Field Oriented
    // | does what it says lollll
    if(isFieldOriented){
        double heading = GetHeading();
        strafe = strafe * cos(heading) - forward * sin(heading);
        forward = strafe * sin(heading) + forward * cos(heading);
    }    

    // Build motor commands
    int fl = (strafe + forward + turn)*127;
    int fr = (strafe - forward - turn)*127;
    int bl = (strafe - forward + turn)*127;
    int br = (strafe + forward - turn)*127;

    // PROCESSOR: Motor Oversaturation Protection
    // | Preserves differene between motors when goes over
    int maxEffort = std::max({abs(fl), abs(fr), abs(bl), abs(br)});
    if(maxEffort > 127){
        fl = fl/maxEffort * 127;
        fr = fr/maxEffort * 127;
        bl = bl/maxEffort * 127;
        br = br/maxEffort * 127;
    }

    // Move Motors
    FL.move(fl);
    FR.move(fr);
    BL.move(bl);
    BR.move(br);
}

//
// Auton Functions
//
void XDrive::Move_Set(double xTarget, double yTarget, double driveSpeed){
    double stabilizeSpeed = 25;
    Pose_Set(xTarget, yTarget, GetHeading(), driveSpeed, stabilizeSpeed);
}
void XDrive::Turn_Set(double angleTarget, double turnSpeed){
    double stabilizeSpeed = 25;
    Pose_Set(GetX(), GetY(), angleTarget, stabilizeSpeed, turnSpeed);
}
void XDrive::Pose_Set(double xTarget, double yTarget, double angleTarget, double forwardSpeed, double turnSpeed){
    // Set the PID constants for the auton
    ZeroDriverInput();
    ZeroAutonInput();

    // Reset PID timers so that the exit conditions work properly
    xPID.timers_reset();
    yPID.timers_reset();
    turnPID.timers_reset();  

    // Set PID Targets
    xPID.target_set(xTarget);
    yPID.target_set(yTarget);
    turnPID.target_set(angleTarget);

    // Set Slew
    xSlew.initialize(true, forwardSpeed, 0, 0); // Slew will be enabled later in AutonExecute
    ySlew.initialize(true, forwardSpeed, 0, 0);
    turnSlew.initialize(true, turnSpeed, 0, 0);
}

void XDrive::AutonExecute(){
    while (true) {
        // Compute PID outputs
        double x_current = x_tracker.get();
        double y_current = y_tracker.get();
        double theta_current = GetHeading(); // degrees

        // Apply slew to the PID outputs
        AUTON_Strafe = xSlew.iterate(xPID.compute(x_current));
        AUTON_Forward = ySlew.iterate(xPID.compute(x_current));
        AUTON_Turn = turnSlew.iterate(xPID.compute(x_current));

        // Execute Move
        XDrive::XDriveMove();

        pros::delay(util::DELAY_TIME);

        // Wait for the PID to be within a certain threshold of the target before moving on
        bool xExited = xPID.exit_condition() != ez::exit_output::RUNNING;
        bool yExited = yPID.exit_condition() != ez::exit_output::RUNNING;
        bool turnExited = turnPID.exit_condition() != ez::exit_output::RUNNING;
        if(xExited == false || yExited == false || turnExited == false){
            return;
        }

        pros::delay(util::DELAY_TIME);
    }
}

void XDrive::ZeroDriverInput(){
    DRIVER_Turn = 0;
    DRIVER_Strafe = 0;
    DRIVER_Forward = 0;
}
void XDrive::ZeroAutonInput(){
    AUTON_Turn = 0;
    AUTON_Strafe = 0;
    AUTON_Forward = 0;
}