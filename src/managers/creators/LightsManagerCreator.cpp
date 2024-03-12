#include "LightsManagerCreator.h"

std::shared_ptr<LightsManager> LightsManagerCreator::createManager()
{
    if (nullptr == _manager)
        createInstance();

    return _manager;
}

void LightsManagerCreator::createInstance()
{
    static std::shared_ptr<LightsManager> manager(new LightsManager());
    _manager = manager;
}
