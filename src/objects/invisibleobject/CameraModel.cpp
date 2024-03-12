#include "CameraModel.h"

VecD CameraModel::getLocation() const
{
    return _location;
}

VecD CameraModel::getDirection() const
{
    return _direction;
}

VecD CameraModel::getUp() const
{
    return _up;
}

double CameraModel::getFOV() const
{
    return _FOV;
}

double CameraModel::getZnear() const
{
    return _Znear;
}

double CameraModel::getZfar() const
{
    return _Zfar;
}

double CameraModel::getAspectRatio() const
{
    return _aspect_ratio;
}
