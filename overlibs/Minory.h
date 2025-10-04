#pragma once
#include <vector>
#include <random>
#include <hardware/gpio.h>
#include <pico/types.h>
#include <pico/time.h>
#include <allpins.h>

class Minory{
    private:

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dist;

    uint MAX_GAME = 8;
    uint lvl_game = 1;
    std::vector<uint> memory;
    std::vector<uint> input;
   
    void gamefinish_minory();
    void gamewin_minory();
    void gameover_minory();
    bool checkit_minory();
    void blinkled_minory(uint rorg);
    void playled_minory();
    void addmore_minory();
    bool input_minory();
    void clearall_minory();

    public:
    
    bool play_minory();
    Minory();
    ~Minory();
};