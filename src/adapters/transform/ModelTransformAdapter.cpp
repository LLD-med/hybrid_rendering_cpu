#include "ModelTransformAdapter.h"
#include <QDebug>
#include "Vector.hpp"

void ModelTransformAdapter::setAdaptee(std::shared_ptr<BaseObject> adaptee)
{
    _adaptee = dynamic_pointer_cast<SurfaceModel>(adaptee);
}


void ModelTransformAdapter::updateCenter(std::shared_ptr<SurfaceModelImpl> model)
{
    VecD center = VecD({0, 0, 0});
    size_t count = 0;
    for (const auto &vertex : model->getMesh().getVertices())
    {
        center = center + vertex.getPosition();
        count++;
    }

    center = VecD({ center.getX() / count,
                    center.getY() / count,
                    center.getZ() / count });

    model->setCenter(center);
}

void ModelTransformAdapter::transformPosition(std::shared_ptr<SurfaceModelImpl> model, Transform &transformer)
{
    auto mesh = model->getMesh();
    for (auto &vertex : mesh.getVertices())
    {
        auto pos = vertex.getPosition();
        Transform cur_location = {{pos.getX(), pos.getY(), pos.getZ(), 1}};
        Transform new_location = cur_location * transformer;

        vertex.setPosition(VecD({new_location.getElement(0, 0), new_location.getElement(0, 1), new_location.getElement(0, 2)}));
    }
}

void ModelTransformAdapter::movePointsToOrigin(const VecD &center)
{
    VecD diff = VecD({0, 0, 0}) - center;

    Transform move_diff;
    move_diff.setMove(diff.getX(),  diff.getY(),  diff.getZ());

    transformPosition(_adaptee->_modelImpl, move_diff);
    updateCenter(_adaptee->_modelImpl);
}



void ModelTransformAdapter::movePointsToCenter(const VecD &center)
{
//    VecD diff = center;
    VecD diff = VecD(center);

    Transform move_diff;
    move_diff.setMove(diff.getX(),  diff.getY(),  diff.getZ());

    transformPosition(_adaptee->_modelImpl, move_diff);
    updateCenter(_adaptee->_modelImpl);
}


void ModelTransformAdapter::request()
{
    if (_adaptee && _transformer.getMatrix())
	{
//        auto tmp = _adaptee->setMoveCoefs();
//        updateCenter(_adaptee->_modelImpl);

//        VecD oldCenter = _adaptee->getCenter();

//        movePointsToOrigin(oldCenter);
//        transformPosition(_adaptee->_modelImpl, _transformer);
//        movePointsToCenter(oldCenter);
	}
}
