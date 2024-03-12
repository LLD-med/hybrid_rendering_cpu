#ifndef COMPOSITETRANSFORMADAPTER_H
#define COMPOSITETRANSFORMADAPTER_H

#include <BaseTransformAdapter.h>
#include <ModelTransformAdapter.h>
#include <Composite.h>

class CompositeTransformAdapter : public BaseTransformAdapter
{
public:
	virtual void request() override;
	virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) override;
private:
	std::shared_ptr<Composite> _adaptee;
};

#endif // COMPOSITETRANSFORMADAPTER_H
