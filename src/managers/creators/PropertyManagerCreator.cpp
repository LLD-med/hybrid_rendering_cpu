#include "PropertyManagerCreator.h"

std::shared_ptr<PropertyManager> PropertyManagerCreator::createManager()
{
    if (nullptr == _manager)
        createInstance();

    return _manager;
}

void PropertyManagerCreator::createInstance()
{
    static std::shared_ptr<PropertyManager> manager(new PropertyManager());
    _manager = manager;
}
