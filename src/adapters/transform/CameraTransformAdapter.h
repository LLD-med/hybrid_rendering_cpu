#ifndef CAMERATRANSFORMADAPTER_H
#define CAMERATRANSFORMADAPTER_H

#include <BaseTransformAdapter.h>
#include "Camera.h"

class CameraTransformAdapter : public BaseTransformAdapter
{
public:
	virtual void request() override;
	virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) override;

protected:
    void transformCamera(std::shared_ptr<CameraModel> &cameraObject);

private:
	std::shared_ptr<Camera> _adaptee;
};

#endif // CAMERATRANSFORMADAPTER_H
