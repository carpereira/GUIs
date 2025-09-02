#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Aplicação três Retângulos!",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /*EXECUÇÃO*/
    SDL_Rect r = {100, 20, 10, 10}; // azul
    SDL_Rect t = {200, 20, 10, 10}; // vermelho (segue mouse)
    SDL_Rect s = {300, 20, 10, 10}; // verde
    SDL_Event evt;
    bool quit = false;

    while (!quit) {
        // espera até 500ms por evento
        int isevt = SDL_WaitEventTimeout(&evt, 500);

        if (isevt) {
            if (evt.type == SDL_QUIT)
                quit = true;
            else if (evt.type == SDL_KEYDOWN) {
                // controla retângulo azul (r)
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:    
                    if (r.y > 0) 
                    r.y -= 5;                 
                    break;
                    case SDLK_DOWN:  
                    if (r.y < 390) 
                    r.y += 5; 
                    break;
                    case SDLK_LEFT:                     
                    if (r.x > 0) 
                    r.x -= 5; 
                    break;
                    case SDLK_RIGHT: 
                    if (r.x < 390) 
                    r.x += 5; 
                    break;

                    // controla retângulo verde (s)
                    case SDLK_w: 
                    if (s.y > 0) 
                    s.y -= 5; 
                    break;
                    case SDLK_s: 
                    if (s.y < 390) 
                    s.y += 5; 
                    break;
                    case SDLK_a: 
                    if (s.x > 0) 
                    s.x -= 5; 
                    break;
                    case SDLK_d: 
                    if (s.x < 390) 
                    s.x += 5; 
                    break;
                }
            }
            else if (evt.type == SDL_MOUSEMOTION) {
                // centraliza retângulo vermelho no cursor
                t.x = evt.motion.x - t.w / 2;
                t.y = evt.motion.y - t.h / 2;
                // limites da janela
                if (t.x < 0) t.x = 0;
                if (t.y < 0) t.y = 0;
                if (t.x > 400 - t.w) t.x = 400 - t.w;
                if (t.y > 400 - t.h) t.y = 400 - t.h;
            }
        } else {
            // se não houve evento em 500ms, move r automaticamente
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

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); 
        SDL_RenderFillRect(ren, &t);

        SDL_SetRenderDrawColor(ren, 0, 255, 0, 255); 
        SDL_RenderFillRect(ren, &s);

        SDL_RenderPresent(ren);
    }
    /*FINALIZAÇÃO*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

