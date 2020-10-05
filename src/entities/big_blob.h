#ifndef BIG_BLOB_H
#define BIG_BLOB_H

#include "entity.h"
#include "../util/vec2d.h"

class BigBlob : public Entity {
    const static string name;
    const static float scale;
    const static float mass;
    const static float friction;
    const static float diameter;
    const static float speed;

    static SDL_Texture *image;

    public:
    BigBlob(float x, float y);
    BigBlob(Vec2d pos);
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