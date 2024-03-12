#include "SurfaceModel.h"
#include <ModelLoadModerator.h>
#include "exceptions/Exceptions.hpp"

#include <QDebug>

ModelLoadModerator::ModelLoadModerator(std::shared_ptr<BaseModelDirector> director, std::shared_ptr<BaseLoader> loader)
{
    _director = director;
    _loader = loader;
}

void ModelLoadModerator::setFileName(std::string &fileName)
{
    _loader->setFileName(fileName);
}

std::shared_ptr<BaseObject> ModelLoadModerator::create()
{
    std::shared_ptr<SurfaceModel> model_sh_ptr;

    try
    {
        model_sh_ptr = std::dynamic_pointer_cast<SurfaceModel>(_director->create(_loader));
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

    return std::shared_ptr<BaseObject>(model_sh_ptr);
}
