#include "ModelPropertyCommand.h"

void ModelPropertyCommand::setAdapter()
{
    auto adapter = std::make_shared<ModelOpticalAdapter>();
    _propertyManager->setAdapter(adapter);
}


ChangeModelColor::ChangeModelColor(const std::shared_ptr<BaseObject> model, const double cx, const double cy, const double cz) :
    _model(model), _cx(cx), _cy(cy), _cz(cz)
{
    _method = &PropertyManager::changeColor;
}

void ChangeModelColor::execute()
{
    ((*_propertyManager).*_method)(_model, _cx, _cy, _cz);
}


ChangeModelTexture::ChangeModelTexture(const std::shared_ptr<BaseObject> model, QImage texture) :
    _model(model), _texture(texture)
{
    _method = &PropertyManager::changeTexture;
}

void ChangeModelTexture::execute()
{
    ((*_propertyManager).*_method)(_model, _texture);
}


ChangeModelProperties::ChangeModelProperties(const std::shared_ptr<BaseObject> model, const double px, const double py, const double pz) :
    _model(model), _px(px), _py(py), _pz(pz)
{
    _method = &PropertyManager::changeProperties;
}

void ChangeModelProperties::execute()
{
    ((*_propertyManager).*_method)(_model, _px, _py, _pz);
}
