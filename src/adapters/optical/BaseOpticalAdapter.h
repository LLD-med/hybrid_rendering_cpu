#ifndef BASEOPTICALADAPTER_H
#define BASEOPTICALADAPTER_H

#include <BaseAdapter.h>
#include <BaseObject.h>
#include "Vector.hpp"
#include <QImage>

class BaseOpticalAdapter: public BaseAdapter
{
public:
    virtual ~BaseOpticalAdapter() = default;

    void setTexture(QImage &texture) { _texture = texture; }
    void setColor(VecD &color) { _color = color; flag = 1; }
    void setCoeff(VecD &coeffs) { _coeffs = coeffs; flag = 2; }

    virtual void setAdaptee(std::shared_ptr<BaseObject> adaptee) = 0;
    virtual void request() = 0;

protected:
    int flag = 0;
    QImage _texture;
    VecD _color;
    VecD _coeffs;
};

#endif // BASEOPTICALADAPTER_H
