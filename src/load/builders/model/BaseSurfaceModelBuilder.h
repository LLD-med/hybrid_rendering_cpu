#ifndef BASESURFACEMODELBUILDER_H
#define BASESURFACEMODELBUILDER_H

#include <BaseBuilder.h>
#include <memory>
#include "surfacemodel/Face.h"
#include "surfacemodel/Material.h"
#include "surfacemodel/Mesh.h"
#include "surfacemodel/SurfaceModel.h"
#include "surfacemodel/SurfaceModelImpl.h"

class BaseSurfaceModelBuilder : public BaseBuilder
{
public:
    BaseSurfaceModelBuilder() = default;
    ~BaseSurfaceModelBuilder() = default;

    virtual void build() override = 0;
    virtual void buildFace(const Face &face) = 0;
    virtual void buildMaterial(const  Material &material) = 0;
    virtual void buildMesh(const Mesh &mesh) = 0;
    virtual bool isBuild() const override = 0;

    virtual std::shared_ptr<SurfaceModel> get() = 0;

protected:
    std::shared_ptr<SurfaceModelImpl> _model;
};

#endif // BASESURFACEMODELBUILDER_H
