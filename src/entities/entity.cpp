#include "entity.h"

const float Entity::MAX_ANGLE_SPEED = 15.0;
const float Entity::MAX_ANGLE = 0.9;

Entity::Entity(float x, float y): position(Vec2d{x, y}), velocity(Vec2d{0, 0}),
facingRight{true}, moving{false}, heightOffset{0.0} { }

Entity::Entity(Vec2d pos): position(Vec2d{pos}), velocity(Vec2d{0, 0}),
facingRight{true}, moving{false}, heightOffset{0.0} { }

float Entity::getX() const {
    return position.getX();
}

float Entity::getY() const {
    return position.getY();
}

float Entity::getHeightOffset() const {
    return heightOffset;
}

float Entity::getRotateAngle() const {
    return MAX_ANGLE * std::max(std::min(velocity.getX(), MAX_ANGLE_SPEED), -MAX_ANGLE_SPEED);
}

void Entity::setFacingRight(bool newFacingRight) {
    facingRight = newFacingRight;
}

bool Entity::getFacingRight() const {
    return facingRight;
}

void Entity::setMoving(bool newMoving) {
    moving = newMoving;
}

bool Entity::getMoving() const {
    return moving;
}

void Entity::activate() {
    activated = true;
}

bool Entity::getActivated() {
    return activated;
}

void Entity::eliminate() {
    eliminated = true;
}

bool Entity::getEliminated() {
    return eliminated;
}

void Entity::update(const Entity* player) {
    if (eliminated) {
        brightness = max(brightness-10, 128);
    }

    if (this != player) {
        updateAI(player);
    }
    updateMotion();
}

void Entity::updateAI(const Entity* player) {
    if (!eliminated) {
        auto diff = player->getPosition() - position;
        push(diff / diff.abs() * getSpeed());
        setMoving(true);
        setFacingRight(diff.getX() > 0);
    }
}

void Entity::updateMotion() {
    position += velocity;
    velocity /= getFriction();

    if (moving) {
        heightOffset -= 1.0;
        if (heightOffset < -4.0) {
            heightOffset = 0.0;
        }
    } else {
        heightOffset = 0.0;
    }

    moving = false;
}

void Entity::push(const Vec2d& force) {
    velocity += Vec2d(force / getMass());
}

Vec2d Entity::getPosition() const {
    return position;
}

Vec2d Entity::getVelocity() const {
    return velocity;
}

void Entity::clearVelocity() {
    velocity.zero();
}

Vec2d Entity::getMomentum() const{
    return velocity * getMass();
}

float Entity::distance(const Entity& other) {
    return (other.getPosition() - position).abs();
}

bool Entity::touching(const Entity& other) {
    return distance(other) < (getDiameter() + other.getDiameter());
}

void Entity::collision(Entity& other, float pushFactor) {
    float totalMass = getMass() + other.getMass();
    float myMassShare = getMass() / totalMass;
    float otherMassShare = other.getMass() / totalMass;
    // Calculate total momentum
    // Divide between objects weighted by mass
    // Apply forces to objects
    auto momentum_me_other = getMomentum() * myMassShare;
    auto momentum_me_me = getMomentum() * otherMassShare;
    auto momentum_other_me = other.getMomentum() * otherMassShare;
    auto momentum_other_other = other.getMomentum() * myMassShare;

    clearVelocity();
    other.clearVelocity();

    push((momentum_other_me-momentum_me_me) * pushFactor);
    other.push((momentum_me_other-momentum_other_other) * pushFactor);

    // Separate if too close
    if (distance(other) < (getDiameter() + other.getDiameter())) {
        auto awayForce = (position - other.getPosition()) * 0.05;
        push(awayForce);
        other.push(-awayForce); 
    }
}