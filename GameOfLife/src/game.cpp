#include "game.hpp"

void Game::init_game(unsigned int w, unsigned int h)
{
    m_output.resize(h+2, vector<short int>(0));
    m_state.resize(h+2, vector<short int>(0));
    
    for (unsigned int j = 0; j < (h+2); j++)
    {
        m_output[j].resize(w+2);
        m_state[j].resize(w+2);
    }

    g_width = w;
    g_height = h;

    for (int i = 0; i <= g_width+1; i++) 
    {
        for (int j = 0; j <= g_height+1; j++)
        {
            m_output[i][j] = -1;
        }
    }

    // Use [h+2] and [w+2] in order to get free borders
    // at [0] and [h+1].
    // m_state[0] and m_state[h+1] are never deal with
    // altought periodic conditions can be implemented 
    // on it in the evolve_cell function (you may also 
    // create your own evolve_cell().
}

void Game::evolve_cell(unsigned int i, unsigned int j)
{
    int nNeighbours = m_state[i-1][j-1] + m_state[i-1][j+0] + m_state[i-1][j+1] +
                      m_state[i+0][j-1] +        0          + m_state[i+0][j+1] +
                      m_state[i+1][j-1] + m_state[i+1][j+0] + m_state[i+1][j+1];

    if (m_state[i][j] == 1) 
    { 
        if (nNeighbours != 2 && nNeighbours != 3) { m_output[i][j] = 0; }
    }
    else if (m_state[i][j] == 0)
    {
        if (nNeighbours == 3) { m_output[i][j] = 1; }
    }
}
