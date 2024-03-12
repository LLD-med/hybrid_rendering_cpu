#include <iterator>

#include <Scene.h>
#include <Composite.h>

#include <QDebug>

Scene::Scene() : _sceneObjects(new ObjectsContainer) { }


std::size_t Scene::addObject(const std::shared_ptr<BaseObject> &object)
{
    return _sceneObjects->addObject(object);
}


void Scene::deleteObject(const std::size_t id)
{
    _sceneObjects->deleteObject(id);
}


std::shared_ptr<BaseObject> Scene::getObject(const std::size_t id)
{
    return _sceneObjects->getObject(id);
}

std::shared_ptr<Composite> Scene::getComposite()
{
    auto composite = std::make_shared<Composite>(_sceneObjects->getObjects());
    return composite;
}

SceneIterator Scene::begin()
{
    return _sceneObjects->begin();
}


SceneIterator Scene::end()
{
    return _sceneObjects->end();
}
