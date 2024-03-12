#ifndef CAMERAMODEL_H
#define CAMERAMODEL_H

#include "Vector.hpp"

class CameraModel
{
public:
    CameraModel() = default;
    CameraModel(const VecD &location, const VecD &direction, const VecD &up = {0, 1, 0})
        : _location(location), _direction(direction), _up(up) { }

    CameraModel(float width, float height, VecD pos = {0, 0, -7}, VecD up = {0, 1, 0},
                VecD direction = {0, 0, 1}, double fov = 45, double zn = 0.1, double zf = 1000.)
        : _location(pos), _direction(direction), _up(up), _FOV(fov),
          _Znear(zn), _Zfar(zf)
    {
        _aspect_ratio = width / height;
    }
    ~CameraModel() = default;

    VecD getLocation() const;
    VecD getDirection() const;
    VecD getUp() const;
    double getFOV() const;
    double getZnear() const;
    double getZfar() const;
    double getAspectRatio() const;

    void setLocation(const VecD &location) { _location = location; }
    void setDirection(const VecD &direction) { _direction = direction; }
    void setUp(const VecD &up) { _up = up; }
    void setFOV(const double &fov) { _FOV = fov; };
    void setZnear(const double &near) { _Znear = near; };
    void setZfar(const double &far) { _Zfar = far; };
    void setAspectRatio(const double &ar) { _aspect_ratio = ar; };

private:
    VecD _location;
    VecD _direction;
    VecD _up;

    double _FOV;
    double _Znear;
    double _Zfar;

    double _aspect_ratio;
};


#endif // CAMERAMODEL_H
