#include "FileSurfaceModelLoader.h"
#include <ModelLoadModeratorCreator.h>
#include <FileSurfaceModelDirector.h>

std::shared_ptr<ModelLoadModerator> ModelLoadModeratorCreator::createModerator()
{
    if (nullptr == _moderator)
        createInstance();

    return _moderator;
}

void ModelLoadModeratorCreator::createInstance()
{
    static std::shared_ptr<ModelLoadModerator> moderator;

    if (!moderator)
    {
//		auto loader = std::shared_ptr<BaseLoader>(new FileCarcassModelLoader());
        auto loader = std::make_shared<FileSurfaceModelLoader>();
//		auto director = std::shared_ptr<BaseModelDirector>(new FileModelDirector());
        auto director = std::make_shared<FileSurfaceModelDirector>();
		moderator = std::make_shared<ModelLoadModerator>(director, loader);
    }

    _moderator = moderator;
}
