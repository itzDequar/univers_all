#include "Minory.h"

Minory::Minory() : gen(rd()), dist(1, 2){

}
Minory::~Minory() {
    clearall_minory();
}

void Minory::gamefinish_minory() {
    for (uint i = 0; i < 15; i++) {
        gpio_put(RLED_PIN, 1);
        gpio_put(GLED_PIN, 0);
        sleep_ms(85);
        gpio_put(RLED_PIN, 0);
        gpio_put(GLED_PIN, 1);
        sleep_ms(85);
    }
    gpio_put(RLED_PIN, 0);
    gpio_put(GLED_PIN, 0);
}
void Minory::gameover_minory() {
    for (uint i = 0; i < 12; i++) {
        gpio_put(RLED_PIN, 1);
        sleep_ms(100);
        gpio_put(RLED_PIN, 0);
        sleep_ms(100);
    }
}
void Minory::gamewin_minory() {
    for (uint i = 0; i < 12; i++) {
        gpio_put(GLED_PIN, 1);
        sleep_ms(100);
        gpio_put(GLED_PIN, 0);
        sleep_ms(100);
    }
}

bool Minory::checkit_minory() {
    if (input == memory) return true;
    if (input != memory) return false;
}

void Minory::blinkled_minory(uint rorg) {
    sleep_ms(750);
    if (rorg == 1) gpio_put(RLED_PIN, 1);
    if (rorg == 2) gpio_put(GLED_PIN, 1);
    sleep_ms((500 / lvl_game)+100);
    if (rorg == 1) gpio_put(RLED_PIN, 0);
    if (rorg == 2) gpio_put(GLED_PIN, 0);
}

void Minory::playled_minory() {
    for (uint n : memory) {
        if(n == 1) blinkled_minory(1);
        if(n == 2) blinkled_minory(2);
    }
}

void Minory::addmore_minory() {
    memory.push_back(dist(gen));
}

void Minory::clearall_minory() {
    memory.clear();
    input.clear();
    lvl_game = 1;
}

bool Minory::input_minory() {
    bool left;
    bool right;
    while (1) {
        left = ( gpio_get(LBTTN_PIN) == 0 );
        right = ( gpio_get(RBTTN_PIN) == 0 );

        if(left) {
            input.push_back(1);
            while (gpio_get(LBTTN_PIN) == 0) {
                sleep_ms(10);
            }
        } else if(right) {
            input.push_back(2);
            while (gpio_get(RBTTN_PIN) == 0) {
                sleep_ms(10);
            }
        };

        if (input.size() == memory.size()) {
            if (checkit_minory() == false) {
                clearall_minory();
                return false;
            } else {
                lvl_game++;
                input.clear();
                return true;
            }
        }
    }
}

bool Minory::play_minory() {
    while(1) {
        addmore_minory();
        playled_minory();
        if (!input_minory()) {
            gameover_minory();
            return false;
        } else {
            gamewin_minory();
        }
        if (lvl_game > MAX_GAME) {
            clearall_minory();
            gamefinish_minory();
            return true;
        };
    }
}