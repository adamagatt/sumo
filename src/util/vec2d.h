#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

class Vec2d {
    float x;
    float y;
    
    friend std::ostream& operator<<(std::ostream &output, const Vec2d& V);

    public:
    Vec2d(float x, float y);
    float getX() const;
    float getY() const;
    void zero();

    Vec2d operator-() const;
    float abs() const;

    Vec2d operator+(const Vec2d& other) const;
    Vec2d& operator+=(const Vec2d& other);
    Vec2d operator-(const Vec2d& other);
    Vec2d& operator-=(const Vec2d& other);
    Vec2d operator*(float scale) const;
    Vec2d& operator*=(float scale);
    Vec2d operator/(float scale) const;
    Vec2d& operator/=(float scale);
};

#endif