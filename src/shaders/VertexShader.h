#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "VertexShaderImpl.h"

class VertexShader : public VertexShaderImpl
{
public:
//    VertexShader();
    VertexShader(const VecD &color = {0.8, 0.8, 0.8},
                 const VecD &ambient = {0.3, 0.3, 0.3},
                 const double &intens = 1.) :
        _light_color(color), _ambient(ambient), _intensity(intens) {}

    virtual Vertex apply(const Vertex &a, const Transform& rotation,
                 const Transform& objToWorld, std::shared_ptr<CameraModel> cam) override;

    ~VertexShader() override{ }
protected:
    VecD _light_color;
    VecD _ambient;
    double _intensity;
};

#endif // VERTEXSHADER_H
