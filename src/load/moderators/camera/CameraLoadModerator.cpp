#include <CameraLoadModerator.h>
#include <CameraBuilder.h>
#include "exceptions/Exceptions.hpp"

CameraLoadModerator::CameraLoadModerator(std::shared_ptr<BaseCameraDirector> director, std::shared_ptr<BaseLoader> loader)
{
    _director = director;
    _loader = loader;
}

std::shared_ptr<BaseObject> CameraLoadModerator::create()
{
    std::shared_ptr<Camera> camera_sh_ptr;

    try
    {
        camera_sh_ptr = std::dynamic_pointer_cast<Camera>(_director->create(_loader));
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

    return std::shared_ptr<BaseObject>(camera_sh_ptr);
}

void CameraLoadModerator::setFileName(std::string &fileName)
{
    _loader->setFileName(fileName);
}
