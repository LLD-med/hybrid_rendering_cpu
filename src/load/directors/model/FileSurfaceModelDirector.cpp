#include "FileSurfaceModelDirector.h"
#include "surfacemodel/Material.h"

#include <QDebug>

FileSurfaceModelDirector::FileSurfaceModelDirector()
{
    auto builder = std::shared_ptr<SurfaceModelBuilder>(new SurfaceModelBuilder());
    _builder = builder;
}

FileSurfaceModelDirector::FileSurfaceModelDirector(std::shared_ptr<BaseSurfaceModelBuilder> &builder)
{
    _builder = builder;
}

std::shared_ptr<BaseObject> FileSurfaceModelDirector::create(std::shared_ptr<BaseLoader> loader)
{
    loader->open();
    _builder->build();

    std::string meshName = loader->loadMeshName();
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices = loader->loadVertices(indices);
    Mesh modelMesh = Mesh(meshName, vertices, indices);

    Material mat = loader->loadMaterial();
    std::vector<Face> faces = loader->loadFaces(vertices, indices);

    _builder->buildMesh(modelMesh);
    _builder->buildMaterial(mat);

    for(int i = 0; i < (int)faces.size(); i++)
        _builder->buildFace(faces[i]);

    loader->close();

    auto tmp = _builder->get();
    return tmp;
}
