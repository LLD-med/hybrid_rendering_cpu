#ifndef SURFACEMODEL_H
#define SURFACEMODEL_H

#include "BaseModel.h"
#include "SurfaceModelImpl.h"

class SurfaceModel : public BaseModel
{
    friend class DrawSurfaceModelAdapter;
    friend class ModelTransformAdapter;
    friend class CompositeAdapter;
    friend class DrawCompositeAdapter;
    friend class ModelOpticalAdapter;
public:
    SurfaceModel() : _modelImpl(new SurfaceModelImpl) { }
    explicit SurfaceModel(const std::shared_ptr<SurfaceModelImpl> &modelImpl) :
        _modelImpl(modelImpl) { }
    explicit SurfaceModel(const SurfaceModel &model);

//    ~SurfaceModel() override = default;

    virtual VecD getCenter() const override;

protected:
    std::shared_ptr<SurfaceModelImpl> _modelImpl;
};

#endif // SURFACEMODEL_H
