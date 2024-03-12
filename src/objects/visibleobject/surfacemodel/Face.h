#ifndef FACE_H
#define FACE_H

#include "Vertex.h"
#include "Vector.hpp"
//#include <vector>

class Face
{
public:
    Face() = default;
    Face(const Face &face) = default;
    ~Face() = default;

    Face(Vertex &v1, Vertex &v2, Vertex &v3);

    void setA(Vertex &a);
    void setB(Vertex &b);
    void setC(Vertex &c);
    void setNormal(VecD &norm);
    void setNormal(VecD norm);

    void setColorA(const VecD &color);
    void setColorB(const VecD &color);
    void setColorC(const VecD &color);

    Vertex getA() const;
    Vertex getB() const;
    Vertex getC() const;
    VecD getNormal() const;

private:
    Vertex _a, _b, _c;
    VecD _normal;
};

#endif // FACE_H
