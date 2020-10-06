#ifndef BLOB_H
#define BLOB_H

#include "entity.h"

class Blob : public Entity {
    const static string name;
    const static float scale;
    const static float mass;
    const static float friction;
    const static float diameter;
    const static float speed;

    static SDL_Texture *image;

    public:
    Blob(float x, float y);
    Blob(Vec2d pos);
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