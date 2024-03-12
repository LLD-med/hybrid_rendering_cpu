#ifndef LIGHTOPTICALADAPTER_H
#define LIGHTOPTICALADAPTER_H

#include "BaseOpticalAdapter.h"
#include "Light.h"

class LightOpticalAdapter : public BaseOpticalAdapter
{
public:
    virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) override;
    virtual void request() override;

protected:
    std::shared_ptr<Light> _adaptee;
};


#endif // LIGHTOPTICALADAPTER_H
