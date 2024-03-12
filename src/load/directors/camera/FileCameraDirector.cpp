#include <FileCameraDirector.h>
#include <Exceptions.hpp>
#include <CameraBuilder.h>

FileCameraDirector::FileCameraDirector()
{

    auto builder = std::make_shared<CameraBuilder>();
	_builder = builder;
}

FileCameraDirector::FileCameraDirector(std::shared_ptr<BaseCameraBuilder> builder)
{
	_builder = builder;
}

std::shared_ptr<BaseObject> FileCameraDirector::create(std::shared_ptr<BaseLoader> &loader)
{
    loader->open();

	_builder->build();
    VecD location = loader->loadVec();
    VecD direction = loader->loadVec();
	_builder->buildLocation(location, direction);

	loader->close();

	return _builder->get();
}
