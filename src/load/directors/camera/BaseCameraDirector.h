#ifndef BASECAMERADIRECTOR_H
#define BASECAMERADIRECTOR_H

#include <BaseDirector.h>
#include <BaseLoader.h>
#include <BaseCameraBuilder.h>
#include <BaseObject.h>

class BaseCameraDirector : public BaseDirector
{
public:
    virtual std::shared_ptr<BaseObject> create(std::shared_ptr<BaseLoader> &loader) = 0;
};

#endif // BASECAMERADIRECTOR_H
