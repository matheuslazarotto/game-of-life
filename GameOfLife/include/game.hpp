#ifndef GAME_H
#define GAME_H

#include <vector>

using namespace std;

class Game
{
    private:

    
    public:
        int g_width;
        int g_height;

        Game() {};

        vector<vector<short int>> m_output;
        vector<vector<short int>> m_state;

        short int get_cell_state(unsigned int i, 
                                 unsigned int j) { return m_state[i][j]; }

        void init_game(unsigned int w, 
                       unsigned int h);

        void set_cell_state(unsigned int i, 
                            unsigned int j,
                            short int s) { m_state[i][j] = s; }

        void evolve_cell(unsigned int i,
                         unsigned int j);
        
        unsigned int get_height() { return g_height; }
        unsigned int get_width()  { return g_width; }
};

#endif
