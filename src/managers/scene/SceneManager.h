#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <BaseManager.h>
#include <Scene.h>
#include <Camera.h>

class SceneManager : public BaseManager
{
public:
    SceneManager();
    SceneManager(const SceneManager &scene) = delete;
    SceneManager &operator = (const SceneManager &scene) = delete;

    ~SceneManager() = default;

    std::shared_ptr<Scene> getScene() const;
    std::shared_ptr<BaseObject> getObject(const size_t id) { return _scene->getObject(id); };
    std::shared_ptr<Composite> getComposite() { return _scene->getComposite(); };
//    std::shared_ptr<Composite> getVisibleObjects() { return _scene->getSceneObject

    size_t addObject(const std::shared_ptr<BaseObject> &object);
    void deleteCamera(const size_t id);
    void setScene(std::shared_ptr<Scene> &scene);

private:
    std::shared_ptr<Scene> _scene;
};


#endif // SCENEMANAGER_H
