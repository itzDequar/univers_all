#include "hardware/gpio.h"
#include "overlibs/Patternbtn.h"
#include <pico/time.h>
#include "allpins.h"


bool enabled = true;
bool running = true;

void blink_end() {
    for (int i = 0; i < 5; i++) {
        gpio_put(GLED_PIN, 1);
        gpio_put(RLED_PIN, 0);
        sleep_ms(100);
        gpio_put(GLED_PIN, 0);
        gpio_put(RLED_PIN, 1);
        sleep_ms(100);
    }
    gpio_put(GLED_PIN, 1);
    gpio_put(RLED_PIN, 1);
    sleep_ms(250);
    gpio_put(GLED_PIN, 0);
    gpio_put(RLED_PIN, 0);
}

void setup() {
    //buttons init
    gpio_init(LBTTN_PIN);
    gpio_set_dir(LBTTN_PIN, GPIO_IN);
    gpio_pull_up(LBTTN_PIN);

    gpio_init(MBTTN_PIN);
    gpio_set_dir(MBTTN_PIN, GPIO_IN);
    gpio_pull_up(MBTTN_PIN);

    gpio_init(RBTTN_PIN);
    gpio_set_dir(RBTTN_PIN, GPIO_IN);
    gpio_pull_up(RBTTN_PIN);

    //led init
    gpio_init(RLED_PIN);
    gpio_set_dir(RLED_PIN, GPIO_OUT);

    gpio_init(GLED_PIN);
    gpio_set_dir(GLED_PIN, GPIO_OUT);
}

void loop(absolute_time_t &press_start_single, absolute_time_t &press_start_double) {
    bool left_PRESSED = (gpio_get(LBTTN_PIN) == 0);
    bool midle_PRESSED = (gpio_get(MBTTN_PIN) == 0);
    bool right_PRESSED = (gpio_get(RBTTN_PIN) == 0);

    if(running) {
        pattern_button(midle_PRESSED, press_start_single);
        offon_pattern(left_PRESSED, right_PRESSED, running, enabled, press_start_double);
    }

    if (!running) {
        gpio_put(RLED_PIN, 1);
        gpio_put(GLED_PIN, 1);
    }
}

int main() {
    absolute_time_t press_start_single = nil_time;
    absolute_time_t press_start_double = nil_time;

    setup();

    while (enabled) {
        loop(press_start_single, press_start_double);
        sleep_ms(10);
    }

    blink_end();
    return 0;
}