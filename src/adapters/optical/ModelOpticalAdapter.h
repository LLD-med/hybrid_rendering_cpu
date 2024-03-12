#ifndef MODELOPTICALADAPTER_H
#define MODELOPTICALADAPTER_H

#include "BaseOpticalAdapter.h"
#include "SurfaceModel.h"

class ModelOpticalAdapter : public BaseOpticalAdapter
{
public:
    virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) override;
    virtual void request() override;

//protected:
//    void changeMaterial(std::shared_ptr<SurfaceModelImpl> &model);

private:
    std::shared_ptr<SurfaceModel> _adaptee;
};

#endif // MODELOPTICALADAPTER_H
