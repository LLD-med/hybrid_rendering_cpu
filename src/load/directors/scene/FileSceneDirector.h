#ifndef FILESCENEDIRECTOR_H
#define FILESCENEDIRECTOR_H

#include <BaseSceneDirector.h>
#include "FileSurfaceModelLoader.h"

class FileSceneDirector : public BaseSceneDirector
{
public:
    FileSceneDirector();
    explicit FileSceneDirector(std::shared_ptr<BaseSceneBuilder> &builder);
//    ~FileSceneDirector() = default;
    virtual ~FileSceneDirector() {}


    std::shared_ptr<Scene> create(std::shared_ptr<BaseLoader> &loader) override;

protected:
    virtual void createModels(std::shared_ptr<BaseLoader> &loader) override;
    virtual void createCameras(std::shared_ptr<BaseLoader> &loader) override;

	std::shared_ptr<BaseSceneBuilder> _builder;
};

#endif // FILESCENEDIRECTOR_H
