#ifndef VEC2D_H
#define VEC2D_H

#include <iostream>

class Vec2d {
    // The x-component for the vector
    float x;
    // The y-component for the vector
    float y;
    
    /**
     * @brief Write a vector to an output stream.
     * 
     * @param output The output stream to write to.
     * @param V The vector to write.
     * @return std::ostream& A reference to the output stream after writing.
     */
    friend std::ostream& operator<<(std::ostream &output, const Vec2d& V);

    /**
     * @brief Compare whether two vectors are equal, based on comparing each of their
     * components.
     * 
     * @param lhs The first vector to compare
     * @param rhs The second vector to compare
     * @return true if the two vectors are equivalent, otherwise false
     */
    friend bool operator==(const Vec2d& lhs, const Vec2d& rhs);


    public:
    /**
     * @brief Construct a new vector object
     * 
     * @param x The x-component to use for the new vector.
     * @param y The y-component to use for the new vector.
     */
    Vec2d(float x, float y);

    /**
     * @brief Return the x-component of this vector.
     * 
     * @return float The x-component of this vector.
     */
    float getX() const;

    /**
     * @brief Return the y-component of this vector.
     * 
     * @return float The y-component of this vector.
     */    
    float getY() const;

    /**
     * @brief Set all components of the vector to zero.
     */
    void zero();

    /**
     * @brief Unary negation of the vector.
     * 
     * @return Vec2d A new vector with the same magnitude but opposite direction.
     */
    Vec2d operator-() const;

    /**
     * @brief Calculate the (l2-norm) magnitude of the vector.
     * 
     * @return float The magnitude of the vector.
     */
    float abs() const;

    /**
     * @brief Return the result of adding this vector to another.
     * 
     * @param other The vector to add to this one.
     * @return Vec2d A new vector for the results of the addition.
     */
    Vec2d operator+(const Vec2d& other) const;

    /**
     * @brief Add another vector to this one, mutating it in-place.
     * 
     * @param other The vector to add to this one.
     * @return Vec2d& A reference to this vector after the addition is performed.
     */
    Vec2d& operator+=(const Vec2d& other);

    /**
     * @brief Return the result of subtracting another vector from this one.
     * 
     * @param other The vector to subtract from this one.
     * @return Vec2d A new vector for the results of the subtraction.
     */
    Vec2d operator-(const Vec2d& other);

    /**
     * @brief Subtract another vector from this one, mutating it in-place.
     * 
     * @param other The vector to subtract from this one.
     * @return Vec2d& A reference to this vector after the subtraction is performed.
     */
    Vec2d& operator-=(const Vec2d& other);

    /**
     * @brief Return the result of scaling this vector by a given scalar.
     * 
     * @param scale The scaling factor to use for the operation.
     * @return Vec2d A new vector for the results of the scaling.
     */
    Vec2d operator*(float scale) const;

    /**
     * @brief Scale this vector in-place by a giving scaling factor.
     * 
     * @param scale The scaling factor to use for the operation.
     * @return Vec2d& A reference to this vector after the scaling is performed.
     */
    Vec2d& operator*=(float scale);

    /**
     * @brief Inverse-scaling of this vector. The result returned will have all components
     * divided by the provided scaling factor.
     * 
     * @param scale The factor to use for the operation.
     * @return Vec2d A new vector for the results of the scaling.
     */
    Vec2d operator/(float scale) const;

    /**
     * @brief In-place inverse scaling of this vector by a giving scaling factor.
     * 
     * @param scale The scaling factor to use for the operation.
     * @return Vec2d& A reference to this vector after the inverse scaling is performed.
     */
    Vec2d& operator/=(float scale);
};

#endif