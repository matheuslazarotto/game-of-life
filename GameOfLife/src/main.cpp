/**
 * Conway's Game Of Life
 * 
 * Basic reproduction of a interactive 
 * Conway's game of life (a.k.a. Cellular Automata).
 * 
 * This code is meant to be hacked and explored as 
 * a educational tool.
 *
 * Commands:
 * 		[Left click] ---- give life to a cell
 * 		[Space] --------- stops game
 * 		[c] ------------- cells genocide (clear grid)
 * 		[g] ------------- turn on|off grid frame
 * 		[w|s] ----------- increase|decrease time iterations rate
 * 
 * Implemented by M. Lazarotto (27/03/2020)
 **/

#include <iostream>
#include <cstdlib>

#include "game.hpp"
#include "canvas.hpp"
#include "system.hpp"

int main(int argc, char **argv)
{	
	// Settings
	unsigned const int nCells_w = 100; // Number of horizontal cells
	unsigned const int nCells_h = 100; // Number of vertical cells
	unsigned const int nPixel = 8;     // Pixels per cell [n x n]

	System sys(nCells_w, nCells_h, nPixel);

	while (sys.running_sys)
	{		
		while (sys.running_game)
		{
			sys.running_game = sys.run();
		}
		
		sys.running_sys = 0;
	} 

	return sys.sys_quit();
}
