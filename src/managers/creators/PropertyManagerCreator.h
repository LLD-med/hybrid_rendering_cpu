#ifndef PROPERTYMANAGERCREATOR_H
#define PROPERTYMANAGERCREATOR_H

#include "PropertyManager.h"

class PropertyManagerCreator
{
public:
    std::shared_ptr<PropertyManager> createManager();

private:
    void createInstance();

    std::shared_ptr<PropertyManager> _manager;
};

#endif // PROPERTYMANAGERCREATOR_H
