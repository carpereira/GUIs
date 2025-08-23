#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
/*INICIALIZAÇÃO*/
SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* win = SDL_CreateWindow("Animação Circular!",
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      400, 400, SDL_WINDOW_SHOWN
                      );
SDL_Renderer* ren = SDL_CreateRenderer(win, -1,0);

/*EXECUÇÃO*/
SDL_Rect r = {40,20,10,10};
SDL_Rect s = {360,20,10,10};
SDL_Rect t = {360,380,10,10};
SDL_Rect w = {20,380,10,10};

while (w.y>20){
    if(r.x<360){
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
        SDL_Delay(100);
        r.x += 2;
        r.y = 20; 
    } 
    else if(r.x==360 && s.y<380){
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(ren, &s);
    SDL_RenderPresent(ren);
    SDL_Delay(100);
    r.x = 360;
    s.y += 2;     
}
    else if(s.y==380 && t.x>20){
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(ren, &t);
    SDL_RenderPresent(ren);
    SDL_Delay(100);
    s.y = 380;
    t.x -= 2;    
}
    else if(t.x==20 && w.y>20){
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
    SDL_RenderFillRect(ren, &w);
    SDL_RenderPresent(ren);
    SDL_Delay(100);
    t.x = 20;
    w.y -= 2;    
}
}
/*FINALIZAÇÃO*/
SDL_DestroyRenderer(ren);
SDL_DestroyWindow(win);
SDL_Quit();
}

