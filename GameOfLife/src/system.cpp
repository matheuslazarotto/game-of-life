#include "system.hpp"

System::System(unsigned int game_cells_w, 
               unsigned int game_cells_h, 
               unsigned int cell_pixels)
{
    // Load SDL and set canvas
    int scrWidth = (game_cells_w + 2) * cell_pixels;
    int scrHeight = (game_cells_h + 2) * cell_pixels; 
    canvas.init(scrWidth, scrHeight);
    canvas.clear();
    canvas.setColor(255, 255, 255, 255);

    // Set Game 
    pixel = cell_pixels;
    game.init_game(game_cells_w, game_cells_h);
    
    running_sys = 1;
    running_game = 1;
}

int System::run()
{
    // Set colors
    Uint8 r_cell_dead = 10;
    Uint8 g_cell_dead = 10;
    Uint8 b_cell_dead = 10;
    Uint8 a_cell_dead = 255;

    Uint8 r_cell_live = 33;
    Uint8 g_cell_live = 247;
    Uint8 b_cell_live = 0;
    Uint8 a_cell_live = 255;

    Uint8 r_grid = 200;
    Uint8 g_grid = 200;
    Uint8 b_grid = 200;
    Uint8 a_grid = 255;

    // Flags
    bool hold_grid = false;
    bool hold_pause = false;
    bool draw_grid = true;
    bool pause_iter = false;
    bool live_cell = false;
    bool kill_cell = false;
    double frame_max = 80.0;
    double frame_rate = 30.0;
    double frame_min = 1.0;
    
    // Set clock random seed 
    srand((unsigned) time(0));
    clock_t clock_counter;

    // Set random initial state
    for (unsigned int i = 1; i <= game.get_width(); i++) 
    {
        for (unsigned int j = 1; j <= game.get_height(); j++)
        {
            game.m_output[i][j] = rand() % 2;
        }
    }

    // Game loop
    while (!canvas.quit)
    {
        // Get time
        clock_counter = clock();

        // Event handling
        while (SDL_PollEvent(&(canvas.cEvent)) != 0)
        {
            // Close window request
            if (canvas.cEvent.type == SDL_QUIT) { canvas.quit = true; }

            // Set grid
            if (canvas.cEvent.key.keysym.sym == SDLK_g && !hold_grid)
            {
                if (draw_grid) { draw_grid = false; } // Enable
                else { draw_grid = true; }            // Disable
                hold_grid = true; 
            }

            // Pause
            if (canvas.cEvent.key.keysym.sym == SDLK_SPACE && !hold_pause)
            {
                if (pause_iter) { pause_iter = false; } // Enable
                else { pause_iter = true; }             // Disable
                hold_pause = true;
            }

            // Give live to a cell
            if (canvas.cEvent.button.button == SDL_BUTTON_LEFT)
            {
                live_cell = true;
            }
            // Kill a cell
            if (canvas.cEvent.button.button == SDL_BUTTON_RIGHT)
            {
                kill_cell = true;
            }

            // Increase|Decrease frame rate
            if (canvas.cEvent.key.keysym.sym == SDLK_w)
            {
                frame_rate += 1.0;
                if (frame_rate > frame_max) { frame_rate = frame_max; }
            }
            if (canvas.cEvent.key.keysym.sym == SDLK_s)
            {
                frame_rate -= 1.0;
                if (frame_rate < frame_min) { frame_rate = frame_min; }
            }
        }

        // Clear current frame
        canvas.clear();

        if (pause_iter) // Pause iteration
        {
            // Draw current state
            for (unsigned int i = 1; i <= game.get_width(); i++)
            {
                for (unsigned int j = 1; j <= game.get_height(); j++)
                {
                    if (game.m_output[i][j] == 1)
                    {
                        canvas.drawPixel(i * pixel, j * pixel, pixel, 
                                         r_cell_live, g_cell_live, 
                                         b_cell_live, a_cell_live);
                    }
                    else if (game.m_output[i][j] == 0)
                    {
                        canvas.drawPixel(i * pixel, j * pixel, pixel, 
                                         r_cell_dead, g_cell_dead, 
                                         b_cell_dead, a_cell_dead);
                    }
                }
            }

            // Draw hightlighted cell
            SDL_GetMouseState(&canvas.cX, &canvas.cY);
            int pixel_i = canvas.cX / pixel;
            int pixel_j = canvas.cY / pixel;
            canvas.drawPixel(pixel_i * pixel, pixel_j * pixel, pixel, 255, 255, 255, 255);

            // Set selected pixel to state
            if (live_cell)
            {
                game.m_output[pixel_i][pixel_j] = 1;
                live_cell = false;
            }

            // Unset selected pixel
            if (kill_cell)
            {
                game.m_output[pixel_i][pixel_j] = 0;
                kill_cell = false;
            }
        }
        else // Evolve state
        {
        
            // Store output state
            for (unsigned int i = 1; i <= game.get_width(); i++)
            {
                for (unsigned int j = 1; j <= game.get_height(); j++)
                {
                    game.set_cell_state(i, j, game.m_output[i][j]);
                }
            }

            // Evolve and and draw
            for (unsigned int i = 1; i <= game.get_width(); i++)
            {
                for (unsigned int j = 1; j <= game.get_height(); j++)
                {
                    game.evolve_cell(i, j);

                    if (game.m_output[i][j] == 1)
                    {
                        canvas.drawPixel(i * pixel, j * pixel, pixel, 
                                         r_cell_live, g_cell_live, 
                                         b_cell_live, a_cell_live);
                    }
                    else if (game.m_output[i][j] == 0)
                    {
                        canvas.drawPixel(i * pixel, j * pixel, pixel, 
                                         r_cell_dead, g_cell_dead, 
                                         b_cell_dead, a_cell_dead);
                    }
                }
            }

        }

        // Draw grid
        if (draw_grid)
        {
            if (pixel > 1) // Avoid loop prison
            {
                for (int i = pixel; i < canvas.getWidth(); i += pixel)
                {
                    canvas.drawLine(i, pixel, i, canvas.getHeight()-pixel,
                                    r_grid, g_grid, b_grid, a_grid);
                }
                for (int j = pixel; j < canvas.getHeight(); j += pixel)
                {
                    canvas.drawLine(pixel, j, canvas.getWidth()-pixel, j,
                                    r_grid, g_grid, b_grid, a_grid);
                }
            }
        }

        canvas.show();
        
        // Hold time
        if (!pause_iter)
        {
            while(CLOCKS_PER_SEC / frame_rate > (clock() - clock_counter))
		    {
		    }
        }

        hold_grid = false;
        hold_pause = false;
    }
        
    if (canvas.quit == true) { return 0; }

    return 1;
}

int System::handle_event()
{
    // Future implementation, given that small bugs in 
    // in commands are happening :/
    //// State handling
    //Uint8 *key_state = SDL_GetKeyboardState(NULL);

    return 0;
}

int System::sys_quit()
{
    return canvas.canvas_quit();
}
