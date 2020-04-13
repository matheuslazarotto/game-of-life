#ifndef CANVAS_H
#define CANVAS_H

#include <cstdio>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

class Canvas 
{
    public:
        SDL_Event cEvent;

        Canvas() {};
        Canvas(const Canvas &);
        Canvas& operator=(const Canvas &);
        ~Canvas();

        void init(unsigned int scrWidth, unsigned int scrHeight,
                  string WindowName = "Game of Life",
                  unsigned short int r = 255,
                  unsigned short int g = 255,
                  unsigned short int b = 255);
        
        void show();

        void clear(Uint8 r = 255, Uint8 g = 255, Uint8 b = 255);

        void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha);
        
        void setViewport(int x, int y, int w, int h);

        void drawLine(int xo, int yo, int xf, int yf,
                      Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        
        void drawPoint(int xo, int yo, 
                       Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        void drawPixel(int xo, int yo, short int pixel,
                       Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        int getWidth() { return cWidth; }
        
        int getHeight() { return cHeight; }

        int canvas_quit();

        // Canvas coordinates
        int cX;
        int cY;
        
        // Flags
        bool quit = false;

    private:
        SDL_Window *cWindow;
        SDL_Renderer *cRenderer;

        unsigned int cWidth;
        unsigned int cHeight;
};

#endif