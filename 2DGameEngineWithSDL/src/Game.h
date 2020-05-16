#pragma once
#include <SDL.h>

///Prints fps count in console
#define FPS_COUNTER 0

class Game
{
private:
    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Uint32 lastTicks = 0;

#if FPS_COUNTER
    int fpsCounter = 0;
    float timeSummary = 0;
#endif

public:
    Game() {};
    ~Game();
    bool Initialize(int windowWidth, int windowHeight);
    bool IsRunning();
    void PorcessInput();
    void Update();
    void Render();
};

