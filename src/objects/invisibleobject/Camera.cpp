#include <Camera.h>

Camera::Camera()
{
    _cameraImpl = std::make_shared<CameraModel>();
}

Camera::Camera(const Camera &camera)
{
    _cameraImpl = camera._cameraImpl;
    _id = camera._id;
}

Camera::Camera(float width, float height, VecD pos, VecD up, VecD direction,
               double fov, double zn, double zf)
{
    _cameraImpl = std::make_shared<CameraModel>(width, height, pos, up,
                                                direction, fov, zn, zf);
}

Camera::Camera(const VecD &location, const VecD &direction)
{
    _cameraImpl = std::make_shared<CameraModel>(location, direction);
}

VecD Camera::getCenter() const
{
    return _cameraImpl->getLocation();
}

Transform Camera::getView()
{
    Transform viewMat;
    viewMat.setView(_cameraImpl->getLocation(),
                    _cameraImpl->getLocation() + _cameraImpl->getDirection(),
                    _cameraImpl->getUp());
    return viewMat;
}

Transform Camera::getProjection()
{
    Transform projectionwMat;
    projectionwMat.setProjectionFOV(_cameraImpl->getFOV(),
                             _cameraImpl->getAspectRatio(),
                             _cameraImpl->getZnear(),
                             _cameraImpl->getZfar());
    return projectionwMat;
}

Camera::~Camera() { }
