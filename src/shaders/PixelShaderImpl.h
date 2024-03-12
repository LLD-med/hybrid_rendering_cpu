#ifndef PIXELSHADERIMPL_H
#define PIXELSHADERIMPL_H

#include "surfacemodel/Vertex.h"

class PixelShaderImpl
{
public:
    virtual VecD apply(const Vertex &a, const Vertex &b,
                       const Vertex &c, const VecD &bary) = 0;

    virtual ~PixelShaderImpl() { }
};

#endif // PIXELSHADERIMPL_H
