#include "Game.h"
#include <SDL.h>
#include <iostream>
#include "Constants.h"

//TODO tmp code for testing SDL
float posX, posY = 20.f;
float vel = 50.f;
//

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::Initialize(int windowWidth, int windowHeight)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Unable to initialize SDL, error: " << SDL_GetError();
        return false;
    }

    window = SDL_CreateWindow("Window title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, 0);
    if (!window)
    {
        std::cout << "Unable create window, error: " << SDL_GetError();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cout << "Unable create renderer, error: " << SDL_GetError();
        return false;
    }

    lastTicks = SDL_GetTicks();

    isRunning = true;

    return true;
}

bool Game::IsRunning()
{
    return isRunning;
}

void Game::PorcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            isRunning = false;
            break;
        }
    default:
        break;
    }
}

void Game::Update()
{
    ///FPS limitation
    float timeFromLastTick = (SDL_GetTicks() - lastTicks) / 1000.f;
    if (timeFromLastTick < TARGET_TIME_FOR_FAME)
    {
        SDL_Delay((TARGET_TIME_FOR_FAME - timeFromLastTick) * 1000.f);
    }

    ///Delta time
    float currentTicks = SDL_GetTicks();
    float deltaTime = (currentTicks - lastTicks) / 1000.f;
    lastTicks = currentTicks;

#if FPS_COUNTER
    fpsCounter++;
    timeSummary += deltaTime;
    if (timeSummary >= 1)
    {
        std::cout << "FPS: " << fpsCounter << std::endl;
        timeSummary = 0;
        fpsCounter = 0;
    }
#endif
    //TODO tmp code for testing SDL
    posX = posX + (vel * deltaTime);
    posY = posY + (vel * deltaTime);
    //
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    //TODO tmp code for testing SDL
    SDL_Rect projectile = {
        (int)posX,
        (int)posY,
        50,
        50,
    };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);
    //
    SDL_RenderPresent(renderer);
}
