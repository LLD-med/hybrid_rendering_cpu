#ifndef CAMERASMANAGER_H
#define CAMERASMANAGER_H

#include <BaseManager.h>
#include <Camera.h>
#include <../../camerasHolder/CamerasHolder.h>

class CamerasManager : public BaseManager
{
public:
    CamerasManager();
    explicit CamerasManager(const CamerasManager&) = delete;
    CamerasManager& operator=(const CamerasManager&) = delete;
    ~CamerasManager() = default;

    std::shared_ptr<CamerasHolder> getHolder() const;
    void setHolder(std::shared_ptr<CamerasHolder> holder);
    std::shared_ptr<Camera> getCamera() const;
    void setCamera(const std::size_t id);

    size_t addCamera(const VecD &location, const VecD &direction) { return _holder->addCamera(location, direction); };
    size_t addCamera(int width, int height) { return _holder->addCamera(width, height); };

    void deleteCamera(const size_t id)
    {
        _holder->deleteCamera(id);
    };

private:
    std::shared_ptr<CamerasHolder> _holder;
    std::shared_ptr<Camera> _currentCamera;
};

#endif // CAMERASMANAGER_H
