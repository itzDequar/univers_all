#pragma once
#include "Patternbtn.cpp"

bool offon_pattern(bool pressed1, bool pressed2, bool &running, bool &enabled, absolute_time_t &press_start);
bool pattern_button(bool pressed, absolute_time_t &press_start);