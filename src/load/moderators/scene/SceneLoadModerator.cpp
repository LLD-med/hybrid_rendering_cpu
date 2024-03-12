#include "SceneLoadModerator.h"
#include "exceptions/Exceptions.hpp"

SceneLoadModerator::SceneLoadModerator(std::shared_ptr<BaseSceneDirector> director, std::shared_ptr<BaseLoader> loader)
{
    _director = director;
    _loader = loader;
}

std::shared_ptr<Scene> SceneLoadModerator::create()
{
    std::shared_ptr<Scene> scene;

    try
    {
        scene = _director->create(_loader);
    }
    catch (SourceException &error)
    {
        std::string msg = "Error : Open file";
        throw SourceException(msg);
    }
    catch (std::exception &error)
    {
        std::string msg = "Error : Read model";
        throw SourceException(msg);
    }

    return scene;
}

void SceneLoadModerator::setDirector(std::shared_ptr<BaseSceneDirector> director)
{
    _director = director;
}

void SceneLoadModerator::setFileName(std::string &fileName)
{
    _loader->setFileName(fileName);
}
