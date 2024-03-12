#include "CamerasHolder.h"
#include "Camera.h"

CamerasHolder::CamerasHolder() : _cameraObjects(new ObjectsContainer) { }

std::size_t CamerasHolder::addCamera(const VecD &location, const VecD &direction)
{
    auto camera = std::make_shared<Camera>(location, direction);
    return _cameraObjects->addObject(camera);
}

std::size_t CamerasHolder::addCamera(int width, int height)
{
    auto camera = std::make_shared<Camera>(width, height);
    return _cameraObjects->addObject(camera);
}

void CamerasHolder::deleteCamera(const std::size_t id)
{
    _cameraObjects->deleteObject(id);
}

std::shared_ptr<BaseObject> CamerasHolder::getCamera(const std::size_t id)
{
    return _cameraObjects->getObject(id);
}
