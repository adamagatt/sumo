#include "blob.h"

const float Blob::scale{4.0};
const float Blob::mass{0.65};
const float Blob::friction{1.05};
const float Blob::diameter{20};
const float Blob::speed{mass * 0.3};

SDL_Texture* Blob::image = nullptr;

Blob::Blob(float x, float y): Entity(x, y) { }
Blob::Blob(Vec2d pos): Entity(pos) { }

void Blob::loadImage(SDL_Renderer* renderer) {
    image = IMG_LoadTexture(renderer, "assets/blob.png");
}

SDL_Texture* Blob::getImage() const {
    SDL_SetTextureColorMod(image, brightness, brightness, brightness);
    return image;
}

string Blob::getName() const {
    return "Blob";
}

float Blob::getScale() const {
    return scale;
}

float Blob::getMass() const {
    return mass;
}

float Blob::getFriction() const {
    return friction;
}

float Blob::getDiameter() const {
    return diameter;
}

float Blob::getSpeed() const {
    return speed;
}