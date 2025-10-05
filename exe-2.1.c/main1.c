#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h> // para abs()

#define MY_EVENT (SDL_USEREVENT + 1)
#define CLICK_TIMEOUT 250

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    SDL_Window* win = SDL_CreateWindow("Multi-Click",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       400, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;

    SDL_Rect rect = {100, 100, 200, 150};

    int clickCount = 0;
    Uint32 lastClickTime = 0;
    int lastX = -1, lastY = -1;

    SDL_Event evt; 
    
    // Limpa a tela
    SDL_SetRenderDrawColor(ren, 255,255,255,255);
    SDL_RenderClear(ren); 
    SDL_RenderPresent(ren);

    while (!quit) {                
        // Espera eventos com timeout
        if (SDL_WaitEventTimeout(&evt, CLICK_TIMEOUT)) {
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
            else if (evt.type == SDL_MOUSEBUTTONDOWN) {
                Uint32 now = SDL_GetTicks();

                if (clickCount == 0 ||
                   (now - lastClickTime <= CLICK_TIMEOUT &&
                    abs(evt.button.x - lastX) < 5 &&
                    abs(evt.button.y - lastY) < 5)) 
                {
                    // Continua sequência de cliques
                    clickCount++;
                    lastClickTime = now;
                    lastX = evt.button.x;
                    lastY = evt.button.y;
                } else {
                    // Expirou → gera evento anterior
                    SDL_Event userevent;
                    userevent.type = MY_EVENT;
                    userevent.user.code = clickCount;
                    userevent.user.data1 = NULL;
                    userevent.user.data2 = NULL;
                    SDL_PushEvent(&userevent);

                    // Reinicia sequência
                    clickCount = 1;
                    lastClickTime = now;
                    lastX = evt.button.x;
                    lastY = evt.button.y;
                }
            }
        } else {
            // Timeout sem evento → finalizar múltiplo clique
            if (clickCount > 0) {
                SDL_Event userevent;
                userevent.type = MY_EVENT;
                userevent.user.code = clickCount;
                userevent.user.data1 = NULL;
                userevent.user.data2 = NULL;
                SDL_PushEvent(&userevent);
                clickCount = 0;
            }
        }
               
        // Trata eventos customizados de múltiplos cliques
        if (evt.type == MY_EVENT) {            
            switch (evt.user.code) {
                case 1: // Clique simples
                    SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
                    SDL_RenderClear(ren);
                    SDL_RenderPresent(ren);
                    break;
                case 2: // Duplo clique
                    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                    SDL_RenderDrawRect(ren, &rect);
                    SDL_RenderPresent(ren);
                    break;
                case 3: // Triplo clique
                    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                    SDL_RenderFillRect(ren, &rect);
                    SDL_RenderPresent(ren);
                    break;
                case 4: // Quádruplo clique → sair
                    quit = true;
                    break;
            }                       
        }        
    }
    
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

