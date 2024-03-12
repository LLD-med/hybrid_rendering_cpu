#include "Ray.h"

VecD Ray::getOrigin() const
{
    return origin;
}

VecD Ray::getDirection() const
{
    return direction;
}

RayType Ray::getType() const
{
    return type;
}
