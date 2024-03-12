#include "SurfaceModel.h"

SurfaceModel::SurfaceModel(const SurfaceModel &model)
{
    _id = model._id;
}

//VecD SurfaceModel::getCenter() const
//{
//    std::vector<Vertex> vertices = _modelImpl->getMesh().getVertices();
//    auto vert_num = vertices.size();
//    double center_x = 0, center_y = 0, center_z = 0;
//    for (auto& vertex: vertices)
//    {
//        center_x += vertex.getPosition().getX();
//        center_y += vertex.getPosition().getY();
//        center_z += vertex.getPosition().getZ();
//    }
//    VecD res({center_x / vert_num, center_y / vert_num, center_z / vert_num});

//    return res;
//}

VecD SurfaceModel::getCenter() const
{
    return _modelImpl->getCenter();
}
