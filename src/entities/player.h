#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
    const static string name;
    const static float scale;
    const static float mass;
    const static float friction;
    const static float diameter;
    const static float speed;

    static SDL_Texture *image;

    public:
    Player(float x, float y);
    Player(Vec2d pos);
    static void loadImage(SDL_Renderer* renderer);
    SDL_Texture* getImage() const;
    string getName() const;
    float getScale() const;
    float getMass() const;
    float getFriction() const;
    float getDiameter() const;
    float getSpeed() const;
};

#endif