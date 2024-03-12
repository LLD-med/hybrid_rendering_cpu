#include "CameraTransformAdapter.h"
#include "Vector.hpp"
#include "Transform.h"

void CameraTransformAdapter::setAdaptee(std::shared_ptr<BaseObject> adaptee)
{
	_adaptee = dynamic_pointer_cast<Camera>(adaptee);
}

VecD rotateQautr(const VecD &axis, const VecD &v, const double &angle)
{
    VecD u({ v.getX(), v.getY(), v.getZ(), 0 });
    VecD q({ axis.VecNormalize().getX(), axis.VecNormalize().getY(), axis.VecNormalize().getZ(), cos(angle * 0.5) });
    double sin_angle = sin(angle * 0.5);
    q.setX(q.getX() * sin_angle);
    q.setY(q.getY() * sin_angle);
    q.setZ(q.getZ() * sin_angle);

    VecD v1({ q.getX(), q.getY(), q.getZ() });
    VecD v2({ u.getX(), u.getY(), u.getZ() });
    VecD qu = v2 * q.getW() + v1.VectorProd(v2);

    v1 = VecD{ qu.getX(), qu.getY(), qu.getZ() };
    v2 = VecD{ -q.getX(), -q.getY(), -q.getZ() };

    return v1 * q.getW() + v1.VectorProd(v2);
}

void CameraTransformAdapter::transformCamera(std::shared_ptr<CameraModel> &cameraObject)
{
    // движение камеры
    VecD location = cameraObject->getLocation();
    VecD direction = cameraObject->getDirection();
    VecD up = cameraObject->getUp();

    VecD normal = (direction.VectorProd(up)).VecNormalize();
    normal *= _transformer.getElement(0, 0);

    cameraObject->setLocation(location + normal);
    location.setY(location.getY() + _transformer.getElement(0, 1));
    cameraObject->setLocation(location + direction.VecNormalize() * _transformer.getElement(0, 2));

    // вращение камеры
    normal = (direction.VectorProd(up)).VecNormalize();
    cameraObject->setDirection(rotateQautr(normal, direction, _transformer.getElement(0, 3)));
    cameraObject->setUp(rotateQautr(normal, up, _transformer.getElement(0, 3)));

    Transform rotateY;
    rotateY.setRotate(0, _transformer.getElement(0, 4), 0);

    cameraObject->setDirection(direction * rotateY);
    cameraObject->setUp(up * rotateY);
//    cameraObject->setDirection(rotateY.VectorByTransform(direction));
//    cameraObject->setUp(rotateY.VectorByTransform(up));
}

void CameraTransformAdapter::request()
{
    if (_adaptee && _transformer.getMatrix())
        transformCamera(_adaptee->_cameraImpl);
}
