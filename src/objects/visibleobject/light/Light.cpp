#include "Light.h"

Light::Light()
{
    _light = std::make_shared<LightImpl>();
}

Light::Light(const Light &light)
{
    _light = light._light;
    _id = light._id;
}

Light::Light(const VecD &location, const VecD &direction, lightType type)
{
    _light = std::make_shared<LightImpl>(location, direction, type);
}

VecD Light::getCenter() const
{
    return _light->getLocation();
}

lightType Light::getType() const
{
    return _light->getType();
}

Light::~Light() { }
