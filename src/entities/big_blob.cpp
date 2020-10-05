#include "big_blob.h"

const float BigBlob::scale{5.5};
const float BigBlob::mass{0.9};
const float BigBlob::friction{1.035};
const float BigBlob::diameter{40};
const float BigBlob::speed{mass * 0.7};
SDL_Texture* BigBlob::image = nullptr;

BigBlob::BigBlob(float x, float y): Entity(x, y) { }
BigBlob::BigBlob(Vec2d pos): Entity(pos) { }

void BigBlob::loadImage(SDL_Renderer* renderer) {
    image = IMG_LoadTexture(renderer, "assets/big_blob.png");
}

SDL_Texture* BigBlob::getImage() const {
    SDL_SetTextureColorMod(image, brightness, brightness, brightness);
    return image;
}

string BigBlob::getName() const {
    return "BigBlob";
}

float BigBlob::getScale() const {
    return scale;
}

float BigBlob::getMass() const {
    return mass;
}

float BigBlob::getFriction() const {
    return friction;
}

float BigBlob::getDiameter() const {
    return diameter;
}

float BigBlob::getSpeed() const {
    return speed;
}