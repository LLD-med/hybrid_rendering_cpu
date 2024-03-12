#ifndef CAMERASHOLDER_H
#define CAMERASHOLDER_H

#include <ObjectsContainer.h>
#include <Composite.h>
#include "Vector.hpp"

class CamerasHolder
{
public:
	CamerasHolder();
	~CamerasHolder() = default;

    std::size_t addCamera(const VecD &location, const VecD &direction);
    std::size_t addCamera(int width, int height);
    void deleteCamera(const std::size_t id);
    std::shared_ptr<BaseObject> getCamera(const std::size_t id);

protected:
    std::shared_ptr<ObjectsContainer> _cameraObjects;
};

#endif // CAMERASHOLDER_H
