#include "xDrive.hpp"
#include "SimpleSlew.hpp"

double headingControlTarget = 0;

bool startedMovement = false;
SimpleSlew INPUT_Left_X(1.0);
SimpleSlew INPUT_Left_Y(1.0);
void XDrive::DriverControl(){
    // Input Catching
    double INPUT_Right_X = (double) master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    INPUT_Left_X.Set((double)master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));
    INPUT_Left_Y.Set((double)master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));

    // Heading Control
    if(abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) > 10){
        forwardHeadingPID.target_set(GetHeading());
        // backwardHeadingPID.target_set(GetHeading());
    }
    else{
        INPUT_Right_X += forwardHeadingPID.compute(GetHeading());
        // else INPUT_Right_X += backwardHeadingPID.compute(GetHeading());
    }


    // PROCESSOR: Driver Control Deadband (or Deadzone)
    // | Help the bot stay still when not touching the sticks
    // double DEADBAND_LIMIT = 0.1;
    // if (abs(INPUT_Right_X) < DEADBAND_LIMIT) INPUT_Right_X = 0;
    // if (abs(INPUT_Left_X) < DEADBAND_LIMIT) INPUT_Left_X = 0;
    // if (abs(INPUT_Left_Y) < DEADBAND_LIMIT) INPUT_Left_Y = 0;

    // PROCESSOR: Input Smoothing
    // | Smooths out inputs and dedicates more of the stick to lower velocities, improving accuracy
    // double SMOOTHING_FACTOR = 1; // Higher values dedicate more stick space to fine low speeds
    // INPUT_Right_X = pow(INPUT_Right_X, SMOOTHING_FACTOR);
    // INPUT_Left_X = pow(INPUT_Left_X, SMOOTHING_FACTOR);
    // INPUT_Left_Y = pow(INPUT_Left_Y, SMOOTHING_FACTOR);

    // Building the movement components  
    DRIVER_Turn = INPUT_Right_X;        
    DRIVER_Strafe = INPUT_Left_X.Get();
    DRIVER_Forward = INPUT_Left_Y.Get();
}

void XDrive::XDriveMove(){
    // Build the Combined Movements
    double forward = -(DRIVER_Forward + AUTON_Forward);
    double strafe = -(DRIVER_Strafe + AUTON_Strafe);
    double turn = DRIVER_Turn + AUTON_Turn;

    // PROCESSOR: Field Oriented
    // | does what it says lollll
    if(isFieldOriented){ 
        double initialStrafe = strafe;
        double initialForward = forward;

        double heading = GetHeading();

        strafe = initialStrafe * cos(heading) - initialForward * sin(heading);
        forward = initialStrafe * sin(heading) + initialForward * cos(heading);
    }    

    // Build motor commands
    int fl = (-strafe - forward + turn);
    int fr = (+forward - strafe + turn);
    int bl = (-forward + strafe + turn);
    int br = (strafe + forward + turn);

    // PROCESSOR: Motor Oversaturation Protection
    // | Preserves differene between motors when goes over
    //Not sure if using integer divison would lose preciseness rather than calculating a scale of type double and multiplying everything by it
    int maxEffort = std::max({abs(fl), abs(fr), abs(bl), abs(br)});
    if(maxEffort > 127){
        fl = fl/maxEffort * 127;
        fr = fr/maxEffort * 127;
        bl = bl/maxEffort * 127;
        br = br/maxEffort * 127;
    }

    // Move Motors
    fl *= (600/127);
    fr *= (600/127);
    bl *= (600/127);
    br *= (600/127);

    FL.move_velocity(fl);
    FR.move_velocity(fr);
    BL.move_velocity(bl);
    BR.move_velocity(br);
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
    AUTON_xSlew.initialize(true, forwardSpeed, xTarget, GetX()); // Slew will be enabled later in AutonExecute
    AUTON_ySlew.initialize(true, forwardSpeed, yTarget, GetY());
    AUTON_turnSlew.initialize(true, turnSpeed, angleTarget, GetHeading());
}

void XDrive::AutonExecute(){
    while (true) {
        // Compute PID outputs
        double x_current = GetX();
        double y_current = GetY();
        double theta_current = GetHeading(); // degrees

        // Apply slew to the PID outputs
        AUTON_Strafe = clamp(AUTON_xSlew.iterate(xPID.compute(x_current)), -127.0, 127.0);
        AUTON_Forward = clamp(AUTON_ySlew.iterate(xPID.compute(y_current)), -127.0, 127.0);
        AUTON_Turn = clamp(AUTON_turnSlew.iterate(xPID.compute(theta_current)), -127.0, 127.0);

        // Execute Move
        XDrive::XDriveMove();

        pros::delay(util::DELAY_TIME);

        // Wait for the PID to be within a certain threshold of the target before moving on
        //What if just X exists but we havent made it to our y coordinate yet?
        bool xExited = xPID.exit_condition() != ez::exit_output::RUNNING;
        bool yExited = yPID.exit_condition() != ez::exit_output::RUNNING;
        bool turnExited = turnPID.exit_condition() != ez::exit_output::RUNNING;
        if(xExited == false && yExited == false && turnExited == false){
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