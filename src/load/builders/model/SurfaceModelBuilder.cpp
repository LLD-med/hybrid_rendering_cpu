#include "SurfaceModelBuilder.h"

void SurfaceModelBuilder::build()
{
    _model = std::make_shared<SurfaceModelImpl>();
}

void SurfaceModelBuilder::buildFace(const Face &face)
{
    if (!isBuild()) { }

    _model->addFace(face);
}

void SurfaceModelBuilder::buildMaterial(const  Material &material)
{
    if (!isBuild()) { }

    _model->setMaterial(material);
}

void SurfaceModelBuilder::buildMesh(const Mesh &mesh)
{
    if (!isBuild()) { }

    _model->setMesh(mesh);
}

bool SurfaceModelBuilder::isBuild() const
{
    return nullptr != _model;
}

std::shared_ptr<SurfaceModel> SurfaceModelBuilder::get()
{
    auto tmp = std::make_shared<SurfaceModel>(_model);
    return tmp;
}
