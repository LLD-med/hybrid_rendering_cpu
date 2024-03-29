#ifndef BASECAMERABUILDER_H
#define BASECAMERABUILDER_H

#include <Camera.h>
#include <BaseBuilder.h>

class BaseCameraBuilder : public BaseBuilder
{
public:
    BaseCameraBuilder() = default;
    ~BaseCameraBuilder() = default;

    virtual void build() override = 0;
//    virtual void buildLocation(const CameraModel &newCamera) = 0;
    virtual void buildLocation(const VecD &location, const VecD &direction) = 0;
    virtual bool isBuild() const override = 0;

    virtual std::shared_ptr<Camera> get() = 0;

protected:
    std::shared_ptr<Camera> _camera;
};

#endif // BASECAMERABUILDER_H
