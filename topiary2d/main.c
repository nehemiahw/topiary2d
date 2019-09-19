#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdbool.h>

//STRUCTS//////////////////////////////////////////////////////////
typedef struct
{
    int x, y;
    short life;
    char* name;
}Man;

//CONSTANTS////////////////////////////////////////////////////////

//VARIABLE DECLARATIONS////////////////////////////////////////////
bool fullScreen = false;
//FUNCTION DECLARATIONS////////////////////////////////////////////
bool init(void);
void loadFiles();

int processEvents(SDL_Window* window, Man* man)
{
    SDL_Event event;
    int quit = 0;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    quit = 1;
                }
            }
            break;
        //keydown case
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = 1;
                break;
            }
        }//end of keydown case
            break;
        case SDL_QUIT:
            quit = 1;
            break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT])
    {
        man->x -= 10;
    }

    if(state[SDL_SCANCODE_RIGHT])
    {
        man->x += 10;
    }

    if(state[SDL_SCANCODE_UP])
    {
        man->y -= 10;
    }

    if(state[SDL_SCANCODE_DOWN])
    {
        man->y += 10;
    }

    return quit;
}

void renderToScr(SDL_Renderer* renderer, Man* man)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect rect = {man->x, man->y, 50, 90};
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}


int main(int argc, const char* argv[])
{
    //the window being rendered to
    SDL_Window*   window;
    SDL_Renderer* renderer;

    //the surface contained by the window
    SDL_Surface*  surface;
    SDL_Texture*  texture;
    SDL_Event     event;

    //Initialize SDL2
    SDL_Init(SDL_INIT_VIDEO);

    Man man;
    man.x = 220;
    man.y = 140;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize SDL_ERROR: %s\n", SDL_GetError());
    }

    window  = SDL_CreateWindow("window",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1920,
                               1080,
                               SDL_VIDEO_OPENGL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    surface  = SDL_GetWindowSurface(window);

    int quit = 0;

    while(!quit)
    {
        if(processEvents(window, &man) == 1)
            quit = 1;

        renderToScr(renderer, &man);

        SDL_Delay(33);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    SDL_Quit();

return 0;
}
