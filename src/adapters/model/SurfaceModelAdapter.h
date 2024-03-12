#ifndef SURFACEMODELADAPTER_H
#define SURFACEMODELADAPTER_H

#include <BaseAdapter.h>
#include "SurfaceModel.h"

class SurfaceModel;

class SurfaceModelAdapter: public BaseAdapter
{
public:
    virtual ~SurfaceModelAdapter() = default;

    virtual void setAdaptee(std::shared_ptr<SurfaceModel> adaptee) { _adaptee = adaptee; }

    virtual void request() = 0;
protected:
    std::shared_ptr<SurfaceModel> _adaptee;
};

#endif // SURFACEMODELADAPTER_H
