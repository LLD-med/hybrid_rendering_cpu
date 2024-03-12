#ifndef TEXTURESHADER_H
#define TEXTURESHADER_H

#include "PixelShaderImpl.h"
#include <QImage>
#include "Vector.hpp"
#include "Vertex.h"

class TextureShader : public PixelShaderImpl
{
public:
    TextureShader(const QImage &texture);
    virtual VecD apply(const Vertex &a, const Vertex &b,
                       const Vertex &c, const VecD &bary) override;
    virtual ~TextureShader(){}
private:
    QImage _texture;
};

#endif // TEXTURESHADER_H
