#ifndef SYSTEM_H
#define SYSTEM_H

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include "canvas.hpp"
#include "game.hpp"

class System
{
    private:
        Game game;
        Canvas canvas;
        short int pixel;
    
    public:
        System(unsigned int game_cells_w, 
               unsigned int game_cells_h, 
               unsigned int cell_pixels);

        int run();
        int handle_event();
        int sys_quit();

        int running_sys;
        int running_game;
};

#endif