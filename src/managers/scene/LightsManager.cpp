#include "LightsManager.h"

LightsManager::LightsManager()
{
    _holder = std::make_shared<LightsHolder>();
}

std::shared_ptr<LightsHolder> LightsManager::getHolder() const
{
    return _holder;
}

void LightsManager::setHolder(std::shared_ptr<LightsHolder> holder)
{
    _holder = std::move(holder);
}

void LightsManager::setLight(const std::size_t id)
{
    _currentLight = std::dynamic_pointer_cast<Light>(_holder->getLight(id));
}


std::shared_ptr<Light> LightsManager::getLight() const
{
//    return std::dynamic_pointer_cast<Light>(_holder->getLight(id));
    return _currentLight;
}

std::shared_ptr<Light> LightsManager::getLightById(const std::size_t id) const
{
    return std::dynamic_pointer_cast<Light>(_holder->getLight(id));
}
