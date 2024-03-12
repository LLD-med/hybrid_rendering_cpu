#ifndef LIGHTCOMMAND_H
#define LIGHTCOMMAND_H

#include <memory>
#include <cstddef>

#include "BaseCommand.h"

using ID = std::shared_ptr<std::size_t>;

class LightCommand : public BaseCommand
{
    virtual void setAdapter() override;
};

class AddLight: public LightCommand
{
    using Action = size_t(LightsManager::*)(const VecD &location, const VecD &direction, lightType type);
public:
    AddLight(const ID &id, const VecD &location, const VecD &direction, lightType type);

    virtual void execute() override;

private:
    ID _id;
    lightType _type;
    VecD _location;
    VecD _direction;
    VecD _intens;

    Action _method;
};

class RemoveLight: public LightCommand
{
    using Action = void(LightsManager::*)(const size_t id);
public:
    RemoveLight(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};

class SetLight: public LightCommand
{
    using Action = void(LightsManager::*)(size_t id);
public:
    explicit SetLight(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};

class GetLight: public LightCommand
{
    using Action = std::shared_ptr<Light>(LightsManager::*)() const;
public:
    explicit GetLight(std::shared_ptr<Light> &light);

    ~GetLight() override = default;

    virtual void execute() override;

private:
    std::shared_ptr<Light> &_light;
    Action _method;
};

class GetLightByInd: public LightCommand
{
    using Action = std::shared_ptr<Light>(LightsManager::*)(const std::size_t id) const;
public:
    explicit GetLightByInd(std::shared_ptr<Light> &light, const std::size_t id);

    virtual void execute() override;
private:
    std::size_t _id;
    std::shared_ptr<Light> &_light;
    Action _method;
};



class TransformLight: public LightCommand
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &dx, const double &dy, const double &dz,
                                             const double &ox, const double &oy);
public:
    TransformLight(const std::shared_ptr<Light> light, const double dx, const double dy,
                    const double dz, const double ox, const double oy);

    virtual void execute() override;

private:
    std::shared_ptr<Light> _light;
    double _dx, _dy, _dz, _ox, _oy;
    Action _method;
};



#endif // LIGHTCOMMAND_H
