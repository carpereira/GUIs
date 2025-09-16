#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PLAYER_SPEED 5
#define ENEMY_SPEED 3
#define MAP_WIDTH 25
#define MAP_HEIGHT 19
#define MAX_FASES 3
#define COINS_TO_NEXT 3

int tile_width = 32;
int tile_height = 32;
int tileset_width_in_tiles = 8;
int score = 0;
int fase = 1;
SDL_Rect porta = {WINDOW_WIDTH - 100, WINDOW_HEIGHT - 150, 60, 90};
bool portaAtiva = false; 

int main(int argc, char* args[]) {
    // --- Inicializações ---
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);
    Mix_Music* musicas[MAX_FASES];


    // Inicializar sistema de áudio (44.1kHz, estéreo, buffer 2048)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erro ao inicializar SDL_mixer: %s\n", Mix_GetError());
        return 1;
    }

    srand(time(NULL));

    SDL_Window* win = SDL_CreateWindow("Mario 2D - UERJ",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN);
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

     // Inicializar mapa com bordas sólidas
    int map_data[MAP_HEIGHT][MAP_WIDTH];
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_data[y][x] = (y == 0 || y == MAP_HEIGHT - 1 || x == 0 || x == MAP_WIDTH - 1) ? 1 : 0;
        }
    }

    // --- Carregar Texturas ---
    SDL_Texture* playerTex = IMG_LoadTexture(ren, "assets/player.png");
    SDL_Texture* enemyTex  = IMG_LoadTexture(ren, "assets/enemy.png");
    SDL_Texture* coinTex   = IMG_LoadTexture(ren, "assets/coin.png");
    SDL_Texture* tilemap1Tex = IMG_LoadTexture(ren, "assets/tile.png");//
    SDL_Texture* tilemap2Tex = IMG_LoadTexture(ren, "assets/tile1.jpeg");
    SDL_Texture* tilemap3Tex = IMG_LoadTexture(ren, "assets/tile2.png");

    //---Carregar musicas por fase
    musicas[0] = Mix_LoadMUS("assets/fase1.mp3");
    musicas[1] = Mix_LoadMUS("assets/fase2.mp3");
    musicas[2] = Mix_LoadMUS("assets/fase3.mp3");
    if (musicas[0]) {
        Mix_PlayMusic(musicas[0], -1);
    }

       // --- Carregar som da moeda ---
    Mix_Chunk* coinSound = Mix_LoadWAV("assets/coin.mp3");
    if (!coinSound) {
        printf("Erro ao carregar som: %s\n", Mix_GetError());
    }

    // --- Criar Retângulos ---
    SDL_Rect player = {100, 500, 70, 70};
    SDL_Rect enemy  = {400, 500, 30, 30};
    SDL_Rect coin   = {200, 500, 30, 30};
    SDL_Rect sourceRect; // Posição do tile no spritesheet
    SDL_Rect destRect; //

    int score = 0;
    SDL_Event evt;
    bool quit = false;

    int enemy_dx = (rand() % 3) - 1;
    int enemy_dy = (rand() % 3) - 1;
    int changeDirTimer = 0;

       // --- Carregar sprite da explosão ---
    SDL_Texture* explosionTex = IMG_LoadTexture(ren, "assets/explosion.png");
    if (!explosionTex) {
        printf("Erro ao carregar sprite de explosão: %s\n", IMG_GetError());
    }

    // --- Carregar som de explosão ---
    Mix_Chunk* explosionSound = Mix_LoadWAV("assets/explosion.mp3");
    if (!explosionSound) {
        printf("Erro ao carregar som de explosão: %s\n", Mix_GetError());
    }

    // --- Variáveis de explosão ---
    bool explosionActive = false;
    int explosionFrame = 0;
    SDL_Rect explosionRect = {0, 0, 64, 64}; // tamanho de cada frame (ajuste conforme seu sprite)
    SDL_Rect explosionPos;

    while (!quit) {
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT)
                quit = true;
        }

        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if (keystate[SDL_SCANCODE_LEFT] && player.x > 0)
            player.x -= PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_RIGHT] && player.x < WINDOW_WIDTH - player.w)
            player.x += PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_UP] && player.y > 0)
            player.y -= PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_DOWN] && player.y < WINDOW_HEIGHT - player.h)
            player.y += PLAYER_SPEED;

        if (changeDirTimer <= 0) {
            enemy_dx = (rand() % 3) - 1;
            enemy_dy = (rand() % 3) - 1;
            changeDirTimer = 60;
        } else {
            changeDirTimer--;
        }

        enemy.x += enemy_dx * ENEMY_SPEED;
        enemy.y += enemy_dy * ENEMY_SPEED;

        if (enemy.x < 0) enemy.x = 0;
        if (enemy.x > WINDOW_WIDTH - enemy.w) enemy.x = WINDOW_WIDTH - enemy.w;
        if (enemy.y < 0) enemy.y = 0;
        if (enemy.y > WINDOW_HEIGHT - enemy.h) enemy.y = WINDOW_HEIGHT - enemy.h;

        // --- Colisão com moeda ---
        if (SDL_HasIntersection(&player, &coin)) {
            score++;

            // toca som da moeda
            if (coinSound)
                Mix_PlayChannel(-1, coinSound, 0);

            // reposiciona moeda
            coin.x = rand() % (WINDOW_WIDTH - coin.w);
            coin.y = rand() % (WINDOW_HEIGHT - coin.h);

            // Ativar porta quando pegar 10 moedas
            if (score >= COINS_TO_NEXT) {
                portaAtiva = true;
            }
        }

        // --- Colisão com porta ---
        if (portaAtiva && SDL_HasIntersection(&player, &porta)) {
            fase++;
            score = 0;           // reseta moedas
            portaAtiva = false;  // esconde porta

            player.x = 100; 
            player.y = 500;

            enemy.x = 400; 
            enemy.y = 500;

            coin.x = rand() % (WINDOW_WIDTH - coin.w);
            coin.y = rand() % (WINDOW_HEIGHT - coin.h);

            if (fase > MAX_FASES) {
                printf("Parabéns! Você completou todas as fases!\n");
                quit = true;
             } else {
                Mix_HaltMusic();
                if (musicas[fase - 1]){
                    Mix_PlayMusic(musicas[fase - 1], -1);
                }
             }
        }

            // --- Colisão com inimigo ---
        if (SDL_HasIntersection(&player, &enemy) && !explosionActive) {
            Mix_PlayChannel(-1, explosionSound, 0);
        
            explosionActive = true;
            explosionFrame = 0;
            explosionPos.x = enemy.x;
            explosionPos.y = enemy.y;
            explosionPos.w = 64;
            explosionPos.h = 64;

            player.x = 100;
            player.y = 500;
            score -= 5;
            if (score < 0) score = 0;
        }

        SDL_SetRenderDrawColor(ren, 135, 206, 235, 255);
        SDL_RenderClear(ren);

        // Desenhar o tile //
        
        for (int y = 0; y < MAP_HEIGHT; ++y) {
            for (int x = 0; x < MAP_WIDTH; ++x) {
                int tile_id = map_data[y][x];

                sourceRect.x = (tile_id % tileset_width_in_tiles) * tile_width;
                sourceRect.y = (tile_id / tileset_width_in_tiles) * tile_height;
                sourceRect.w = tile_width;
                sourceRect.h = tile_height;

                destRect.x = x * tile_width;
                destRect.y = y * tile_height;
                destRect.w = tile_width;
                destRect.h = tile_height;

                switch (fase) {
                    case 1:
                        SDL_RenderCopy(ren, tilemap1Tex, &sourceRect, &destRect);
                        break;
                    case 2:
                        SDL_RenderCopy(ren, tilemap2Tex, &sourceRect, &destRect);
                        break;
                    case 3:
                        SDL_RenderCopy(ren, tilemap3Tex, &sourceRect, &destRect); 
                        break;
                }


            }
        }

        SDL_RenderCopy(ren, coinTex, NULL, &coin);
        SDL_RenderCopy(ren, enemyTex, NULL, &enemy);
        SDL_RenderCopy(ren, playerTex, NULL, &player);

        // Desenhar porta se ativa
        if (portaAtiva) {
            SDL_SetRenderDrawColor(ren, 139, 69, 19, 255); // marrom
            SDL_RenderFillRect(ren, &porta);
        }

        if (explosionActive) {
            explosionRect.x = (explosionFrame % 8) * 64;
            explosionRect.y = 0;

            SDL_RenderCopy(ren, explosionTex, &explosionRect, &explosionPos);

            if (++explosionFrame > 7) {
                explosionActive = false;
            }
        }

        SDL_RenderPresent(ren);
        SDL_Delay(100); // controla a velocidade da explosão
    } 

    // --- Limpeza ---
    Mix_FreeChunk(coinSound);
    SDL_DestroyTexture(playerTex);
    SDL_DestroyTexture(enemyTex);
    SDL_DestroyTexture(coinTex);
    SDL_DestroyTexture(tilemap1Tex);//
    SDL_DestroyTexture(tilemap2Tex);//
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    for (int i = 0; i < MAX_FASES; i++) {
        if (musicas[i]) {
            Mix_FreeMusic(musicas[i]);
        }
    }
    Mix_CloseAudio();
    SDL_DestroyTexture(explosionTex);
    Mix_FreeChunk(explosionSound);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
