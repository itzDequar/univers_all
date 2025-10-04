#include "Minory.h"

Minory::Minory() : gen(static_cast<unsigned>(time(nullptr))), dist(1, 2){

}
Minory::~Minory() {
    clearall_minory();
}

void Minory::gamefinish_minory() {
    for (unsigned char i = 0; i < 8; i++) {
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
    for (unsigned char i = 0; i < 5; i++) {
        gpio_put(RLED_PIN, 1);
        sleep_ms(100);
        gpio_put(RLED_PIN, 0);
        sleep_ms(100);
    }
}
void Minory::gamewin_minory() {
    for (unsigned char i = 0; i < 5; i++) {
        gpio_put(GLED_PIN, 1);
        sleep_ms(100);
        gpio_put(GLED_PIN, 0);
        sleep_ms(100);
    }
}

void Minory::blinkled_minory(unsigned char rorg) {
    sleep_ms(750);
    if (rorg == 1) gpio_put(RLED_PIN, 1);
    if (rorg == 2) gpio_put(GLED_PIN, 1);
    sleep_ms((500 / lvl_game)+100);
    if (rorg == 1) gpio_put(RLED_PIN, 0);
    if (rorg == 2) gpio_put(GLED_PIN, 0);
}

void Minory::playled_minory() {
    for (unsigned char n : memory) {
        if(n == 1) blinkled_minory(1);
        if(n == 2) blinkled_minory(2);
    }
}

void Minory::addmore_minory() {
    memory.push_back(dist(gen));
}

void Minory::clearall_minory() {
    memory.clear();
    input = 0;
    lvl_game = 1;
}

bool Minory::input_minory() {
    bool left;
    bool right;
    while (1) {
        left = ( gpio_get(LBTTN_PIN) == 0 );
        right = ( gpio_get(RBTTN_PIN) == 0 );

        if(left) {
            if (memory[input] != 1) return false;
            input++;
            while (gpio_get(LBTTN_PIN) == 0) {
                sleep_ms(10);
            }
        } else if(right) {
            if (memory[input] != 2) return false;
            input++;
            while (gpio_get(RBTTN_PIN) == 0) {
                sleep_ms(10);
            }
        };

        if (input == memory.size()) {
            lvl_game++;
            input = 0;
            return true;
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