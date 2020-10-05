#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <algorithm> 
#include <iostream>
#include <vector>
#include <random>

#include "entities/entity.h"
#include "entities/blob.h"
#include "entities/big_blob.h"
#include "entities/player.h"
#include "util/vec2d.h"

using namespace std;

class MainComponent
{
 public:
    void init();
    ~MainComponent();

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

    vector<Entity*> entities;

    SDL_Window *window;
    SDL_Renderer* renderer;
    SDL_Rect texr;
    const Uint8* keystate;

    Player* player;

    void drawScene(SDL_Renderer* renderer);
    bool playerInput(Player* player);
    void entityTick(Player* player);
    void checkEliminated(Entity* entity);
    int randRange(int min, int max);
    Vec2d randStartPos();
    void initialise();
};

int MainComponent::randFramesEnd = 0;

void MainComponent::initialise() {
    for (auto e: entities) {
        delete e;
    }
    entities.clear();

    timeToSpawn = 8000/TICK_TIME_MS;
    randFramesEnd = (int)(5000 / TICK_TIME_MS);

    player = new Player{SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/2.0f};
    entities.push_back(player);   
    entities.push_back(new Blob{SCREEN_WIDTH*3.0f/4.0f, SCREEN_HEIGHT/2.0f});
}

MainComponent::~MainComponent()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void MainComponent::init() {
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("My Game Window", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(window == nullptr) {
        cout << "Error could not create window" << SDL_GetError() << endl;
    }
    
    Player::loadImage(renderer);
    Blob::loadImage(renderer);
    BigBlob::loadImage(renderer);

    initialise();

    keystate = SDL_GetKeyboardState(NULL);
    while (1) {
        if (playerInput(player)) {
            break;
        }

        entityTick(player);
        drawScene(renderer);
        SDL_Delay(TICK_TIME_MS);

        if (timeToSpawn-- <= 0) {
            timeToSpawn = randRange(RAND_FRAMES_BEGIN, randFramesEnd);
            randFramesEnd -= (int)(80/TICK_TIME_MS);
            int xPos, yPos;
            if (randRange(0, 5) == 0) {
                entities.push_back(new BigBlob(randStartPos()));
            } else {
                entities.push_back(new Blob(randStartPos()));
            }
        }
	}
}

bool MainComponent::playerInput(Player* player) {
    SDL_PumpEvents();
    if (keystate[SDL_SCANCODE_ESCAPE]) {
        SDL_Quit();
        return true;
    } else if (keystate[SDL_SCANCODE_R]) {
        initialise();
    } else {
        if (!player->getEliminated()) {
            auto offset = Vec2d{0, 0};
            if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_I]) {
                offset += Vec2d{0, -player->getSpeed()};
                player->setMoving(true);
            } else if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_K]) {
                offset += Vec2d{0, +player->getSpeed()};
                player->setMoving(true);
            }
            if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_J]) {
                offset += Vec2d{-player->getSpeed(), 0};
                player->setFacingRight(false);
                player->setMoving(true);
            } else if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_L]) {
                offset += Vec2d{+player->getSpeed(), 0};
                player->setFacingRight(true);
                player->setMoving(true);
            }
            player->push(offset);
        }
    }
    return false;
}

void MainComponent::entityTick(Player* player) {
    for(auto e1 = entities.begin(); e1 != entities.end() - 1; ++e1) {
        for(auto e2 = std::next(e1); e2 != entities.end(); ++e2) {
            if ((*e1)->touching(**e2)) {
                (*e1)->collision(**e2, PUSH_FACTOR);
            }
        }
    }

    for (auto e : entities) {
        e->update(player);
        checkEliminated(e);
    }
}

void MainComponent::drawScene(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, 240, 245 ,255, 255);
        SDL_RenderClear(renderer);
        filledEllipseRGBA(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2,
            PAD_WIDTH, PAD_HEIGHT,
            180, 210, 230, 255
        );
        filledEllipseRGBA(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2,
            PAD_WIDTH-15, PAD_HEIGHT-9,
            220, 240, 250, 255
        );
        ellipseRGBA(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2,
            PAD_WIDTH, PAD_HEIGHT,
            0, 0, 0, 255
        );
        ellipseRGBA(renderer, SCREEN_WIDTH/2, SCREEN_HEIGHT/2,
            PAD_WIDTH-15, PAD_HEIGHT-9,
            0, 0, 0, 255
        );

        sort(entities.begin(), entities.end(),
            [](const Entity* a, const Entity* b) -> bool {
                return a->getY() < b->getY();
            }
        );

        int w, h;
        for (auto e : entities) {
	        SDL_QueryTexture(e->getImage(), NULL, NULL, &w, &h);
            float scaleFactor = BACKGROUND_SCALE + (1.0 - BACKGROUND_SCALE) * e->getY() / SCREEN_HEIGHT;
            float apparentScale = e->getScale() * scaleFactor;
            texr.w = w*apparentScale;
            texr.h = h*apparentScale;
            texr.x = e->getX() - texr.w/2;
            texr.y = e->getY() + e->getHeightOffset() - texr.h;
            SDL_RenderCopyEx(renderer, e->getImage(), NULL, &texr, e->getRotateAngle(), NULL, (e->getFacingRight() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL));
        }
        SDL_RenderPresent(renderer);
}

void MainComponent::checkEliminated(Entity* entity) {
    constexpr int PAD_WIDTH_SQUARE = PAD_WIDTH * PAD_WIDTH;
    constexpr int PAD_HEIGHT_SQUARE = PAD_HEIGHT * PAD_HEIGHT;
    constexpr long COMPARE_VALUE = (long)PAD_WIDTH_SQUARE * PAD_HEIGHT_SQUARE;
    float yDiff = abs(entity->getY() - (SCREEN_HEIGHT >> 1));
    float xDiff = abs(entity->getX() - (SCREEN_WIDTH >> 1));
    float ellipseDist = (
        yDiff * yDiff * PAD_WIDTH_SQUARE
        + xDiff * xDiff * PAD_HEIGHT_SQUARE
    );
    if (ellipseDist > COMPARE_VALUE && entity->getActivated()) {
        entity->eliminate();
    } else if (ellipseDist < COMPARE_VALUE && !entity->getActivated()) {
        entity->activate();
    }
}

int MainComponent::randRange(int min, int max) {
    return (int)((float)rand() / RAND_MAX * (max-min))+min;
}

Vec2d MainComponent::randStartPos() {
    if (rand() < (RAND_MAX >> 1)) {
        return Vec2d(
            (rand() < (RAND_MAX >> 1)) ? 0 : SCREEN_WIDTH,
            randRange(0, SCREEN_HEIGHT)
        );
    } else {
        return Vec2d(
            randRange(0, SCREEN_WIDTH),
            (rand() < (RAND_MAX >> 1)) ? 0 : SCREEN_HEIGHT
        );
    }
}

int main(int argc, const char * argv[]) {

    MainComponent mainComponent;
    mainComponent.init();

    return 0;
}