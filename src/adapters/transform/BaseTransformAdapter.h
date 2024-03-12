#ifndef BASETRANSFORMADAPTER_H
#define BASETRANSFORMADAPTER_H

#include <BaseAdapter.h>
#include <BaseObject.h>
#include <Transform.h>

class BaseTransformAdapter: public BaseAdapter
{
public:
	virtual ~BaseTransformAdapter() = default;

    void setTransformer(Transform &transformer) { _transformer = transformer; }
	virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) = 0;
	virtual void request() = 0;

protected:
    Transform _transformer;
};
#endif // BASETRANSFORMADAPTER_H
