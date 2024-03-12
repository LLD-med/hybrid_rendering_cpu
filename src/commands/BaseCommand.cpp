#include <BaseCommand.h>

void BaseCommand::setManagers(std::shared_ptr<DrawManager> drawManager,
                              std::shared_ptr<LoadManager> loadManager,
                              std::shared_ptr<SceneManager> sceneManager,
                              std::shared_ptr<TransformManager> transformManager,
                              std::shared_ptr<PropertyManager> propertyManager,
                              std::shared_ptr<ModelLoadModerator> modelLoadModerator,
                              std::shared_ptr<SceneLoadModerator> sceneLoadModerator,
                              std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter,
                              std::shared_ptr<CamerasManager> camerasManager,
                              std::shared_ptr<LightsManager> lightsManager)
{
    _drawManager = drawManager;
    _loadManager = loadManager;
    _sceneManager = sceneManager;
    _transformManager = transformManager;
    _propertyManager = propertyManager;
    _modelLoadModerator = modelLoadModerator;
    _sceneLoadModerator = sceneLoadModerator;
    _drawCompositeAdapter = drawCompositeAdapter;
    _camerasManager = camerasManager;
    _lightsManager = lightsManager;
}
