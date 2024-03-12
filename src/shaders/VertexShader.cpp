#include "VertexShader.h"
#include "Vector.hpp"
#include "Transform.h"
#include <QImage>

Vertex VertexShader::apply(const Vertex &a, const Transform& rotation,
                           const Transform& objToWorld, std::shared_ptr<CameraModel> cam)
{
    VecD pos = a.getPosition();
    VecD new_pos({ pos.getX(), pos.getY(), pos.getZ(), 1 });

//    new_pos = objToWorld.VectorByTransform(new_pos); //  вектор на матрицу
    new_pos =  new_pos * objToWorld; //  вектор на матрицу
    Vertex res = a;
    res.setPosition(VecD{new_pos.getX(), new_pos.getY(), new_pos.getZ()});

    VecD a_norm = a.getNormal();
    VecD normal({ a_norm.getX(), a_norm.getY(), a_norm.getZ(), 1 });

    normal = normal * rotation;

    VecD normal3D = VecD{normal.getX(), normal.getY(), normal.getZ()};
    res.setNormal(normal3D.VecNormalize());

    VecD tmp_vec = res.getNormal().VecNormalize();
    double tmp = tmp_vec.ScalarProd(-cam->getDirection().VecNormalize());
    auto diffuse = _light_color;
    diffuse *= std::max(0., tmp);
    diffuse *= _intensity;

    auto new_color = (diffuse + _ambient).VecSaturate();
    res.setColor(res.getColor().HadamardProd(new_color).VecSaturate());
    return res;
}
