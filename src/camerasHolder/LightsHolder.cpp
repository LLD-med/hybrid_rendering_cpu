#include "LightsHolder.h"
#include "Light.h"

LightsHolder::LightsHolder() : _lightObjects(new ObjectsContainer) { }

std::size_t LightsHolder::addLight(const VecD &location, const VecD &direction, lightType type)
{
    auto light = std::make_shared<Light>(location, direction, type);
    return _lightObjects->addObject(light);;
}

void LightsHolder::deleteLight(const std::size_t id)
{
    _lightObjects->deleteObject(id);
}

std::shared_ptr<BaseObject> LightsHolder::getLight(const std::size_t id)
{
    return _lightObjects->getObject(id);
}


int LightsHolder::getCount()
{
    return _lightObjects->getCount();
}
