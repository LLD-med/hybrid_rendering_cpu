#include "CameraBuilder.h"
#include <FileSceneDirector.h>
#include <FileCameraDirector.h>
#include <FileSurfaceModelDirector.h>
#include <Exceptions.hpp>

FileSceneDirector::FileSceneDirector()
{
//	auto builder = std::shared_ptr<BaseSceneBuilder>(new SceneBuilder());
    auto builder = std::make_shared<SceneBuilder>();
	_builder = builder;
}

FileSceneDirector::FileSceneDirector(std::shared_ptr<BaseSceneBuilder> &builder)
{
	_builder = builder;
}

std::shared_ptr<Scene> FileSceneDirector::create(std::shared_ptr<BaseLoader> &loader)
{
    loader->open();

	_builder->build();

    createModels(loader);
    createCameras(loader);

	loader->close();

	return _builder->get();
}


void FileSceneDirector::createModels(std::shared_ptr<BaseLoader> &loader)
{
    //может сломать чтение obj файла!!!
	size_t modelsCount = loader->loadCount();

    std::shared_ptr<BaseSurfaceModelBuilder> modBuilder = std::make_shared<SurfaceModelBuilder>();

    for (size_t i = 0; i < modelsCount; i++)
    {
        auto model = FileSurfaceModelDirector(modBuilder).create(loader);
		_builder->buildObject(model);
    }
}

void FileSceneDirector::createCameras(std::shared_ptr<BaseLoader> &loader)
{
	size_t camsCount = loader->loadCount();

	std::shared_ptr<BaseCameraBuilder> camBuilder = std::make_shared<CameraBuilder>();

    for (size_t i = 0; i < camsCount; i++)
    {
        auto camera = FileCameraDirector(camBuilder).create(loader);
		_builder->buildObject(camera);
    }
}
