#include <SDL2/SDL.h>
#include <stdbool.h>

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Animando e Movendo um Retângulo",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         300, 300, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    
    /* EXECUÇÃO */
    SDL_Rect r = { 0,0, 20,20 };      // retângulo que desce e vai para direita
    SDL_Rect s = {280,280,20,20};     // retângulo que sobe e vai para esquerda
    SDL_Rect t = {150,150,20,20};     // segue o mouse
    
    bool quit = false;
    SDL_Event evt;
    int dir_r;
    int dir_s;
    
    while(!quit){ 
        int isert = SDL_WaitEventTimeout(&evt, 30);               
        
        if (isert){
            if (evt.type == SDL_QUIT)
                quit = true;   
            else if (evt.type == SDL_MOUSEMOTION) {
                // centraliza retângulo t no cursor
                t.x = evt.motion.x - t.w / 2;
                t.y = evt.motion.y - t.h / 2;
                // limites da janela
                if (t.x < 0) t.x = 0;
                if (t.y < 0) t.y = 0;
                if (t.x > 300 - t.w) t.x = 300 - t.w;
                if (t.y > 300 - t.h) t.y = 300 - t.h;             
            }     
        }
        // Movimento automático de r
switch (dir_r) {
    case 0: // baixo
        r.y += 2;
        if (r.y >= 280) dir_r = 1;
        break;
    case 1: // direita
        r.x += 2;
        if (r.x >= 280) dir_r = 2;
        break;
    case 2: // cima
        r.y -= 2;
        if (r.y <= 0) dir_r = 3;
        break;
    case 3: // esquerda
        r.x -= 2;
        if (r.x <= 0) dir_r = 0;
        break;
}

    // Movimento automático de s 
    switch (dir_s) {
        case 0: // cima
            s.y -= 2;
            if (s.y <= 0) dir_s = 1;
            break;
        case 1: // esquerda
            s.x -= 2;
            if (s.x <= 0) dir_s = 2;
            break;
        case 2: // baixo
            s.y += 2;
            if (s.y >= 280) dir_s = 3;
            break;
        case 3: // direita
            s.x += 2;
            if (s.x >= 280) dir_s = 0;
            break;
    }

        // Limpa a tela
        SDL_SetRenderDrawColor(ren, 255,255,255,255);
        SDL_RenderClear(ren);

        // Desenha r (vermelho)
        SDL_SetRenderDrawColor(ren, 255,0,0,255);
        SDL_RenderFillRect(ren, &r);

        // Desenha s (verde)
        SDL_SetRenderDrawColor(ren, 0,255,0,255);
        SDL_RenderFillRect(ren, &s);

        // Desenha t (azul, segue o mouse)
        SDL_SetRenderDrawColor(ren, 0,0,255,255);
        SDL_RenderFillRect(ren, &t);

        // Atualiza a tela
        SDL_RenderPresent(ren);
    }

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
