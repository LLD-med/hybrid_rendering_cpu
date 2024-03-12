#include "CamerasManagerCreator.h"

std::shared_ptr<CamerasManager> CamerasManagerCreator::createManager()
{
    if (nullptr == _manager)
        createInstance();

    return _manager;
}

void CamerasManagerCreator::createInstance() {
    static std::shared_ptr<CamerasManager> manager(new CamerasManager());
    _manager = manager;
}
