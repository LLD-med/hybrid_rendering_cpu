#include "Transform.h"

Transform::Transform(std::initializer_list<std::initializer_list<double>> init_list)
{
    _mtr = Matrix(init_list);
}

Transform::Transform(const Matrix<double> &matrix)
{
    _mtr = matrix;
}

Transform::Transform(Transform &matrix)
{
    _mtr = matrix.getMatrix();
}

Transform::Transform(const Transform &matrix)
{
    _mtr = matrix.getMatrix();
}

Transform &Transform::operator=(Transform &&matrix) noexcept
{
    _mtr = matrix.getMatrix();
    return *this;
}

Transform::operator glm::mat4() const
{;
    return glm::mat4(
                _mtr[0][0], _mtr[0][1], _mtr[0][2], _mtr[0][3],
                _mtr[1][0], _mtr[1][1], _mtr[1][2], _mtr[1][3],
                _mtr[2][0], _mtr[2][1], _mtr[2][2], _mtr[2][3],
                _mtr[3][0], _mtr[3][1], _mtr[3][2], _mtr[3][3]);
}

Transform Transform::operator*(Transform &t) const
{
    return Transform(_mtr * t.getMatrix());
}

Transform &Transform::operator=(Transform &t)
{
    _mtr = t.getMatrix();
    return *this;
}

double &Transform::getElement(size_t i, size_t j)
{
    return _mtr[i][j];
}

const double &Transform::getElement(size_t i, size_t j) const
{
    return _mtr[i][j];
//    return this->_mtr[i][j];
}

void Transform::setIdentity()
{
    _mtr = {{1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}};
}

void Transform::setMove(const double &dx, const double &dy, const double &dz)
{
    _mtr = {{ 1,  0,  0, 0},
            { 0,  1,  0, 0},
            { 0,  0,  1, 0},
            {dx, dy, dz, 1}};
}

void Transform::setScale(const double &kx, const double &ky, const double &kz)
{
    _mtr = {{kx,  0,  0, 0},
            { 0, ky,  0, 0},
            { 0,  0, kz, 0},
            { 0,  0,  0, 1}};
}

void Transform::setRotate(const double &ox, const double &oy, const double &oz)
{
    Matrix<double> mtr_ox = {{1,        0,        0,        0},
                             {0,     cos(ox), -sin(ox),     0},
                             {0,     sin(ox),  cos(ox),     0},
                             {0,        0,        0,        1}};

    Matrix<double> mtr_oy = {{ cos(oy), 0, sin(oy), 0},
                             {    0,    1,    0,    0},
                             {-sin(oy), 0, cos(oy), 0},
                             {    0,    0,    0,    1}};

    Matrix<double> mtr_oz = {{ cos(oz), -sin(oz),     0,        0},
                             { sin(oz),  cos(oz),     0,        0},
                             {    0,        0,        1,        0},
                             {    0,        0,        0,        1}};

    _mtr = mtr_ox * mtr_oy * mtr_oz;
}

void Transform::setMultipleTransform(const double &dx, const double &dy, const double &dz, const double &ox, const double &oy)
{
    _mtr = {{ dx,  dy,  dz, ox,  oy}};
}

void Transform::setProjectionFOV(const double &fov, const double &aspect_ratio, const double &zn, const double &zf)
{
    double fov_rad = fov * M_PI / 180.;
    double h = 1. / std::tan(fov_rad * 0.5);
    double w = h / aspect_ratio;
    double q = zf / (zf - zn);

    _mtr = {{w, 0, 0, 0},
            {0, h, 0, 0},
            {0, 0, q, 1},
            {0, 0, -zn * q, 0}};
}

void Transform::setView(const VecD &position, const VecD &view, const VecD &up)
{
    VecD forward = (view - position).VecNormalize();
//    VecD forward = (view - position);
//    forward.VecNormalize();
    VecD right = (up.VectorProd(forward)).VecNormalize();
    VecD newUp = forward.VectorProd(right);

    _mtr = {{right.getX(), newUp.getX(), forward.getX(), 0},
            {right.getY(), newUp.getY(), forward.getY(), 0},
            {right.getZ(), newUp.getZ(), forward.getZ(), 0},
            {-right.ScalarProd(position), -newUp.ScalarProd(position), -forward.ScalarProd(position), 1}};
}

void Transform::setToWorld(Transform &move, Transform &scale, Transform &rotate)
{
    _mtr = scale.getMatrix() * rotate.getMatrix() * move.getMatrix();
}

Matrix<double> &Transform::getMatrix()
{
    return _mtr;
}

const Matrix<double> &Transform::getMatrix() const
{
    return _mtr;
}

Transform operator *(Transform &mat1, Transform &mat2)
{
    return Transform(mat1.getMatrix() * mat2.getMatrix());
}

//template <typename T>
//Vector<T> Transform::VectorByTransform(const Vector<T> &vector) const
//{
//    auto size = vector.getSize();

//    Vector<T> res(size);

//    for (int i = 0; i < size; i++)
//    {
//        auto var = 0;
//        for (int j = 0; j < size; j++)
//            var += vector.get_elem(j) + this->getElement(j, i);
//        res.set_elem(i, var);
//    }
//    return res;
//}
