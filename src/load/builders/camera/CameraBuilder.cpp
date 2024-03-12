#include <CameraBuilder.h>

void CameraBuilder::build()
{
    _camera = std::make_shared<Camera>();
}

//void CameraBuilder::buildLocation(const CameraModel &newCamera)
void CameraBuilder::buildLocation(const VecD &location, const VecD &direction)
{
    auto camera = std::make_shared<Camera>(location, direction);
}

bool CameraBuilder::isBuild() const
{
    return nullptr != _camera;
}

std::shared_ptr<Camera> CameraBuilder::get()
{
    return _camera;
}
