#include "LightCommand.h"
#include <QDebug>

void LightCommand::setAdapter()
{
    auto adapter = std::make_shared<LightAdapter>();
    _transformManager->setAdapter(adapter);
}

AddLight::AddLight(const ID &id, const VecD &location, const VecD &direction, lightType type) :
     _id(id), _type(type), _location(location), _direction(direction) {
    _method = &LightsManager::addLight;
}

void AddLight::execute()
{
    (*_id) = ((*_lightsManager).*_method)(_location, _direction, _type);
}

RemoveLight::RemoveLight(const std::size_t id) : _id(id)
{
    _method = &LightsManager::deleteLight;
}

void RemoveLight::execute()
{
    ((*_lightsManager).*_method)(_id);
}

SetLight::SetLight(const std::size_t id) : _id(id)
{
    _method = &LightsManager::setLight;
}

void SetLight::execute()
{
    ((*_lightsManager).*_method)(_id);
}

GetLight::GetLight(std::shared_ptr<Light> &light) : _light(light)
{
    _method = &LightsManager::getLight;
}

void GetLight::execute()
{
    ((*_lightsManager).*_method)();
}


GetLightByInd::GetLightByInd(std::shared_ptr<Light> &light, const std::size_t id) : _light(light), _id(id)
{
    _method = &LightsManager::getLightById;
}

void GetLightByInd::execute()
{
    _light = ((*_lightsManager).*_method)(_id);
}


TransformLight::TransformLight(const std::shared_ptr<Light> light, const double dx, const double dy, const double dz, const double ox, const double oy) :
    _light(light), _dx(dx), _dy(dy), _dz(dz), _ox(ox), _oy(oy)
{
    _method = &TransformManager::multipleTransform;
}

void TransformLight::execute()
{
    ((*_transformManager).*_method)(_light, _dx, _dy, _dz, _ox, _oy);
}


