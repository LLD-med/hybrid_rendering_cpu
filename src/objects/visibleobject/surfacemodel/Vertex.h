#ifndef VERTEX_H
#define VERTEX_H

//#include "Vector.hpp"
#include "Vector.hpp"

class Vertex
{
public:
    Vertex() = default;
//    Vertex(VecD pos, VecD norm, VecD color, float u, float v) :
    Vertex(VecD &pos, VecD &norm, VecD &color, double u, double v) :
        _position(pos), _normal(norm), _color(color), _u(u), _v(v) { }

    void setPosition(const VecD &pos);
    void setNormal(const VecD &norm);
    void setColor(const VecD &color);
    void setU(const double &new_u);
    void setV(const double &new_v);
    void setInvW(const double &new_w);

    VecD getPosition() const;
    VecD getNormal() const;
    VecD getColor() const;
    double getU() const;
    double getV() const;
    double getInvW() const;

private:
    VecD _position;
    VecD _normal;
    VecD _color;

    double _u, _v;
    double _invW = 1.;
};

#endif // VERTEX_H
