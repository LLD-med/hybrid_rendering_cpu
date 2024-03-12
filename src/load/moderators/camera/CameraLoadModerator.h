#ifndef CAMERALOADMODERATOR_H
#define CAMERALOADMODERATOR_H

#include <BaseLoadModerator.h>
#include <BaseCameraDirector.h>

class CameraLoadModerator : public BaseLoadModerator
{
public:
    explicit CameraLoadModerator(std::shared_ptr<BaseCameraDirector> director, std::shared_ptr<BaseLoader> loader);
    ~CameraLoadModerator() = default;

    std::shared_ptr<BaseObject> create() override;
    virtual void setFileName(std::string &fileName) override;

private:
    std::shared_ptr<BaseLoader> _loader;
    std::shared_ptr<BaseCameraDirector> _director;
};

#endif // CAMERALOADMODERATOR_H
