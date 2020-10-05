#include <cmath>
#include <iostream>
#include "vec2d.h"

Vec2d::Vec2d(float x, float y) : x(x), y(y) { }
float Vec2d::getX() const {
    return x;
}

float Vec2d::getY() const {
    return y;
}

void Vec2d::zero() {
    x = 0;
    y = 0;
}

Vec2d Vec2d::operator-() const {
    return Vec2d{-x, -y};
}

float Vec2d::abs() const {
    return sqrt(x*x + y*y);
}

Vec2d Vec2d::operator+(const Vec2d& other) const {
    return Vec2d{x+other.getX(), y+other.getY()};
}

Vec2d& Vec2d::operator+=(const Vec2d& other) {
    this->x += other.getX();
    this->y += other.getY();
    return *this;
}

Vec2d Vec2d::operator-(const Vec2d& other) {
    return *this + (-other);
}

Vec2d& Vec2d::operator-=(const Vec2d& other) {
    return *this += Vec2d{-other.getX(), -other.getY()};
}

Vec2d Vec2d::operator*(float scale) const {
    return Vec2d{this->x * scale, this->y * scale};
}

Vec2d& Vec2d::operator*=(float scale) {
    this->x *= scale;
    this->y *= scale;
    return *this;
}

Vec2d Vec2d::operator/(float scale) const {
    return *this * (1.0 / scale);
}

Vec2d& Vec2d::operator/=(float scale) {
    return *this *= (1.0 / scale);
}

std::ostream& operator<<(std::ostream& output, const Vec2d& v) { 
    output << "[" << v.x << ", " << v.y << "]";
    return output;            
}

bool operator==(const Vec2d& lhs, const Vec2d& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}