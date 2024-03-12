#include "TextureShader.h"
#include "baryFuncs/BaryFuncs.h"
#include <QDebug>
#include "Vector.hpp"

#define EPS 1e-6

TextureShader::TextureShader(const QImage &texture)
{
    _texture = texture;
}

VecD TextureShader::apply(const Vertex &a, const Vertex &b,
                          const Vertex &c, const VecD &bary)
{
    float pixelZ = interpolateCoord(a.getInvW(), b.getInvW(), c.getInvW(), bary);
//    if (pixel_z < EPS)
//        qDebug << "TextureShader error" << std::endl;
    float invZ = 1 / pixelZ;

    auto faceColor = baryCentricInterpolation(a.getColor(), b.getColor(), c.getColor(), bary);
    float pixelU = interpolateCoord(a.getU(), b.getU(), c.getU(), bary) * invZ;
    float pixelV = interpolateCoord(a.getV(), b.getV(), c.getV(), bary) * invZ;

    int x = std::floor(pixelU * (_texture.width() - 1));
    int y = std::floor(pixelV * (_texture.height() - 1));

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    auto color = _texture.pixelColor(x, y);
    auto red = color.red();
    auto green = color.green();
    auto blue = color.blue();

    VecD pixelColor = VecD{ red / 255.f, green / 255.f, blue / 255.f };

    auto res = pixelColor.HadamardProd(faceColor).VecSaturate();

    return res;
}
