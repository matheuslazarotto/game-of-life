# Game of Life
Basic reproduction of Conway's game of life (Cellular Automata).

## Controls
* Space : stops game
* Left click: give life to a cell
* c : cells genocide (clear grid)
* g : turn on grid frame
* w|s : increase|decrease time iterations rate

## Install
To install, just type `make` in `GameOfLife/` folder and `./game` to run it. `make clean` will delete the executable.

In order to install GameOfLife, one must have the c++11 compiler available along with SDL2 C library, which is used for graphics. In case you have ubuntu, you can get the package directly from repository:

`apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev`

The first library `libsdl2-dev` is the Simple DirectMedia Layer with development version, which allows us to load `...hpp` files from it.
The second library `libsdl2-image-dev` is the sub library for image loading, required for textures and external images.
The third library `libsdl2-ttf-dev` is the sub library for text loading.
