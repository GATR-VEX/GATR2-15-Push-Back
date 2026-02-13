#pragma once
#include "pros/misc.h"
#include <string>

enum class Action {
    TOPINTAKE,
    OUTTAKE,
    FLAP,
    PIVOT,
    SCRAPER,
    BOTTOMINTAKE,
    WING,
    PARK,
    SNAPUP,
    SNAPDOWN,
    SNAPLEFT,
    SNAPRIGHT,
    SLOWBOT,
    REVIVE
};

constexpr pros::controller_digital_e_t NO_BUTTON =
    static_cast<pros::controller_digital_e_t>(-1);

pros::controller_digital_e_t WillScheme(Action action);
pros::controller_digital_e_t DavidScheme(Action action);

extern pros::controller_digital_e_t (*currentButtons)(Action);

void determineDriver();