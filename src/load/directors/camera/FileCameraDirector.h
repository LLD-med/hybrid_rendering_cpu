#ifndef FILECAMERADIRECTOR_H
#define FILECAMERADIRECTOR_H


#include <BaseCameraDirector.h>
#include <FileSurfaceModelLoader.h>

class FileCameraDirector : public BaseCameraDirector
{
public:
    FileCameraDirector();
	explicit FileCameraDirector(std::shared_ptr<BaseCameraBuilder> builder);

    ~FileCameraDirector() override = default;

    std::shared_ptr<BaseObject> create(std::shared_ptr<BaseLoader> &loader) override;

protected:
	std::shared_ptr<BaseCameraBuilder> _builder;
};

#endif // FILECAMERADIRECTOR_H
