#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h> 

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

    SDL_Window* win = SDL_CreateWindow("Corrida de Retângulos!",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    SDL_Rect r = {20, 100, 10, 10}; // azul
    SDL_Rect t = {20, 200, 10, 10}; // vermelho (segue mouse)
    SDL_Rect s = {20, 300, 10, 10}; // verde
    SDL_Rect w = {350, 10, 5, 380}; // linha de chegada
    SDL_Event evt;
    bool quit = false;
    Uint32 espera = 500;

    bool fim = false;
    char ordem[4] = "";  
    int chegada = 0;   

    while (!quit) {        
        SDL_Event evt;

        // Usa a função auxiliar
        int gotEvent = AUX_WaitEventTimeout(&evt, &espera);

        if (gotEvent) {             
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
            else if (evt.type == SDL_KEYDOWN) {
                // controla retângulo azul (r)
                switch (evt.key.keysym.sym) {                    
                    case SDLK_LEFT:                     
                        if (r.x > 0) r.x -= 5; 
                        break;
                    case SDLK_RIGHT: 
                        if (r.x < 340) r.x += 5; 
                        break;

                    // controla retângulo verde (s)                    
                    case SDLK_a: 
                        if (s.x > 0) s.x -= 5; 
                        break;
                    case SDLK_d: 
                        if (s.x < 340) s.x += 5; 
                        break;
                }
            }
            else if (evt.type == SDL_MOUSEMOTION) {
                // centraliza retângulo vermelho no cursor
                t.x = evt.motion.x - t.w / 2;                
                if (t.x < 0) t.x = 0;                
                if (t.x > 340) t.x = 340;                
            }
        } else {
            // timeout atingido → reseta
            espera = 500;

            // movimento automático
            if (r.x < 340) r.x += 2;
            if (s.x < 340) s.x += 3;
            if (t.x < 340) t.x += 4;
        }

        // --- CHECAGEM DE CHEGADA ---
        if (!fim) {
            if (r.x >= 340 && !strchr(ordem, 'r')) {
                ordem[chegada++] = 'r';
            }
            if (s.x >= 340 && !strchr(ordem, 's')) {
                ordem[chegada++] = 's';
            }
            if (t.x >= 340 && !strchr(ordem, 't')) {
                ordem[chegada++] = 't';
            }

            if (chegada == 3) {
                ordem[3] = '\0';
                printf("Ordem de chegada: ");
                for (int i = 0; i < 3; i++) {
                    if (ordem[i] == 'r') printf("Azul ");
                    if (ordem[i] == 's') printf("Verde ");
                    if (ordem[i] == 't') printf("Vermelho ");
                }
                printf("\n");
                fim = true;
            }
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

        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); 
        SDL_RenderFillRect(ren, &w);

        SDL_RenderPresent(ren);        
    }

    /* FINALIZAÇÃO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

