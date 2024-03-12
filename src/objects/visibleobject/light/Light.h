#ifndef LIGHT_H
#define LIGHT_H

#include <VisibleObject.h>
#include "LightImpl.h"

class Light: public VisibleObject
{
    friend class LightAdapter;
    friend class LightOpticalAdapter;
    friend class DrawCompositeAdapter;
public:
    Light();
    explicit Light(const std::shared_ptr<LightImpl> &light) : _light(light) { }
    explicit Light(const Light &light);

    Light(const VecD &location, const VecD &direction, lightType type);
    ~Light() override;

    virtual VecD getCenter() const override;

    lightType getType() const;
private:
    std::shared_ptr<LightImpl> _light;
};

#endif // LIGHT_H
