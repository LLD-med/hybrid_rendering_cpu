#include "CamerasManager.h"

CamerasManager::CamerasManager()
{
    _holder = std::make_shared<CamerasHolder>();
}

std::shared_ptr<Camera> CamerasManager::getCamera() const
{
    return _currentCamera;
}

void CamerasManager::setCamera(const std::size_t id)
{
    _currentCamera = std::dynamic_pointer_cast<Camera>(_holder->getCamera(id));
}

std::shared_ptr<CamerasHolder> CamerasManager::getHolder() const
{
    return _holder;
}

void CamerasManager::setHolder(std::shared_ptr<CamerasHolder> holder)
{
    _holder = std::move(holder);
}
