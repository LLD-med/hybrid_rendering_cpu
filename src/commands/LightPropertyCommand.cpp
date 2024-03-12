#include "LightPropertyCommand.h"

void LightPropertyCommand::setAdapter()
{
    auto adapter = std::make_shared<LightOpticalAdapter>();
    _propertyManager->setAdapter(adapter);
}


ChangeLightColor::ChangeLightColor(const std::shared_ptr<Light> light, const double cx, const double cy, const double cz) :
    _light(light), _cx(cx), _cy(cy), _cz(cz)
{
    _method = &PropertyManager::changeColor;
}

void ChangeLightColor::execute()
{
    ((*_propertyManager).*_method)(_light, _cx, _cy, _cz);
}


ChangeLightIntensity::ChangeLightIntensity(const std::shared_ptr<Light> light, const double px, const double py, const double pz) :
    _light(light), _px(px), _py(py), _pz(pz)
{
    _method = &PropertyManager::changeProperties;
}

void ChangeLightIntensity::execute()
{
    ((*_propertyManager).*_method)(_light, _px, _py, _pz);
}
