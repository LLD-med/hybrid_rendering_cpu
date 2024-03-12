#ifndef RAY_H
#define RAY_H

#include "Vector.hpp"

#define MAX_RECURSION_DEPTH 4

enum RayType
{
    primary = 0,
    secondary
};

class Ray
{
public:
    Ray(const VecD& origin_, const VecD& direction_): origin(origin_) , direction(direction_.VecNormalize())
    {
        invdirection = VecD({1 / direction.getX(), 1 / direction.getY(), 1 /direction.getZ()});
        sign[0] = (invdirection.getX() < 0);
        sign[1] = (invdirection.getY() < 0);
        sign[2] = (invdirection.getZ() < 0);
    }

    Ray(const Ray& other) : origin(other.origin), direction(other.direction.VecNormalize()) {}

    VecD getOrigin() const;
    VecD getDirection() const;
    RayType getType() const;

public:
    RayType type;
    VecD origin;
    VecD direction, invdirection;
    int sign[3];
};

#endif // RAY_H
