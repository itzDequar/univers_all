#pragma once
#include <vector>
#include <time.h>
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

    unsigned char MAX_GAME = 8;
    unsigned char lvl_game = 1;
    std::vector<unsigned char> memory;
    unsigned char input = 0;
   
    void gamefinish_minory();
    void gamewin_minory();
    void gameover_minory();
    void blinkled_minory(unsigned char rorg);
    void playled_minory();
    void addmore_minory();
    bool input_minory();
    void clearall_minory();

    public:
    
    bool play_minory();
    Minory();
    ~Minory();
};