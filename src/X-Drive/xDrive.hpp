#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

class XDrive{
    private:
        pros::MotorGroup FL;
        pros::MotorGroup FR;
        pros::MotorGroup BL;
        pros::MotorGroup BR;

        ez::tracking_wheel x_tracker;  // This tracking wheel is perpendicular to the drive wheels
        ez::tracking_wheel y_tracker;   // This tracking wheel is parallel to the drive wheels

        ez::Drive chassis;

        ez::PID xPID;
        ez::PID yPID;
        ez::PID turnPID;

        double DRIVER_Strafe = 0;
        double DRIVER_Forward = 0;
        double DRIVER_Turn = 0;

        double AUTON_Strafe = 0;
        double AUTON_Forward = 0;
        double AUTON_Turn = 0;

        // Declare a slew limiter for one motor or axis
        ez::slew ySlew;   // forward
        ez::slew xSlew; // strafe
        ez::slew turnSlew;   // turn

    
    public:
        bool isFieldOriented = false;

        XDrive(ez::Drive chassis): 
            FL({1,-18}), 
            FR({3,-4}), 
            BL({6,-5}), 
            BR({8,-7}), 
            x_tracker(9, 2, 0), 
            y_tracker(10, 2, 0), 
            chassis(chassis),
            xPID(),
            yPID(),
            turnPID(),
            xSlew(),
            ySlew(),
            turnSlew(){
                turnPID.constants_set(5, 0.0, 0.0);
                turnPID.exit_condition_set(100, 2, 100, 2, 100, 100); 
                turnSlew.speed_max_set(5.0);

                xPID.constants_set(5, 0.0, 0.0);
                xPID.exit_condition_set(100, 0.5, 100, 0.5, 100, 100);
                xSlew.speed_max_set(5.0);

                yPID.constants_set(5, 0.0, 0.0);
                yPID.exit_condition_set(100, 0.5, 100, 0.5, 100, 100);
                ySlew.speed_max_set(5.0);
            }

        void DriverControl();

        inline double GetHeading(){
            return (int)chassis.drive_imu_get() * M_PI/180.0;
        }
        inline double GetX(){
            return x_tracker.get();
        }
        inline double GetY(){
            return y_tracker.get();
        }
        void ZeroDriverInput();
        void ZeroAutonInput();
        void XDriveMove();
        void Move_Set(double xTarget, double yTarget, double driveSpeed);
        void Turn_Set(double angleTarget, double turnSpeed);
        void Pose_Set(double xTarget, double yTarget, double angleTarget, double forwardSpeed, double turnSpeed);
        void AutonExecute();
    };