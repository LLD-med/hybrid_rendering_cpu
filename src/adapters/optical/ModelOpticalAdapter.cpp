#include "ModelOpticalAdapter.h"

void ModelOpticalAdapter::setAdaptee(std::shared_ptr<BaseObject> adaptee)
{
    _adaptee = dynamic_pointer_cast<SurfaceModel>(adaptee);
}

void ModelOpticalAdapter::request()
{
    if (_adaptee)
    {
        std::shared_ptr<SurfaceModelImpl> model = _adaptee->_modelImpl;
        if (flag == 2)
        {
            model->setProperties(_coeffs);
        }
        if (flag == 1)
        {
            model->setColor(_color);
        }
        if (flag == 0)
        {
            model->setTexture(_texture);
        }
    }
}
