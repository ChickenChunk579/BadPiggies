#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "spdlog/spdlog.h"
#if defined(__APPLE__)
#include <_locale.h>
#endif

const Uint32 fps = 60;
const Uint32 minframetime = 1000 / fps;

static int frameCount = 0;
static Uint32 lastTime = 0;

int main() {
    spdlog::info("Bad Piggies v1.0");
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Renderer* renderer = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        spdlog::error("Failed to initialize SDL");
        return 1;
    }
    spdlog::info("Initialized SDL");
    window = SDL_CreateWindow(
        "Bad Piggies",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 720,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        spdlog::error("Failed to create window");
        return 1; 
    }

    spdlog::info("Created window");

    renderer = SDL_CreateRenderer(window, 0, 0);

    bool running = true;
    SDL_Event event;
    uint32_t frametime;
    while (running) {
        frametime = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);

        frameCount++;
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastTime >= 1000) {
            int fps = frameCount * 1000 / (currentTime - lastTime);
            char title[256];
            #if defined(__APPLE__)
            #else
            sprintf_s(title, "Bad Piggies - FPS: %d", fps);
            SDL_SetWindowTitle(window, title);
            #endif
            lastTime = currentTime;
            frameCount = 0;
        }

        if (SDL_GetTicks() - frametime < minframetime) {
            SDL_Delay(minframetime - (SDL_GetTicks() - frametime));
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
}