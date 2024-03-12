#ifndef BASESCENEDIRECTOR_H
#define BASESCENEDIRECTOR_H

#include <SceneBuilder.h>
#include <BaseLoader.h>

class BaseSceneDirector
{
public:
    virtual std::shared_ptr<Scene> create(std::shared_ptr<BaseLoader> &loader) = 0;

protected:
    virtual void createModels(std::shared_ptr<BaseLoader> &loader) = 0;
    virtual void createCameras(std::shared_ptr<BaseLoader> &loader) = 0;
};

#endif // BASESCENEDIRECTOR_H
