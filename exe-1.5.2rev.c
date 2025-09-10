#include <SDL2/SDL.h>
#include <stdbool.h>

// Função auxiliar que desconta o tempo passado
int AUX_WaitEventTimeout(SDL_Event* evt, Uint32* ms) {
    Uint32 antes = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    Uint32 decorrido = SDL_GetTicks() - antes;

    if (*ms > decorrido) {
        *ms -= decorrido;
    } else {
        *ms = 0;
    }
    return ret;
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Contando o tempo!",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /*EXECUÇÃO*/
    SDL_Rect r = {100, 20, 10, 10};     
    bool quit = false;
    Uint32 espera = 500;    

    while (!quit) {        
        SDL_Event evt;
        
        int gotEvent = AUX_WaitEventTimeout(&evt, &espera);

        if (gotEvent) {             
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
            else if (evt.type == SDL_KEYDOWN) {
                // controla retângulo azul (r)
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:    
                        if (r.y > 0) r.y -= 5;                 
                        break;
                    case SDLK_DOWN:  
                        if (r.y < 390) r.y += 5; 
                        break;
                    case SDLK_LEFT:                     
                        if (r.x > 0) r.x -= 5; 
                        break;
                    case SDLK_RIGHT: 
                        if (r.x < 390) r.x += 5; 
                        break;
                }
            }
        } else {            
            // timeout atingido → reseta
            espera = 500;

            // movimento automático
            r.x += 2;
            r.y += 2;
            if (r.x > 400 - r.w) r.x = 0;
            if (r.y > 400 - r.h) r.y = 0;
        }
        // --- DESENHO ---
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
}

