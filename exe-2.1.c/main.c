#include <SDL2/SDL.h>
#include <stdbool.h>

#define CLICK_TIMEOUT 250

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);

    SDL_Window* win = SDL_CreateWindow("Multi-Click",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       400, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    bool quit = false;
    SDL_Event evt;

    SDL_Rect rect = {100, 100, 200, 150};

    int clickCount = 0;
    Uint32 lastClickTime = 0;
    int lastX = -1, lastY = -1;

    while (!quit) {
        // Espera eventos
        if (SDL_WaitEventTimeout(&evt, CLICK_TIMEOUT)) {
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
            else if (evt.type == SDL_MOUSEBUTTONDOWN) {
                Uint32 now = SDL_GetTicks();
                // Primeiro clique ou clique dentro da janela
                if (clickCount == 0 ||
                   (now - lastClickTime <= CLICK_TIMEOUT &&
                    abs(evt.button.x - lastX) < 5 &&
                    abs(evt.button.y - lastY) < 5)) 
                {
                    clickCount++;
                    lastClickTime = now;
                    lastX = evt.button.x;
                    lastY = evt.button.y;
                } else {
                    // Expirou, gera evento anterior
                    SDL_Event userEvent;
                    userEvent.type = SDL_USEREVENT;
                    userEvent.user.code = clickCount;
                    SDL_PushEvent(&userEvent);

                    // Novo clique inicia nova contagem
                    clickCount = 1;
                    lastClickTime = now;
                    lastX = evt.button.x;
                    lastY = evt.button.y;
                }
            }
        } else {
            // Timeout sem evento → finalizar múltiplo clique
            if (clickCount > 0) {
                SDL_Event userEvent;
                userEvent.type = SDL_USEREVENT;
                userEvent.user.code = clickCount;
                SDL_PushEvent(&userEvent);
                clickCount = 0;
            }
        }
        // Trata evento de múltiplos cliques
        if (evt.type == SDL_USEREVENT) {
    switch (evt.user.code) {
        case 1:
            SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
            SDL_RenderClear(ren);
            SDL_RenderPresent(ren);
            break;
        case 2:
            SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
            SDL_RenderDrawRect(ren, &rect);
            SDL_RenderPresent(ren);
            break;
        case 3:
            SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
            SDL_RenderFillRect(ren, &rect);
            SDL_RenderPresent(ren);
            break;
        case 4:
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
