#pragma once
#include <pico/types.h>
#include <pico/time.h>
#include <hardware/gpio.h>
#include <overlibs/Minory.h>
#include "allpins.h"

bool offon_pattern(bool pressed1, bool pressed2, bool &running, bool &enabled, absolute_time_t &press_start);
bool any_pattern(bool pressed, absolute_time_t &press_start);