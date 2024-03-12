#ifndef LIGHTIMPL_H
#define LIGHTIMPL_H

#include "Vector.hpp"

enum lightType
{
    ambient,
    point,
    directional
};

class LightImpl
{
public:
    LightImpl() = default;
    LightImpl(const VecD &location, const VecD &direction, lightType type) : _type(type), _location(location), _direction(direction) { }
    ~LightImpl() = default;

    VecD getLocation() const;
    VecD getDirection() const;
    VecD getIntensity() const;
    VecD getColor() const;
    lightType getType() const;

    void setLocation(const VecD &location) { _location = location; }
    void setDirection(const VecD &direction) { _direction = direction; }
    void setType(const lightType type) { _type = type; }
    void setIntensity(const VecD &intens) { _intens = intens; }
    void setColor(const VecD &color) { _color = color; }

private:
    lightType _type;
    VecD _color;

    VecD _intens;
    VecD _location;
    VecD _direction;
};

#endif // LIGHTIMPL_H
