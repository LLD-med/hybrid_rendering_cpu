#include "LightImpl.h"

VecD LightImpl::getLocation() const
{
    return _location;
}

VecD LightImpl::getDirection() const
{
    return _direction.VecNormalize();
}

VecD LightImpl::getIntensity() const
{
    return _intens;
}

lightType LightImpl::getType() const
{
    return _type;
}
