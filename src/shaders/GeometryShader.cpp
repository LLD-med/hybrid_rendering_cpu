#include "GeometryShader.h"
#include "Vector.hpp"
#include "Transform.h"

#define EPS 1e-6

Vertex GeometryShader::apply(const Vertex &a, const Transform& projMat,
                             const Transform& viewMat)
{
    VecD pos = a.getPosition();
    VecD new_pos(VecD{ pos.getX(), pos.getY(), pos.getZ(), 1 });
    new_pos = new_pos * viewMat; //  вектор на матрицу
//    new_pos = viewMat.VectorByTransform(new_pos); //  вектор на матрицу
//    new_pos = (new_pos ^ viewMat); //  вектор на матрицу
    new_pos = new_pos * projMat;
//    new_pos = projMat.VectorByTransform(new_pos);
//    new_pos = (new_pos ^ projMat);

    Vertex res = a;
    res.setPosition(VecD{new_pos.getX(), new_pos.getY(), new_pos.getZ()});

    if (fabs(new_pos.getW()) < EPS)
        new_pos.setW(1);
    res.setInvW(1 / new_pos.getW());
    res.setU(res.getU() * res.getInvW());
    res.setV(res.getV() * res.getInvW());

    return res;
}
