#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include <DrawManager.h>
#include <LoadManager.h>
#include <SceneManager.h>
#include <TransformManager.h>
#include <CameraLoadModerator.h>
#include <ModelLoadModerator.h>
#include <SceneLoadModerator.h>
#include <DrawCompositeAdapter.h>
#include <ModelTransformAdapter.h>
#include <CompositeTransformAdapter.h>
#include <CamerasManager.h>
#include "LightsManager.h"
#include <CameraTransformAdapter.h>
#include <LightAdapter.h>
#include <PropertyManager.h>
#include <LightOpticalAdapter.h>
#include <ModelOpticalAdapter.h>

#include <memory>

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;

    virtual void setManagers(std::shared_ptr<DrawManager> drawManager,
                             std::shared_ptr<LoadManager> loadManager,
                             std::shared_ptr<SceneManager> sceneManager,
                             std::shared_ptr<TransformManager> transformManager,
                             std::shared_ptr<PropertyManager> propertyManager,
                             std::shared_ptr<ModelLoadModerator> modelLoadModerator,
                             std::shared_ptr<SceneLoadModerator> sceneLoadModerator,
                             std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter,
                             std::shared_ptr<CamerasManager> camerasManager,
                             std::shared_ptr<LightsManager> lightsManager);

    virtual void execute() = 0;

    virtual void setAdapter() { };

protected:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transformManager;
    std::shared_ptr<PropertyManager> _propertyManager;
    std::shared_ptr<ModelLoadModerator> _modelLoadModerator;
    std::shared_ptr<SceneLoadModerator> _sceneLoadModerator;
    std::shared_ptr<DrawCompositeAdapter> _drawCompositeAdapter;
    std::shared_ptr<CamerasManager> _camerasManager;
    std::shared_ptr<LightsManager> _lightsManager;
};


#endif //BASECOMMAND_H
