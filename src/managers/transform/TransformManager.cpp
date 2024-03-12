#include <cmath>

#include "TransformManager.h"


void TransformManager::setAdapter(std::shared_ptr<BaseTransformAdapter> adapter)
{
	_adapter = adapter;
}


void TransformManager::moveObject(const std::shared_ptr <BaseObject> &object,
                                  const double &dx,
                                  const double &dy,
                                  const double &dz)
{
    Transform transform;
    transform.setMove(dx, dy, dz);

    object->setMoveCoefs(dx, dy, dz);

    _adapter->setTransformer(transform);
	_adapter->setAdaptee(object);
	_adapter->request();
}


void TransformManager::scaleObject(const std::shared_ptr <BaseObject> &object,
								   const double &kx,
								   const double &ky,
								   const double &kz)
{
    Transform transform;
    transform.setScale(kx, ky, kz);

    object->setScaleCoefs(kx, ky, kz);

    _adapter->setTransformer(transform);
	_adapter->setAdaptee(object);
	_adapter->request();
}


void TransformManager::rotateObject(const std::shared_ptr <BaseObject> &object,
                                    const double &ox,
                                    const double &oy,
                                    const double &oz)
{
    Transform transform;
    transform.setRotate(ox, oy, oz);

    object->setRotateCoefs(ox, oy, oz);

    _adapter->setTransformer(transform);
	_adapter->setAdaptee(object);
	_adapter->request();
}

void TransformManager::multipleTransform(const std::shared_ptr <BaseObject> &object,
                                       const double &dx,
                                       const double &dy,
                                       const double &dz,
                                       const double &ox,
                                       const double &oy)
{
    Transform transform;
    transform.setMultipleTransform(dx, dy, dz, ox, oy);

    _adapter->setTransformer(transform);
    _adapter->setAdaptee(object);
    _adapter->request();
}

void TransformManager::transformObject(const std::shared_ptr<BaseObject> &object,
                                       Transform &transform)
{
    _adapter->setTransformer(transform);
	_adapter->setAdaptee(object);
	_adapter->request();
}
