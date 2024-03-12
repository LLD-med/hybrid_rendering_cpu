#include "Vertex.h"

void Vertex::setPosition(const VecD &pos)
{
    _position = pos;
}

void Vertex::setNormal(const VecD &norm)
{
    _normal = norm;
}

void Vertex::setColor(const VecD &color)
{
    _color = color;
}


VecD Vertex::getPosition() const
{
    return _position;
}


VecD Vertex::getNormal() const
{
    return _normal;
}

VecD Vertex::getColor() const
{
    return _color;
}

void Vertex::setU(const double &new_u)
{
    _u = new_u;
}

void Vertex::setV(const double &new_v)
{
    _v = new_v;
}

void Vertex::setInvW(const double &new_w)
{
    _invW = new_w;
}

double Vertex::getU() const
{
    return _u;
}

double Vertex::getV() const
{
    return _v;
}

double Vertex::getInvW() const
{
    return _invW;
}

