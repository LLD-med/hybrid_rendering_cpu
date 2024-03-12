#ifndef CAMERACOMMAND_H
#define CAMERACOMMAND_H

#include <memory>
#include <cstddef>

#include "BaseCommand.h"

using ID = std::shared_ptr<std::size_t>;

class CameraCommand : public BaseCommand
{
    virtual void setAdapter() override;
};

class AddCameraFull: public CameraCommand
{
    using Action = size_t(CamerasManager::*)(const VecD &location, const VecD &direction);
public:
    AddCameraFull(const ID &id, const VecD &location, const VecD &direction);

	virtual void execute() override;

private:
    ID _id;
    VecD _location;
    VecD _direction;

    Action _method;
};

class AddCamera: public CameraCommand
{
    using Action = size_t(CamerasManager::*)(int width, int height);
public:
    AddCamera(const ID &id, int width, int height);

    virtual void execute() override;

private:
    ID _id;
    int _width;
    int _height;

    Action _method;
};


class GetMainCamera : public CameraCommand
{
    using Action = std::shared_ptr<Camera>(CamerasManager::*)() const;
public:
    explicit GetMainCamera(std::shared_ptr<Camera> &camera);

    ~GetMainCamera() override = default;

    void execute() override;

private:
    std::shared_ptr<Camera> &_camera;
    Action _method;
};

class SetCamera: public CameraCommand
{
    using Action = void(CamerasManager::*)(size_t id);
public:
    explicit SetCamera(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};


class RemoveCamera: public CameraCommand
{
    using Action = void(CamerasManager::*)(const size_t id);
public:
    RemoveCamera(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};

// переделать в совместную команду
class TransformCamera: public CameraCommand
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &dx, const double &dy, const double &dz,
                                             const double &ox, const double &oy);
public:
    TransformCamera(const std::shared_ptr<Camera> camera, const double dx, const double dy,
                    const double dz, const double ox, const double oy);

    virtual void execute() override;

private:
    std::shared_ptr<Camera> _camera;
    double _dx, _dy, _dz, _ox, _oy;
    Action _method;
};

class MoveCamera: public CameraCommand
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object,
                                             const double &dx, const double &dy, const double &dz);
public:
    MoveCamera(const std::shared_ptr<Camera> camera, const double dx, const double dy, const double dz);

    virtual void execute() override;

private:
    std::shared_ptr<Camera> _camera;
    double _dx, _dy, _dz;
    Action _method;
};

class RotateCamera: public CameraCommand
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &ox, const double &oy, const double &oz);
public:
    RotateCamera(const std::shared_ptr<Camera> camera, const double ox, const double oy, const double oz);

    virtual void execute() override;

private:
    std::shared_ptr<Camera> _camera;
    double _ox, _oy, _oz;
    Action _method;
};


#endif //CAMERACOMMAND_H
