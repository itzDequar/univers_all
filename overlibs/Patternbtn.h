#include <pico/types.h>
#include <pico/time.h>
#include "Minory.h"

bool offon_pattern(bool pressed1, bool pressed2, bool &running, bool &enabled, absolute_time_t &press_start) {
    if (pressed1 && pressed2) {
        if (is_nil_time(press_start)) {
            press_start = get_absolute_time();
        } else {
            int64_t elapsed_ms = absolute_time_diff_us(press_start, get_absolute_time()) / 1000;
            if (elapsed_ms >= 3000) {
                running = !running;
            }
            if (elapsed_ms >= 6000) {
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
            if (elapsed_ms >= 250) {
                bool checking = true;
                Minorygame game;
                std::array<uint, 16> memory;
                for (int i = 0; i < 16; i++) {
                    memory = game.go_minory();
                    game.play_minory();
                    while (checking) {
                        game.read_buttons_minory();
                    }
                }                
            }
        }
        return true;
    } else {
        press_start = nil_time;
        return false;
    }
}