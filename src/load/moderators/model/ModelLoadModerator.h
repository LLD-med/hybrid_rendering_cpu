#ifndef MODELLOADMODERATOR_H
#define MODELLOADMODERATOR_H

#include <BaseLoadModerator.h>
#include <BaseModelDirector.h>
#include <BaseLoader.h>

class ModelLoadModerator : public BaseLoadModerator
{
public:
    ModelLoadModerator() = default;
    explicit ModelLoadModerator(std::shared_ptr<BaseModelDirector> director, std::shared_ptr<BaseLoader> loader);

    ~ModelLoadModerator() = default;

    std::shared_ptr<BaseObject> create() override;
    virtual void setFileName(std::string &fileName) override;

private:
    std::shared_ptr<BaseLoader> _loader;
    std::shared_ptr<BaseModelDirector> _director;
};

#endif // MODELLOADMODERATOR_H
