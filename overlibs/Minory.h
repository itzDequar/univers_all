#include <hardware/gpio.h>
#include <array>
#include <random>
#include <pico/time.h>
#include "allpins.h"

class Minorygame {
private:
    bool left;
    bool right;
    uint lvl_game = 0;
    uint input_index = 0;
    std::array<uint, 16> input_sequence;
    std::array<uint, 16> memory;
    std::mt19937 gen;
    std::uniform_int_distribution<uint> dis;
public:
    Minorygame()
    : dis(1, 2)
    {
        uint64_t t = time_us_64();
        gen.seed(static_cast<uint32_t>(t & 0xFFFFFFFF));
        memory.fill(0);
        lvl_game = 0;
    }

    std::array<uint,16>& go_minory() {
    if (lvl_game < memory.size()) {
        memory[lvl_game++] = dis(gen);
    }
    return memory;
    }

    void blinkled_minory(uint GPIOLED) {
        sleep_ms(350);
        gpio_put(GPIOLED, 1);
        if(lvl_game == 0) {
            sleep_ms(800);
        } else {
            sleep_ms((300 / lvl_game)+500);
        }
        gpio_put(GPIOLED, 0);
    }

    void endofgame_minory(bool win) {
        for (uint i = 0; i < 10; i++) {
            if(win){
                gpio_put(GLED_PIN, 1);
            } else {
                gpio_put(RLED_PIN, 1);
            }
            sleep_ms(85);
        }
    }

    void play_minory() {
        for(auto val : memory) {
            if (val == 1) {
                blinkled_minory(RLED_PIN);
            }
            if (val == 2) {
                blinkled_minory(GLED_PIN);
            }
        }
    }

    bool trueorfalse_minory() {
        if(input_sequence[input_index] == memory[lvl_game]) {
            return true;
        } else {
            return false;
        }
    }

    bool read_buttons_minory() {
        left  = (gpio_get(LBTTN_PIN) == 0);
        right = (gpio_get(RBTTN_PIN) == 0);

        if (left && input_index < 16) {
            input_sequence[input_index++] = 1;
            if (!trueorfalse_minory()) {
                return false;
            };
            sleep_ms(50);
        }
        else if (right && input_index < 16) {
            input_sequence[input_index++] = 2;
            if (!trueorfalse_minory()) {
                return false;
            };
            sleep_ms(50);
        }
        if (input_index == 16) {
            return true;
        }
        
    }
};