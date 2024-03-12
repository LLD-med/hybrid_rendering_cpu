#ifndef FILESURFACEMODELDIRECTOR_H
#define FILESURFACEMODELDIRECTOR_H

#include <BaseModelDirector.h>
#include <SurfaceModelBuilder.h>

class FileSurfaceModelDirector : public BaseModelDirector
{
public:
    FileSurfaceModelDirector();
    explicit FileSurfaceModelDirector(std::shared_ptr<BaseSurfaceModelBuilder> &builder);

    ~FileSurfaceModelDirector() override = default;

//    std::shared_ptr<BaseObject> create(std::shared_ptr<BaseLoader> &loader) override;
    std::shared_ptr<BaseObject> create(std::shared_ptr<BaseLoader> loader) override;
protected:
    std::shared_ptr<BaseSurfaceModelBuilder> _builder;
};

#endif // FILESURFACEMODELDIRECTOR_H
