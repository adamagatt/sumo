#ifndef SUMO_GAME_H
#define SUMO_GAME_H

#include <SDL2/SDL.h> 

#include <vector>

#include "entities/player.h"
#include "entities/entity.h"

class SumoGame {
 public:
    void init();
    ~SumoGame();

 private:
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 600;
    const static int PAD_WIDTH = 320;
    const static int PAD_HEIGHT = 200;
    const float BACKGROUND_SCALE = 0.6;
    constexpr static float TICK_TIME_MS = 33.33;
    float PUSH_FACTOR = TICK_TIME_MS * 0.02;
    constexpr static int RAND_FRAMES_BEGIN = (int)(1000 / TICK_TIME_MS);
    static int randFramesEnd;

    int timeToSpawn = 8000/TICK_TIME_MS;

    // SDL Components
    SDL_Window *window;
    SDL_Renderer* renderer;
    SDL_Rect texr;
    const Uint8* keystate;

    // Game entities
    vector<Entity*> entities;
    Player* player;

    // Method prototypes
    void drawScene(SDL_Renderer* renderer);
    bool playerInput(Player* player);
    void entityTick(Player* player);
    void checkEliminated(Entity* entity);
    int randRange(int min, int max);
    Vec2d randStartPos();
    void initialise();
};

#endif