#ifndef CAMERABUILDER_H
#define CAMERABUILDER_H

#include <BaseCameraBuilder.h>
//#include <CameraModel.h>

class CameraBuilder : public BaseCameraBuilder
{
public:
    CameraBuilder() = default;
//    ~CameraBuilder() = default;
    virtual ~CameraBuilder() {}

    void build() override;
//    void buildLocation(const CameraModel &newCamera) override;
    void buildLocation(const VecD &location, const VecD &direction) override;
    bool isBuild() const override;

    std::shared_ptr<Camera> get() override;
};

#endif //CAMERABUILDER_H
