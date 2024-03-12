#ifndef LIGHTPROPERTYCOMMAND_H
#define LIGHTPROPERTYCOMMAND_H

#include "BaseCommand.h"

using ID = std::shared_ptr<std::size_t>;

class LightPropertyCommand : public BaseCommand
{
    virtual void setAdapter() override;
};

class ChangeLightColor: public LightPropertyCommand
{
    using Action = void(PropertyManager::*)(const std::shared_ptr<BaseObject> &object,
                                            const double &cx, const double &cy, const double &cz);
public:
    ChangeLightColor(const std::shared_ptr<Light> light,
                     const double cx, const double cy, const double cz);

    virtual void execute() override;

private:
    std::shared_ptr<Light> _light;
    double _cx; double _cy; double _cz;
    Action _method;
};

class ChangeLightIntensity: public LightPropertyCommand
{
    using Action = void(PropertyManager::*)(const std::shared_ptr<BaseObject> &object,
                                            const double &px, const double &py, const double &pz);
public:
    ChangeLightIntensity(const std::shared_ptr<Light> light,
                         const double px, const double py, const double pz);

    virtual void execute() override;

private:
    std::shared_ptr<Light> _light;
    double _px; double _py; double _pz;
    Action _method;
};

#endif // LIGHTPROPERTYCOMMAND_H
