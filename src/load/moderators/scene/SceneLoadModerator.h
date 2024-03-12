#ifndef SCENELOADMODERATOR_H
#define SCENELOADMODERATOR_H

#include "BaseSceneDirector.h"
//#include "SceneBuilder.h"

class SceneLoadModerator
{
public:
    SceneLoadModerator() = default;
    explicit SceneLoadModerator(std::shared_ptr<BaseSceneDirector> director, std::shared_ptr<BaseLoader> loader);

//    ~SceneLoadModerator() = default;
    virtual ~SceneLoadModerator() {}

    std::shared_ptr<Scene> create();
    virtual void setDirector(std::shared_ptr<BaseSceneDirector> director);
    virtual void setFileName(std::string &fileName);

private:
    std::shared_ptr<BaseLoader> _loader;
    std::shared_ptr<BaseSceneDirector> _director;
};

#endif //SCENELOADMODERATOR_H
