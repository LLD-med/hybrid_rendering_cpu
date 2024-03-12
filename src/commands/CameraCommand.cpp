#include <QDebug>

#include <CameraCommand.h>

void CameraCommand::setAdapter()
{
    auto adapter = std::make_shared<CameraTransformAdapter>();
    _transformManager->setAdapter(adapter);
}

AddCameraFull::AddCameraFull(const ID &id, const VecD &location, const VecD &direction) :
    _id(id), _location(location), _direction(direction) {
    _method = &CamerasManager::addCamera;
}

void AddCameraFull::execute()
{
    (*_id) = ((*_camerasManager).*_method)(_location, _direction);
}

AddCamera::AddCamera(const ID &id, int width, int height) :
    _id(id), _width(width), _height(height) {
    _method = &CamerasManager::addCamera;
}

void AddCamera::execute()
{
    (*_id) = ((*_camerasManager).*_method)(_width, _height);
}


GetMainCamera::GetMainCamera(std::shared_ptr<Camera> &camera) : _camera(camera)
{
    _method = &CamerasManager::getCamera;
}

void GetMainCamera::execute()
{
    _camera = ((*_camerasManager).*_method)();
}

RemoveCamera::RemoveCamera(const std::size_t id) : _id(id)
{
    _method = &CamerasManager::deleteCamera;
}

void RemoveCamera::execute()
{
    ((*_camerasManager).*_method)(_id);
}

SetCamera::SetCamera(const std::size_t id) : _id(id)
{
    _method = &CamerasManager::setCamera;
}

void SetCamera::execute()
{
    ((*_camerasManager).*_method)(_id);
}


TransformCamera::TransformCamera(const std::shared_ptr<Camera> camera, const double dx, const double dy, const double dz, const double ox, const double oy) :
    _camera(camera), _dx(dx), _dy(dy), _dz(dz), _ox(ox), _oy(oy)
{
    _method = &TransformManager::multipleTransform;
}

void TransformCamera::execute()
{
    ((*_transformManager).*_method)(_camera, _dx, _dy, _dz, _ox, _oy);
}

//MoveCamera::MoveCamera(const std::shared_ptr<Camera> camera, const double dx, const double dy, const double dz) :
//    _camera(camera), _dx(dx), _dy(dy), _dz(dz)
//{
//    _method = &TransformManager::moveObject;
//}

//void MoveCamera::execute()
//{
//    ((*_transformManager).*_method)(_camera, _dx, _dy, _dz);
//}


//RotateCamera::RotateCamera(const std::shared_ptr<Camera> camera, const double ox, const double oy, const double oz) :
//    _camera(camera), _ox(ox), _oy(oy), _oz(oz)
//{
//    _method = &TransformManager::rotateObject;
////    _method = &TransformManager::moveObject;
//}

//void RotateCamera::execute()
//{

//    ((*_transformManager).*_method)(_camera, _ox, _oy, _oz);
//}


