#ifndef PROPERTYMANAGER_H
#define PROPERTYMANAGER_H

#include <BaseManager.h>
#include <BaseObject.h>
#include "BaseOpticalAdapter.h"

class PropertyManager : public BaseManager
{
public:
    PropertyManager() = default;
    PropertyManager(const PropertyManager &manager) = delete;
    PropertyManager &operator = (const PropertyManager &manager) = delete;

    ~PropertyManager() = default;

    void setAdapter(std::shared_ptr<BaseOpticalAdapter> adapter);

    void changeTexture(const std::shared_ptr<BaseObject> &object,
                       QImage &texture);

    void changeColor(const std::shared_ptr<BaseObject> &object,
                     const double &cx, const double &cy, const double &cz);

    void changeProperties(const std::shared_ptr<BaseObject> &object,
                          const double &px, const double &py, const double &pz);

private:
    std::shared_ptr<BaseOpticalAdapter> _adapter;
};

#endif // PROPERTYMANAGER_H
