#include "canvas.hpp"

Canvas::Canvas(const Canvas &other)
{
    *this = other;
}

Canvas& Canvas::operator=(const Canvas &other)
{
    if (this != &other)
    {
        cWidth = other.cWidth;
        cHeight = other.cHeight;
        cWindow = other.cWindow;
        cRenderer = other.cRenderer;
        cEvent = other.cEvent;
    }

    return *this;
}

Canvas::~Canvas()
{
    SDL_DestroyRenderer(cRenderer);
    SDL_DestroyWindow(cWindow);
    cRenderer = NULL;
    cWindow = NULL;

    SDL_Quit();
}

void Canvas::init(unsigned int scrWidth, unsigned int scrHeight, string WindowName, 
             unsigned short int r, unsigned short int g, unsigned short int b)
{
    if (0 > SDL_Init(SDL_INIT_VIDEO))
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        // Window creation
        cWindow = SDL_CreateWindow(WindowName.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                                       SDL_WINDOWPOS_UNDEFINED,
                                                       scrWidth, scrHeight,
                                                       SDL_WINDOW_SHOWN |
                                                       SDL_WINDOW_RESIZABLE);
        if (NULL == cWindow)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        }

        // Renderer creation
        cRenderer = SDL_CreateRenderer(cWindow, -1, SDL_RENDERER_SOFTWARE);
        if (NULL == cRenderer)
        {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_SetRenderDrawColor(cRenderer, r, g, b, 255);
            cWidth = scrWidth;
            cHeight = scrHeight;
        }
        
        SDL_SetRenderDrawColor(cRenderer, r, g, b, 255);
        SDL_RenderClear(cRenderer);
        SDL_SetRenderTarget(cRenderer, NULL);
    }
}

void Canvas::show()
{
    SDL_RenderPresent(cRenderer);
}

void Canvas::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 alpha)
{
    SDL_SetRenderDrawColor(cRenderer, r, g, b, alpha);
}

void Canvas::clear(Uint8 r, Uint8 g, Uint8 b) 
{
    SDL_SetRenderDrawColor(cRenderer, r, g, b, 255);
    SDL_RenderClear(cRenderer);
}

void Canvas::setViewport(int x, int y, int w, int h)
{
    SDL_Rect viewport = {x, y, w, h};
    SDL_RenderSetViewport(cRenderer, &viewport);
}

void Canvas::drawLine(int xo, int yo, int xf, int yf, 
                      Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    setColor(r, g, b, a);
    SDL_RenderDrawLine(cRenderer, xo, yo, xf, yf);
}

void Canvas::drawPoint(int xo, int yo, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    setColor(r, g, b, a);
    SDL_RenderDrawPoint(cRenderer, xo, yo);
}

void Canvas::drawPixel(int xo, int yo, short int pixel, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Rect pixel_rect = {xo, yo, pixel, pixel};
    setColor(r, g, b, a);
    SDL_RenderFillRect(cRenderer, &pixel_rect);
}

int Canvas::canvas_quit()
{
    SDL_DestroyRenderer(cRenderer);
    SDL_DestroyWindow(cWindow);
    cRenderer = NULL;
    cWindow = NULL;

    SDL_Quit();

    return 0;
}