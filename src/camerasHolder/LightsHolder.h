#ifndef LIGHTSHOLDER_H
#define LIGHTSHOLDER_H

#include <ObjectsContainer.h>
#include "Vector.hpp"
#include "LightImpl.h"

class LightsHolder
{
public:
    LightsHolder();
    ~LightsHolder() = default;

    std::size_t addLight(const VecD &location, const VecD &direction, lightType type);
    void deleteLight(const std::size_t id);
    std::shared_ptr<BaseObject> getLight(const std::size_t id);

    int getCount();

protected:
    std::shared_ptr<ObjectsContainer> _lightObjects;
};


#endif // LIGHTSHOLDER_H
