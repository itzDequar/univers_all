#include "Minory.h"

Minory::Minory() : gen(rd()), dist(1, 2){

}
Minory::~Minory() {
    memory.clear();
    input.clear();
    lvl_game = 1;
}

void Minory::gameover_minory() {
    for (uint i = 0; i < 30; i++) {
        gpio_put(RLED_PIN, 1);
        sleep_ms(100);
        gpio_put(RLED_PIN, 0);
        sleep_ms(100);
    }
}
void Minory::gamewin_minory() {
    for (uint i = 0; i < 30; i++) {
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
    sleep_ms(1100);
    if (rorg == 1) gpio_put(RLED_PIN, 1);
    if (rorg == 2) gpio_put(GLED_PIN, 1);
    sleep_ms((500 / lvl_game)+500);
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
    lvl_game = 0;
}

bool Minory::input_minory() {
    bool left;
    bool right;
    bool i = true;
    while (i) {
        left = ( gpio_get(LBTTN_PIN) == 0 );
        right = ( gpio_get(RBTTN_PIN) == 0 );

        if(left) {
            input.push_back(1);
            while (gpio_get(LBTTN_PIN) == 0) {
                sleep_ms(10); // ждём пока отпустят
            }
        } else if(right) {
            input.push_back(2);
            while (gpio_get(RBTTN_PIN) == 0) {
                sleep_ms(10); // ждём пока отпустят
            }
        };

        if (input.size() == memory.size()) {
            if (checkit_minory() == false) {
                input.clear();
                return false;
            } else {
                input.clear();
                return true;
            }
        }
    }
}

void Minory::play_minory() {
    addmore_minory();
    playled_minory();
    if (input_minory() == false) {
        gameover_minory();
        return;
    } else {
        gamewin_minory();
        return;
    }
}