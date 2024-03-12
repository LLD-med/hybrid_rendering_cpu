#include <utility>
#include "SceneManager.h"


SceneManager::SceneManager()
{
    _scene = std::make_shared<Scene>();
}


std::shared_ptr<Scene> SceneManager::getScene() const
{
    return _scene;
}

size_t SceneManager::addObject(const std::shared_ptr<BaseObject> &object)
{
    return _scene->addObject(object);
};

void SceneManager::deleteCamera(const size_t id)
{
    _scene->deleteObject(id);
};

void SceneManager::setScene(std::shared_ptr<Scene> &scene)
{
    _scene = std::move(scene);
}
