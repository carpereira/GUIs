#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("Figuras Complexas!",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);

    /* Retângulo arredondado */
    /*filledRoundedRectangleRGBA(ren, 40, 200, 100, 100, 20, 0, 255, 0, 255);*/
    roundedRectangleRGBA(ren, 40, 200, 100, 100, 20, 0, 0, 0, 255);

    /* Triângulo */
    Sint16 vx[3] = {200, 250, 300};
    Sint16 vy[3] = {300, 200, 300};
    filledPolygonRGBA(ren, vx, vy, 3, 0, 255, 255, 255);
    polygonRGBA(ren, vx, vy, 3, 0, 0, 139, 255);

    /* Círculo */
    filledCircleRGBA(ren, 150, 200, 50, 120, 0, 0, 255);
    circleRGBA(ren, 150, 200, 50, 220, 20, 60, 255);

    /* Elipse */
    filledEllipseRGBA(ren, 100, 30, 100, 30, 255, 255, 0, 255);
    ellipseRGBA(ren, 100, 30, 100, 30, 10, 20, 60, 255);

    /* Pera (duas elipses) */
    filledEllipseRGBA(ren, 300, 120, 40, 60, 0, 255, 0, 255);  
    filledEllipseRGBA(ren, 300, 100, 25, 35, 0, 200, 0, 255);  

    SDL_RenderPresent(ren);
    SDL_Delay(9000);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
