#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL_image.h>

#include "../util/vec2d.h"

using namespace std;

class Entity {
    protected:
    //! Brightness for displaying the entity's sprite
    int brightness{255};
    //!  If the entity has been eliminated from play
    bool eliminated{false};
    //! If the entity has started play (by entering the ring)
    bool activated{false};    

    private:
    /* All entities */
    //! Speed to scale to the maximum tilt angle
    const static float MAX_ANGLE_SPEED;
    //! Maximum tilt angle to apply to the entity's sprite
    const static float MAX_ANGLE;

    /* Per object */
    Vec2d position;
    Vec2d velocity{0, 0};
    double health;
    bool facingRight{true};
    bool moving{false};
    // Offset for displaying the sprite "off the ground" by adjusting its y position
    float heightOffset{0.0};

    /**
     * @brief Run the entity's AI code for one tick
     * 
     * @param player A reference to which entity is the Player, so that this
     * entity can tell whether it is actually the player or not.
     */
    void updateAI(const Entity* player);

    /**
     * @brief Update the object's physics for one tick
     * 
     */
    void updateMotion();

    public:
    /**
     * @brief Construct a new Entity object at the provided location
     * 
     * @param x The x-coordinate for the new object
     * @param y The y-coordinate for the new object
     */
    Entity(float x, float y);

    /**
     * @brief Construct a new Entity object with its location provided as a vector
     * 
     * @param pos A vector with the location for the new entity
     */
    Entity(Vec2d pos);

    /**
     * @brief Get the entity's name
     * 
     * @return string The name of the entity
     */
    virtual string getName() const =0;
    /**
     * @brief Get the entity's image as an SDL texture
     * 
     * @return SDL_Texture* A pointer to the SDL texture of the current entity
     */
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