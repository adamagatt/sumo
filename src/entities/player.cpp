#include "player.h"

const float Player::scale{0.2};
const float Player::mass{1.0};
const float Player::friction{1.25};
const float Player::diameter{20};
const float Player::speed{mass * 3};

SDL_Texture* Player::image = nullptr;

Player::Player(float x, float y): Entity(x, y) { }
Player::Player(Vec2d pos): Entity(pos) { }

void Player::loadImage(SDL_Renderer* renderer) {
    image = IMG_LoadTexture(renderer, "assets/sumo.png");
}

SDL_Texture* Player::getImage() const {
    SDL_SetTextureColorMod(image, brightness, brightness, brightness);
    return image;
}

string Player::getName() const {
    return "Player";
}

float Player::getScale() const {
    return scale;
}

float Player::getMass() const {
    return mass;
}

float Player::getFriction() const {
    return friction;
}

float Player::getDiameter() const {
    return diameter;
}

float Player::getSpeed() const {
    return speed;
}