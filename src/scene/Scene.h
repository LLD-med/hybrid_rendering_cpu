#ifndef SCENE_H
#define SCENE_H

#include <Composite.h>
#include <Camera.h>
#include "ObjectsContainer.h"

class BaseObject;

using SceneIterator = std::vector<std::shared_ptr<BaseObject>>::iterator;

class Scene
{
public:
    Scene();
    ~Scene() = default;

    std::size_t addObject(const std::shared_ptr<BaseObject> &object);
    void deleteObject(const std::size_t id);

    std::shared_ptr<BaseObject> getObject(const std::size_t id);
    std::shared_ptr<Composite> getComposite();

    SceneIterator begin();
    SceneIterator end();
protected:
    std::shared_ptr<ObjectsContainer> _sceneObjects;

//    int _width, _height;
};

#endif //SCENE_H
