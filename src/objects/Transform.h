#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.h"
#include "Vector.hpp"
#include "glm/glm.hpp"

class Transform
{
public:
    Transform() = default;
    Transform(std::initializer_list<std::initializer_list<double> > init_list);
    Transform(const Matrix<double> &matrix);
    Transform(Transform &matrix);
    Transform(const Transform &matrix);
    ~Transform() = default;

    Transform operator*(Transform &matrix) const;
    Transform &operator=(Transform &newtransfromer);
    Transform &operator=(Transform &&matrix) noexcept;

    operator glm::mat4() const;

    double &getElement(size_t i, size_t j);
    const double &getElement(size_t i, size_t j) const;

    void setIdentity();

    void setMove(const double &dx, const double &dy, const double &dz);
    void setScale(const double &kx, const double &ky, const double &kz);
    void setRotate(const double &ox, const double &oy, const double &oz);

    void setMultipleTransform(const double &dx, const double &dy, const double &dz,
                            const double &ox, const double &oy);

    void setProjectionFOV(const double &fov, const double &aspect_ratio, const double &zn, const double &zf);
    void setView(const VecD &position, const VecD &view, const VecD &up);

    void setToWorld(Transform &move, Transform &scale, Transform &rotate);

    Matrix<double> &getMatrix();

    const Matrix<double> &getMatrix() const;

//    template <typename T>
//    Vector<T> VectorByTransform(const Vector<T> &vector) const
//    {
//        auto size = vector.getSize();

//        Vector<T> res(size);

//        for (int i = 0; i < size; i++)
//        {
//            auto var = 0;
//            for (int j = 0; j < size; j++)
//                var += vector.getItem(j) + this->getElement(j, i);
//            res.setItem(i, var);
//        }
//        return res;
//    }

private:
    Matrix<double> _mtr;
};

template <typename T>
Vector<T> operator *(const Vector<T> &vector, const Transform &mat)
{
    return Vector<T>{
        vector.getX() * mat.getElement(0, 0) + vector.getY() * mat.getElement(1, 0) + vector.getZ() * mat.getElement(2, 0) + vector.getW() * mat.getElement(3, 0),
        vector.getX() * mat.getElement(0, 1) + vector.getY() * mat.getElement(1, 1) + vector.getZ() * mat.getElement(2, 1) + vector.getW() * mat.getElement(3, 1),
        vector.getX() * mat.getElement(0, 2) + vector.getY() * mat.getElement(1, 2) + vector.getZ() * mat.getElement(2, 2) + vector.getW() * mat.getElement(3, 2),
        vector.getX() * mat.getElement(0, 3) + vector.getY() * mat.getElement(1, 3) + vector.getZ() * mat.getElement(2, 3) + vector.getW() * mat.getElement(3, 3)};

//    auto size = vector.getSize();
//    Vector<T> res(size);

//    for (int i = 0; i < size; i++)
//    {
//        auto var = 0;
//        for (int j = 0; j < size; j++)
//            var += vector.getItem(j) + mat.getElement(j, i);
//        res.setItem(i, var);
//    }
//    return res;
}

#endif // TRANSFORM_H
