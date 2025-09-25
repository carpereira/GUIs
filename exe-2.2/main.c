#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char* args[])
{
    /*INICIALIZAÇÃO*/
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* win = SDL_CreateWindow("Drag, Click, or Cancel",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       200, 200,
                                       SDL_WINDOW_SHOWN);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    /*EXECUÇÃO*/
    SDL_Rect r = {75, 70, 50, 50};

    bool running = true;
    bool dragging = false;
    bool clicked = false;
    SDL_Point dragStart = {0, 0};
    SDL_Point origPos = {r.x, r.y};
    bool quit = false;
    SDL_Event evt;

  while (!quit) {
        // espera até 500ms por evento
        int isevt = SDL_WaitEventTimeout(&evt, 500);

        if (isevt) {
            if (evt.type == SDL_QUIT)
                quit = true;
            switch (evt.type) {
                case SDL_MOUSEBUTTONDOWN:
                    if (evt.button.button == SDL_BUTTON_LEFT &&
                        SDL_PointInRect(&(SDL_Point){evt.button.x, evt.button.y}, &r)) {
                        dragging = true;
                        clicked = true;
                        dragStart.x = evt.button.x - r.x;
                        dragStart.y = evt.button.y - r.y;
                        SDL_Log("Dragging");
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (dragging) {
                        dragging = false;
                        if (clicked)
                            SDL_Log("Clicked!");
                        else
                            SDL_Log("Dropped!");
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (dragging) {
                        r.x = evt.motion.x - dragStart.x;
                        r.y = evt.motion.y - dragStart.y;
                        clicked = false;
                    }
                    break;

                case SDL_KEYDOWN:
                    if (evt.key.keysym.sym == SDLK_ESCAPE || (SDLK_ESCAPE && dragging)) {
                        dragging = false;
                        r.x = origPos.x;
                        r.y = origPos.y;
                        SDL_Log("Cancelled!");
                    }
                    break;                    
            }         
        }

        /*DESENHO*/
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
        SDL_RenderFillRect(ren, &r);

        SDL_RenderPresent(ren);
    }

    /*FINALIZAÇÃO*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
