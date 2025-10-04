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
    sleep_ms(250);
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

unsigned char Minory::input_minory() {
    bool left;
    bool mid;
    bool right;
    absolute_time_t quit = nil_time;

    while (1) {
        left = ( gpio_get(LBTTN_PIN) == 0 );
        mid = ( gpio_get(MBTTN_PIN) == 0 );
        right = ( gpio_get(RBTTN_PIN) == 0 );

        if(mid) {
            if (is_nil_time(quit)) {
            quit = get_absolute_time();
            } else {
                int64_t elapsed_ms = absolute_time_diff_us(quit, get_absolute_time()) / 1000;
                if (elapsed_ms >= 5000) {
                    return 10;
                }
            }
        }
        if(left) {
            if (memory[input] != 1) return 0;
            input++;
            while (gpio_get(LBTTN_PIN) == 0) {
                sleep_ms(10);
            }
        } else if(right) {
            if (memory[input] != 2) return 0;
            input++;
            while (gpio_get(RBTTN_PIN) == 0) {
                sleep_ms(10);
            }
        };

        if (input == memory.size()) {
            lvl_game++;
            input = 0;
            return 1;
        }
    }
}

bool Minory::play_minory() {
    while(1) {
        addmore_minory();
        playled_minory();
        switch (input_minory()) {
            case 0:
                gameover_minory();
                return false;
                break;
            case 1:
                gamewin_minory();
                break;
            case 10:
                gamefinish_minory();
                return false;
                break;

            default:
                break;
        }

        if (lvl_game > MAX_GAME) {
            clearall_minory();
            gamefinish_minory();
            return true;
        };
    }
}