#include "CompositeTransformAdapter.h"
#include <QDebug>

void CompositeTransformAdapter::setAdaptee(std::shared_ptr<BaseObject> adaptee)
{
	_adaptee = dynamic_pointer_cast<Composite>(adaptee);
}


void CompositeTransformAdapter::request()
{
    if (_adaptee && _transformer.getMatrix())
	{
		for (auto &elem : _adaptee->_elements)
		{
			if (elem->isComposite())
			{
				auto adapter = std::make_shared<CompositeTransformAdapter>(CompositeTransformAdapter());
				auto com_sh_ptr = std::dynamic_pointer_cast<Composite>(elem);
				adapter->setAdaptee(com_sh_ptr);
                adapter->setTransformer(_transformer);
				adapter->request();
			}
			else
			{
				auto adapter = std::make_shared<ModelTransformAdapter>(ModelTransformAdapter());

                auto model_sh_ptr = std::dynamic_pointer_cast<SurfaceModel>(elem);
				adapter->setAdaptee(model_sh_ptr);
                adapter->setTransformer(_transformer);
                adapter->request();
			}
		}
	}
}
