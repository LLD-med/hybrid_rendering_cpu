#ifndef LIGHTSMANAGERCREATOR_H
#define LIGHTSMANAGERCREATOR_H

#include <memory>
#include <LightsManager.h>

class LightsManagerCreator
{
public:
    std::shared_ptr<LightsManager> createManager();

private:
    void createInstance();
    std::shared_ptr<LightsManager> _manager;
};


#endif // LIGHTSMANAGERCREATOR_H
