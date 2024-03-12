#ifndef BASELOADMODERATOR_H
#define BASELOADMODERATOR_H

#include <memory>

#include <BaseObject.h>
#include <BaseLoader.h>

class BaseLoadModerator
{
public:
    BaseLoadModerator() = default;
    virtual ~BaseLoadModerator() = default;

    virtual std::shared_ptr<BaseObject> create() = 0;
    virtual void setFileName(std::string &fileName) = 0;
};

#endif // BASELOADMODERATOR_H
