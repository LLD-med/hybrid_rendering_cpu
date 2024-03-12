#ifndef MODELPROPERTYCOMMAND_H
#define MODELPROPERTYCOMMAND_H

#include "BaseCommand.h"

using ID = std::shared_ptr<std::size_t>;

class ModelPropertyCommand : public BaseCommand
{
    virtual void setAdapter() override;
};

class ChangeModelColor: public ModelPropertyCommand
{
    using Action = void(PropertyManager::*)(const std::shared_ptr<BaseObject> &object,
                                            const double &cx, const double &cy, const double &cz);
public:
    ChangeModelColor(const std::shared_ptr<BaseObject> model,
                     const double cx, const double cy, const double cz);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _model;
    double _cx; double _cy; double _cz;
    Action _method;
};

class ChangeModelTexture: public ModelPropertyCommand
{
    using Action = void(PropertyManager::*)(const std::shared_ptr<BaseObject> &object,
                                            QImage &texture);
public:
    ChangeModelTexture(const std::shared_ptr<BaseObject> model,
                       QImage texture);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _model;
    QImage _texture;
    Action _method;
};

class ChangeModelProperties: public ModelPropertyCommand
{
    using Action = void(PropertyManager::*)(const std::shared_ptr<BaseObject> &object,
                                            const double &px, const double &py, const double &pz);
public:
    ChangeModelProperties(const std::shared_ptr<BaseObject> model,
                          const double px, const double py, const double pz);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _model;
    double _px; double _py; double _pz;
    Action _method;
};



#endif // MODELPROPERTYCOMMAND_H
