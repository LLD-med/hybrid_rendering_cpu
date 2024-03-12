#include "Face.h"

Face::Face(Vertex &v1, Vertex &v2, Vertex &v3)
{
    _a = v1;
    _b = v2;
    _c = v3;

    _normal = (_b.getPosition() - _a.getPosition()).VectorProd(_c.getPosition() - _a.getPosition());
}

void Face::setA(Vertex &a)
{
    _a = a;
}

void Face::setB(Vertex &b)
{
    _b = b;
}

void Face::setC(Vertex &c)
{
    _c = c;
}

void Face::setNormal(VecD &norm)
{
    _normal = norm;
}

void Face::setNormal(VecD norm)
{
    _normal = norm;
}

void Face::setColorA(const VecD &color)
{
    _a.setColor(color);
}

void Face::setColorB(const VecD &color)
{
    _b.setColor(color);
}

void Face::setColorC(const VecD &color)
{
    _c.setColor(color);
}

Vertex Face::getA() const
{
    return _a;
}

Vertex Face::getB() const
{
    return _b;
}

Vertex Face::getC() const
{
    return _c;
}

VecD Face::getNormal() const
{
    return _normal;
}
