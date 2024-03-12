#include "BoundingBox.h"

#define SIGN(x) (((x) < 0) ? -1 : 1)

bool BoundingBox::checkIntersection(const Ray &r)
{
    float txmin, txmax, tymin, tymax, tzmin, tzmax;

    txmin = (bounds[r.sign[0]].getX() - r.origin.getX()) * r.invdirection.getX();
    txmax = (bounds[1-r.sign[0]].getX() - r.origin.getX()) * r.invdirection.getX();

    tymin = (bounds[r.sign[1]].getY() - r.origin.getY()) * r.invdirection.getY();
    tymax = (bounds[1-r.sign[1]].getY() - r.origin.getY()) * r.invdirection.getY();

    tzmin = (bounds[r.sign[2]].getZ() - r.origin.getZ()) * r.invdirection.getZ();
    tzmax = (bounds[1-r.sign[2]].getZ() - r.origin.getZ()) * r.invdirection.getZ();

    if ((txmin > tymax) || (tymin > txmax))
        return false;
    if (tymin > txmin)
        txmin = tymin;
    if (tymax < txmax)
        txmax = tymax;

    if ((txmin > tzmax) || (tzmin > txmax))
        return false;
    if (tzmin > txmin)
        txmin = tzmin;
    if (tzmax < txmax)
        txmax = tzmax;

    return (SIGN(txmin) == SIGN(txmax));
}

void BoundingBox::createBoundingBox(const std::vector<Vertex> &vertices)
{
    float inf = std::numeric_limits<float>::infinity();
    VecD min = {inf, inf, inf};
    VecD max = {-inf, -inf, -inf};

    for (auto &cur_vertex: vertices)
    {
        VecD tmp(cur_vertex.getPosition());
        auto tmp_x = tmp.getX();
        auto tmp_y = tmp.getY();
        auto tmp_z = tmp.getZ();

//        tmp = tmp * objToWorld(); ????
        if (tmp_x < min.getX())
            min.setX(tmp_x);
        if (tmp_y < min.getY())
            min.setY(tmp_y);
        if (tmp_z < min.getZ())
            min.setZ(tmp_z);

        if (tmp_x > max.getX())
            max.setX(tmp_x);
        if (tmp_y > max.getY())
            max.setY(tmp_y);
        if (tmp_z > max.getZ())
            max.setZ(tmp_z);
    }
}
