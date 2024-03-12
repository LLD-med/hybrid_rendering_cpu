#ifndef GEOMETRYSHADER_H
#define GEOMETRYSHADER_H

#include "GeometryShaderImpl.h"

class GeometryShader : public GeometryShaderImpl
{
public:
//    GeometryShader() = default;
    virtual Vertex apply(const Vertex &a,
                         const Transform& projMat,
                         const Transform& viewMat) override;

    ~GeometryShader() override { };
};

#endif // GEOMETRYSHADER_H
