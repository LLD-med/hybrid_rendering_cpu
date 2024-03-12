#ifndef CAMERA_H
#define CAMERA_H

#include "CameraModel.h"
#include "InvisibleObject.h"
#include "Vector.hpp"
#include "Transform.h"

class Camera : public InvisibleObject
{
    friend class DrawSurfaceModelAdapter;
	friend class CameraTransformAdapter;
    friend class DrawCompositeAdapter;
public:
    Camera();
    explicit Camera(const std::shared_ptr<CameraModel> &camera) : _cameraImpl(camera) { }
    explicit Camera(const Camera &camera);
    explicit Camera(float width, float height, VecD pos = {0, 0, -7}, VecD up = {0, 1, 0},
                    VecD direction = {0, 0, 1}, double fov = 45, double zn = 0.1f, double zf = 1000.f);


    Camera(const VecD &location, const VecD &direction);
    ~Camera() override;

    virtual VecD getCenter() const override;

    Transform getView();
    Transform getProjection();

private:
    std::shared_ptr<CameraModel> _cameraImpl;
};


#endif //CAMERA_H
