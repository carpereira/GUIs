#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>

#define VELOCIDADE 30.0f
#define BATIDA_INTERVALO 250

// ✅ Adicionada a função auxiliar
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

int main(int argc, char* args[]) {
    /*INICIALIZAÇÃO*/
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* win = SDL_CreateWindow("Animando e Movendo um Pássaro",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       300, 300, SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* birdTex = IMG_LoadTexture(ren, "bird.png");
    assert(birdTex != NULL);

    bool quit = false, isup = true;
    int dir_r = 0, dir_s = 0;
    Uint32 espera = 10; // ✅ variável necessária para o AUX_WaitEventTimeout

    /*EXECUÇÃO*/
    SDL_Rect r = {0, 0, 30, 30};
    SDL_Rect s = {270, 270, 30, 30};
    SDL_Rect t = {120, 120, 100, 60};
    SDL_Rect c;

    float pos_r_x = 0, pos_r_y = 0;
    float pos_s_x = 270, pos_s_y = 270;

    Uint32 last_tick = SDL_GetTicks();
    Uint32 last_batida = SDL_GetTicks();

    while (!quit) {
        Uint32 now = SDL_GetTicks();
        float delta = (now - last_tick) / 1000.0f;
        last_tick = now;

        SDL_Event evt;
        int auxEvt = AUX_WaitEventTimeout(&evt, &espera);

        if (auxEvt) {
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
            else if (evt.type == SDL_MOUSEMOTION) {
                t.x = evt.motion.x - t.w / 2;
                t.y = evt.motion.y - t.h / 2;
                if (t.x < 0) t.x = 0;
                if (t.y < 0) t.y = 0;
                if (t.x > 300 - t.w) t.x = 300 - t.w;
                if (t.y > 300 - t.h) t.y = 300 - t.h;
            }
        }

        if (now - last_batida >= BATIDA_INTERVALO) {
            isup = !isup;
            last_batida = now;
        }

        switch (dir_r) {
            case 0: pos_r_y += VELOCIDADE * delta; if (pos_r_y >= 270) dir_r = 1; break;
            case 1: pos_r_x += VELOCIDADE * delta; if (pos_r_x >= 270) dir_r = 2; break;
            case 2: pos_r_y -= VELOCIDADE * delta; if (pos_r_y <= 0)   dir_r = 3; break;
            case 3: pos_r_x -= VELOCIDADE * delta; if (pos_r_x <= 0)   dir_r = 0; break;
        }
        r.x = (int)pos_r_x;
        r.y = (int)pos_r_y;

        switch (dir_s) {
            case 0: pos_s_y -= VELOCIDADE * delta; if (pos_s_y <= 0)   dir_s = 1; break;
            case 1: pos_s_x -= VELOCIDADE * delta; if (pos_s_x <= 0)   dir_s = 2; break;
            case 2: pos_s_y += VELOCIDADE * delta; if (pos_s_y >= 270) dir_s = 3; break;
            case 3: pos_s_x += VELOCIDADE * delta; if (pos_s_x >= 270) dir_s = 0; break;
        }
        s.x = (int)pos_s_x;
        s.y = (int)pos_s_y;

        c = isup ? (SDL_Rect){0, 0, 100, 80} : (SDL_Rect){100, 0, 100, 80};

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, birdTex, &c, &r);
        SDL_RenderCopy(ren, birdTex, &c, &s);
        SDL_RenderCopy(ren, birdTex, NULL, &t);
        SDL_RenderPresent(ren);
    }

    /*FINALIZAÇÃO*/
    SDL_DestroyTexture(birdTex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
