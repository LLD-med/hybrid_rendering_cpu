#ifndef VERTEXSHADERIMPL_H
#define VERTEXSHADERIMPL_H

#include "surfacemodel/Vertex.h"
#include "objects/invisibleobject/CameraModel.h"
#include "Transform.h"

class VertexShaderImpl
{
public:
    virtual Vertex apply(const Vertex &a, const Transform& rotation,
                         const Transform& objToWorld, std::shared_ptr<CameraModel> cam) = 0;

    virtual ~VertexShaderImpl() { }
};

#endif // VERTEXSHADERIMPL_H
