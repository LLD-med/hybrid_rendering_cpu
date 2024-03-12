#include <LightAdapter.h>

void LightAdapter::setAdaptee(std::shared_ptr<BaseObject> adaptee)
{
    _adaptee = dynamic_pointer_cast<Light>(adaptee);
}

void LightAdapter::transformLight(std::shared_ptr<LightImpl> &lightObject)
{
    VecD location = lightObject->getLocation();
    VecD direction = lightObject->getDirection();

//    VecD normal = (direction.VectorProd(up)).VecNormalize();
//    normal *= _transformer.getElement(0, 0);

//    lightObject->setLocation(location + normal);
    location.setY(location.getY() + _transformer.getElement(0, 1));
    lightObject->setLocation(location + direction.VecNormalize() * _transformer.getElement(0, 2));

}

void LightAdapter::request()
{
    if (_adaptee && _transformer.getMatrix())
        transformLight(_adaptee->_light);
}
