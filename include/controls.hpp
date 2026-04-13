#pragma once
#include "pros/misc.h"
#include <string>

enum class Action {
    OUTTAKE,
    REVERSE,
    FLAP,
    PIVOT,
    SCRAPER,
    INTAKE,
    WING,
    PARK,
    SNAPUP,
    SNAPDOWN,
    SNAPLEFT,
    SNAPRIGHT,
    SLOWBOT,
    MAXLEVER
};

constexpr pros::controller_digital_e_t NO_BUTTON =
    static_cast<pros::controller_digital_e_t>(-1);

pros::controller_digital_e_t WillScheme(Action action);
pros::controller_digital_e_t DavidScheme(Action action);

extern pros::controller_digital_e_t (*currentButtons)(Action);