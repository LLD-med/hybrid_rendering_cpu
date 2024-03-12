#ifndef INTERSECTIONDATA_H
#define INTERSECTIONDATA_H

#include "Vector.hpp"
#include "gBuffer.h"

class IntersectionData
{
public:
    IntersectionData() = default;
    IntersectionData(gBuffer &bufferData, int x, int y)
    {
        _position = bufferData.getPosition(x, y);
        _normal = bufferData.getNormal(x, y);
        _color = bufferData.getColor(x, y);
        _properties = bufferData.getProperties(x, y);
        t_coef = 0.;
    }

    void setPosition(VecD &pos);
    void setNormal(VecD &norm);
    void setColor(VecD &color);
    void setProperties(VecD &properties);
    void setT(double value);

    void setPosition(VecD pos);
    void setNormal(VecD norm);
    void setColor(VecD color);
    void setProperties(VecD properties);

    VecD getPosition() const;
    VecD getNormal() const;
    VecD getColor() const;
    VecD getProperties() const;

    double getProperty(int type) const;
    double getT() const;
private:
    VecD _position;
    VecD _normal;
    VecD _color;
    VecD _properties;

    double t_coef;
};

#endif // INTERSECTIONDATA_H
