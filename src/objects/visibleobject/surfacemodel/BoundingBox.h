#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "BaseBounding.h"
#include <vector>
#include "Vertex.h"

class BoundingBox : public BaseBounding
{
public:
    BoundingBox() = default;
    BoundingBox(const VecD& min_, const VecD& max_)
    {
        bounds[0] = min_;
        bounds[1] = max_;
    }
    ~BoundingBox() = default;

    virtual bool checkIntersection(const Ray &ray) override;

    void createBoundingBox(const std::vector<Vertex> &vertices);

private:
//    VecD max, min;
    VecD bounds[2];
};

#endif // BOUNDINGBOX_H
