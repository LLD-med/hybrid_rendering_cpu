#include "IntersectionData.h"

void IntersectionData::setPosition(VecD &pos)
{
    _position = pos;
}

void IntersectionData::setNormal(VecD &norm)
{
    _normal = norm;
}

void IntersectionData::setColor(VecD &color)
{
    _color = color;
}

void IntersectionData::setPosition(VecD pos)
{
    _position = pos;
}

void IntersectionData::setNormal(VecD norm)
{
    _normal = norm;
}

void IntersectionData::setColor(VecD color)
{
    _color = color;
}

void IntersectionData::setT(double value)
{
    t_coef = value;
}

VecD IntersectionData::getPosition() const
{
    return _position;
}

VecD IntersectionData::getNormal() const
{
    return _normal;
}

VecD IntersectionData::getColor() const
{
    return _color;
}

VecD IntersectionData::getProperties() const
{
    return _properties;
}

double IntersectionData::getProperty(int type) const
{
    return _properties.getItem(type);
}

double IntersectionData::getT() const
{
    return t_coef;
}
