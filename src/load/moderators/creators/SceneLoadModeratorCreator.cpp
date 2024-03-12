#include <SceneLoadModeratorCreator.h>
#include <FileSceneDirector.h>

std::shared_ptr<SceneLoadModerator> SceneLoadModeratorCreator::createModerator()
{
    if (nullptr == _moderator)
        createInstance();

    return _moderator;
}

void SceneLoadModeratorCreator::createInstance()
{
    static std::shared_ptr<SceneLoadModerator> moderator;

    if (!moderator)
    {
//		auto loader = std::shared_ptr<BaseLoader>(new FileCarcassModelLoader());
//        auto loader = std::make_shared<FileCarcassModelLoader>();
        auto loader = std::make_shared<FileSurfaceModelLoader>();
//		auto director = std::shared_ptr<BaseSceneDirector>(new FileSceneDirector());
        auto director = std::make_shared<FileSceneDirector>();
		moderator = std::make_shared<SceneLoadModerator>(director, loader);
    }

    _moderator = moderator;
}


