#ifndef MODELTRANSFORMADAPTER_H
#define MODELTRANSFORMADAPTER_H

#include <BaseTransformAdapter.h>
#include "SurfaceModel.h"

class ModelTransformAdapter: public BaseTransformAdapter
{
public:
	virtual void request() override;
	virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) override;

protected:
    void updateCenter(std::shared_ptr<SurfaceModelImpl> data);
    void movePointsToOrigin(const VecD &center);
    void movePointsToCenter(const VecD &center);
    void transformPosition(std::shared_ptr<SurfaceModelImpl> data, Transform &t);

private:
    std::shared_ptr<SurfaceModel> _adaptee;
};

#endif // MODELTRANSFORMADAPTER_H

