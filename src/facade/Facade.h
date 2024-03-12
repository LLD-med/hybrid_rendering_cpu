#ifndef FACADE_H
#define FACADE_H

#include <memory>

#include <BaseCommand.h>

#include <ManagerSolution.h>
#include <DrawManagerCreator.h>
#include <SceneManagerCreator.h>
#include <CamerasManagerCreator.h>
#include <TransformManagerCreator.h>
#include <LoadManagerCreator.h>
#include <../../adapters/transform/BaseTransformAdapter.h>
#include <LightsManagerCreator.h>
#include <PropertyManagerCreator.h>
#include <ModeratorSolution.h>
#include <ModelLoadModeratorCreator.h>
#include <SceneLoadModeratorCreator.h>


class Facade
{
public:
    Facade();
    ~Facade() = default;

    void execute(BaseCommand &command);
private:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<CamerasManager> _camerasManager;
    std::shared_ptr<LightsManager> _lightsManager;
    std::shared_ptr<TransformManager> _transformManager;
    std::shared_ptr<PropertyManager> _propertyManager;
    std::shared_ptr<ModelLoadModerator> _modelLoadModerator;
    std::shared_ptr<SceneLoadModerator> _sceneLoadModerator;
    std::shared_ptr<DrawCompositeAdapter> _drawCompositeAdapter;
};

#endif //FACADE_H
