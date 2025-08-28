#include <SDL2/SDL.h>
#include <stdbool.h>

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Retângulos com Teclado e Mouse",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         200, 100, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    /*Execução*/
    SDL_Rect r = {40,20,10,10};  
    SDL_Event evt;
    bool quit = false;
    int a = 0;

    // lista de cores para os cliques
    SDL_Color cores[10] = {
        {173,255, 47,255}, {127,255,212,255}, {173,255,47,255},
        {255,255,  0,255}, {  0,255,  0,255}, {255,  0,  0,255},
        {176,224,230,255}, {216,191,216,255}, {255,165,  0,255},
        {255,105,180,255}
    };

    // guarda até 10 quadrados clicados
    SDL_Rect quadrados[10];

    while (!quit) {
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT)
                quit = true;

            else if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if (r.y > 0)   
                        r.y -= 5; break;
                    case SDLK_DOWN:
                        if (r.y < 90)                         
                        r.y += 5; 
                        break;
                    case SDLK_LEFT:
                        if (r.x > 0)   
                        r.x -= 5; 
                        break;
                    case SDLK_RIGHT: 
                        if (r.x < 190)                         
                        r.x += 5;                    
                        break;
                }
            }
            else if (evt.type == SDL_MOUSEBUTTONDOWN) {
                if (a < 10) {
                    quadrados[a].x = evt.button.x;
                    quadrados[a].y = evt.button.y;
                    quadrados[a].w = 10;
                    quadrados[a].h = 10;
                    a++;
                }
            }
        }

        // desenhar fundo
        SDL_SetRenderDrawColor(ren, 255,255,255,255);
        SDL_RenderClear(ren);

        // desenhar quadrado azul controlado pelo teclado
        SDL_SetRenderDrawColor(ren, 0,0,255,255);
        SDL_RenderFillRect(ren, &r);

        // desenhar quadrados clicados com as cores
        for (int i = 0; i < a; i++) {
            SDL_SetRenderDrawColor(ren, cores[i].r, cores[i].g, cores[i].b, 255);
            SDL_RenderFillRect(ren, &quadrados[i]);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(10); 
    }
    /*Finalização*/
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

