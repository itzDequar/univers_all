#include <stdio.h>
#include <array>
#include <pico/types.h>
#include <pico/time.h>
#include "allpins.h"
#include "overlibs/Patternbtn.h"

bool enabled = true;
bool running = true;

void blink_end() {
    for (int i = 0; i < 5; i++) {
        gpio_put(GLED_PIN, 1);
        gpio_put(RLED_PIN, 0);
        sleep_ms(200);
        gpio_put(GLED_PIN, 0);
        gpio_put(RLED_PIN, 1);
        sleep_ms(200);
    }
    gpio_put(GLED_PIN, 1);
    gpio_put(RLED_PIN, 1);
    sleep_ms(500);
    gpio_put(GLED_PIN, 0);
    gpio_put(RLED_PIN, 0);
}

int main() {
    absolute_time_t press_start_single = nil_time;
    absolute_time_t press_start_double = nil_time;

    // Кнопки
    gpio_init(LBTTN_PIN);
    gpio_set_dir(LBTTN_PIN, GPIO_IN);
    gpio_pull_up(LBTTN_PIN);

    gpio_init(MBTTN_PIN);
    gpio_set_dir(MBTTN_PIN, GPIO_IN);
    gpio_pull_up(MBTTN_PIN);

    gpio_init(RBTTN_PIN);
    gpio_set_dir(RBTTN_PIN, GPIO_IN);
    gpio_pull_up(RBTTN_PIN);

    // Светодиоды
    gpio_init(RLED_PIN);
    gpio_set_dir(RLED_PIN, GPIO_OUT);

    gpio_init(GLED_PIN);
    gpio_set_dir(GLED_PIN, GPIO_OUT);

    bool left_PRESSED;
    bool midle_PRESSED;
    bool right_PRESSED;

    while (enabled) {
        if(running) {
            left_PRESSED = (gpio_get(LBTTN_PIN) == 0);
            midle_PRESSED = (gpio_get(MBTTN_PIN) == 0);
            right_PRESSED = (gpio_get(RBTTN_PIN) == 0);
            pattern_button(midle_PRESSED, press_start_single);
            offon_pattern(left_PRESSED, right_PRESSED, running, enabled, press_start_double);
        } else {
            offon_pattern(left_PRESSED, right_PRESSED, running, enabled, press_start_double);
            gpio_put(RLED_PIN, 1);
            gpio_put(GLED_PIN, 1);
        }
        
        sleep_ms(10); // антидребезг
    }

    blink_end();
    return 0;
}