#ifndef PIXELSHADER_H
#define PIXELSHADER_H

#include "PixelShaderImpl.h"

class PixelShader : public PixelShaderImpl
{
public:
//    PixelShader() = default;
    virtual VecD apply(const Vertex &a, const Vertex &b,
                       const Vertex &c, const VecD &bary) override;

    ~PixelShader() override { }
};

#endif // PIXELSHADER_H
