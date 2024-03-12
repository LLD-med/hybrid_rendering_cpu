#ifndef BASEBOUNDING_H
#define BASEBOUNDING_H

#include "Vector.hpp"
#include "rayTracing/Ray.h"

class BaseBounding
{
public:
    BaseBounding() = default;
    virtual ~BaseBounding() = default;

    virtual bool checkIntersection(const Ray &ray) = 0;

protected:
    VecD _min;
    VecD _max;
};

#endif // BASEBOUNDING_H
