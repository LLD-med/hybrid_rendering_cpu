#include "PropertyManager.h"

void PropertyManager::setAdapter(std::shared_ptr<BaseOpticalAdapter> adapter)
{
    _adapter = adapter;
}

void PropertyManager::changeTexture(const std::shared_ptr<BaseObject> &object,
                                    QImage &texture)
{
    _adapter->setTexture(texture);
    _adapter->setAdaptee(object);
    _adapter->request();
}

void PropertyManager::changeColor(const std::shared_ptr<BaseObject> &object,
                                  const double &cx, const double &cy, const double &cz)
{
    VecD color = VecD({cx, cy, cz});
    _adapter->setColor(color);
    _adapter->setAdaptee(object);
    _adapter->request();
}

void PropertyManager::changeProperties(const std::shared_ptr<BaseObject> &object,
                                       const double &px, const double &py, const double &pz)
{
    VecD properties = VecD({px, py, pz});
    _adapter->setCoeff(properties);
    _adapter->setAdaptee(object);
    _adapter->request();
}
