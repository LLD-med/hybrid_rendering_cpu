#ifndef BASEMODELDIRECTOR_H
#define BASEMODELDIRECTOR_H

#include <BaseDirector.h>
#include <SurfaceModelBuilder.h>
#include <BaseLoader.h>
//#include <FileCarcassModelLoader.h>

class BaseModelDirector : public BaseDirector
{
public:
//    virtual std::shared_ptr<BaseObject> create(std::shared_ptr<BaseLoader> &loader) = 0;
    virtual std::shared_ptr<BaseObject> create(std::shared_ptr<BaseLoader> loader) = 0;
};

#endif // BASEMODELDIRECTOR_H
