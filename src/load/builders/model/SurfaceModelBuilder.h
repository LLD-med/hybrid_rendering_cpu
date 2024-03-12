#ifndef SURFACEMODELBUILDER_H
#define SURFACEMODELBUILDER_H

#include "BaseSurfaceModelBuilder.h"

class SurfaceModelBuilder : public BaseSurfaceModelBuilder
{
public:
    SurfaceModelBuilder() = default;
//    ~SurfaceModelBuilder() = default;
    virtual ~SurfaceModelBuilder() {};

    void build() override;
    void buildFace(const Face &face) override;
    void buildMaterial(const  Material &material) override;
    void buildMesh(const Mesh &mesh) override;
    bool isBuild() const override;

    std::shared_ptr<SurfaceModel> get() override;
};

#endif // SURFACEMODELBUILDER_H
