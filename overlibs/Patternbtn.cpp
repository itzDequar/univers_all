#include "Patternbtn.h"

bool offon_pattern(bool pressed1, bool pressed2, bool &running, bool &enabled, absolute_time_t &press_start) {
    if (pressed1 && pressed2) {
        if (is_nil_time(press_start)) {
            press_start = get_absolute_time();
        } else {
            int64_t elapsed_ms = absolute_time_diff_us(press_start, get_absolute_time()) / 1000;
            if (elapsed_ms >= 5000) {
                enabled = !enabled;
            }
        }
        return true;
    } else {
        press_start = nil_time;
        return false;
    }
}

bool pattern_button(bool pressed, absolute_time_t &press_start) {
    if (pressed) {
        if (is_nil_time(press_start)) {
            press_start = get_absolute_time();
        } else {
            int64_t elapsed_ms = absolute_time_diff_us(press_start, get_absolute_time()) / 1000;
            if (elapsed_ms >= 200) {
                gpio_put(RLED_PIN, 1);
                gpio_put(GLED_PIN, 1);
            }
        }
        return true;
    } else {
        press_start = nil_time;
        return false;
    }
}