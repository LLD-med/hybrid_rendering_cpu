#ifndef GEOMETRYSHADERIMPL_H
#define GEOMETRYSHADERIMPL_H

#include "surfacemodel/Vertex.h"
#include "Transform.h"

class GeometryShaderImpl
{
public:
    virtual Vertex apply(const Vertex &a,
                         const Transform& projMat,
                         const Transform& viewMat) = 0;

    virtual ~GeometryShaderImpl() { }
};

#endif // GEOMETRYSHADERIMPL_H
