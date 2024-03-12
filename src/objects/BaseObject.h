#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include "Vector.hpp"
#include <memory>
#include <vector>
#include <QDebug>

#include "Transform.h"

class BaseObject;

using ObjIterator = std::vector<std::shared_ptr<BaseObject>>::iterator;

class BaseObject
{
public:
    BaseObject() { _id = _nextId++; rotation.setIdentity(); };
    virtual ~BaseObject() = default;

    virtual bool add(const std::shared_ptr<BaseObject> &) { return false; };
    virtual bool remove(const ObjIterator &) { return false; };

    virtual bool isVisible() { return false; };
	virtual bool isComposite() { return false; };

    virtual VecD getCenter() const = 0;

    virtual ObjIterator begin() { return ObjIterator(); };
    virtual ObjIterator end() { return ObjIterator(); };

    std::size_t getId() { return _id; }

    void setMoveCoefs(const double &x, const double &y, const double &z);
    void setScaleCoefs(const double &x, const double &y, const double &z);
    void setRotateCoefs(const double &x, const double &y, const double &z);

    Transform getObjToWorld();
    Transform getRotationMatrix();

//    void setRotationMatrix(Transform);

protected:
    std::size_t _id;
    static std::size_t _nextId;

    Transform rotation;

    double angle_x = 0., angle_y = 0., angle_z = 0.;
    double move_x = 0, move_y = 0, move_z = 0;
    double scale_x = 1., scale_y = 1., scale_z = 1.;
};

#endif //BASEOBJECT_H
