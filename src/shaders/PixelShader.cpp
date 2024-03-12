#include "PixelShader.h"
#include "./baryFuncs/BaryFuncs.h"
#include "objects/Transform.h"

VecD PixelShader::apply(const Vertex &a, const Vertex &b,
                        const Vertex &c, const VecD &bary)
{
    auto new_color = baryCentricInterpolation(a.getColor(), b.getColor(), c.getColor(), bary);
    return new_color;
}
