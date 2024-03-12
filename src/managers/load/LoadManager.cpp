#include "LoadManager.h"

#include <QDebug>

std::shared_ptr<BaseObject> LoadManager::create(std::string &name)
{
    _moderator->setFileName(name);
    return _moderator->create();
}

std::shared_ptr<Scene> LoadManager::createScene(std::string &name)
{
    _sceneModerator->setFileName(name);
    return _sceneModerator->create();
}

void LoadManager::setModerator(std::shared_ptr<BaseLoadModerator> moderator)
{
    _moderator = moderator;
}

void LoadManager::setSceneModerator(std::shared_ptr<SceneLoadModerator> moderator)
{
    _sceneModerator = moderator;
}
