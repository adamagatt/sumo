#ifndef ENTITY_H
#define ENTITY_H

#include "../util/vec2d.h"
#include <string>
#include <SDL2/SDL_image.h>

using namespace std;

class Entity {
    protected:
    int brightness{255};
    bool eliminated{false};
    bool activated{false};    

    private:
    // All entities
    const static float MAX_ANGLE_SPEED;
    const static float MAX_ANGLE;

    // Per object
    Vec2d position;
    Vec2d velocity{0, 0};
    double health;
    bool facingRight{true};
    bool moving{false};
    float heightOffset{0.0};

    void updateAI(const Entity* player);
    void updateMotion();

    public:
    Entity(float x, float y);
    Entity(Vec2d pos);

    virtual string getName() const =0;
    virtual SDL_Texture* getImage() const=0;
    virtual float getScale() const =0;
    virtual float getMass() const =0;
    virtual float getFriction() const =0;
    virtual float getDiameter() const =0;
    virtual float getSpeed() const=0;

    float getX() const;
    float getY() const;

    Vec2d getPosition() const;
    Vec2d getVelocity() const;
    void clearVelocity();
    Vec2d getMomentum() const;

    float getRotateAngle() const;
    void setFacingRight(bool newFacingRight);
    bool getFacingRight() const;
    void setMoving(bool newMoving);
    bool getMoving() const;
    float getHeightOffset() const;
    float distance(const Entity& other);
    bool touching(const Entity& other);
    void collision(Entity& other, float pushFactor);

    void update(const Entity* player);
    void push(const Vec2d& force);
    void activate();
    bool getActivated();
    void eliminate();
    bool getEliminated();
    void render();
};

#endif