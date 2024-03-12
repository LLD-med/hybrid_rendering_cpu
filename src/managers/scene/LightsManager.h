#ifndef LightsManager_H
#define LightsManager_H

#include <BaseManager.h>
#include "Light.h"
#include "LightsHolder.h"

class LightsManager : public BaseManager
{
public:
    LightsManager();

    explicit LightsManager(const LightsManager&) = delete;
    LightsManager& operator=(const LightsManager&) = delete;
    ~LightsManager() = default;

    std::shared_ptr<LightsHolder> getHolder() const;
    void setHolder(std::shared_ptr<LightsHolder> holder);

    void setLight(const std::size_t id);

    size_t addLight(const VecD &location, const VecD &direction, lightType type)
    {
        return _holder->addLight(location, direction, type);
    };

    void deleteLight(const size_t id)
    {
        _holder->deleteLight(id);
    };

    std::shared_ptr<Light> getLight() const;

    std::shared_ptr<Light> getLightById(const std::size_t id) const;

private:
    std::shared_ptr<LightsHolder> _holder;
    std::shared_ptr<Light> _currentLight;
};

#endif // LightsManager_H
