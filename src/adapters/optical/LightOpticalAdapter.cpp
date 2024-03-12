#include "LightOpticalAdapter.h"

void LightOpticalAdapter::setAdaptee(std::shared_ptr<BaseObject> adaptee)
{
    _adaptee = dynamic_pointer_cast<Light>(adaptee);
}

void LightOpticalAdapter::request()
{
    if (_adaptee)
    {
        if (! _coeffs.isEmpty())
        {
            auto light = _adaptee->_light;
            light->setIntensity(_coeffs);
        }
        if (! _color.isEmpty())
        {
            auto light = _adaptee->_light;
            light->setColor(_color);
        }
    }
}
