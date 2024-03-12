#ifndef LIGHTADAPTER_H
#define LIGHTADAPTER_H

#include <BaseTransformAdapter.h>
#include "Light.h"

class LightAdapter: public BaseTransformAdapter
{
public:
    virtual void request() override;
    virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) override;

protected:
    void transformLight(std::shared_ptr<LightImpl> &lightObject);

private:
    std::shared_ptr<Light> _adaptee;
};

#endif // LIGHTADAPTER_H
