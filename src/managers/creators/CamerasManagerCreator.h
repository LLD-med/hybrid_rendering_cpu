#ifndef CAMERASMANAGERCREATOR_H
#define CAMERASMANAGERCREATOR_H

#include <memory>
#include <CamerasManager.h>

class CamerasManagerCreator
{
public:
    std::shared_ptr<CamerasManager> createManager();

private:
    void createInstance();
    std::shared_ptr<CamerasManager> _manager;
};

#endif // CAMERASMANAGERCREATOR_H
