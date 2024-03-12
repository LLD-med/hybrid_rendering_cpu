#ifndef VECTOR_H
#define VECTOR_H

#include <stdarg.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "BaseVector.h"
#include "Iterator.hpp"
#include "ConstIterator.h"

using namespace std;

enum VecElemId
{
    X = 0,
    Y = 1,
    Z = 2,
    W = 3,
};

using VecI = Vector<int>;
using VecF = Vector<float>;
using VecD = Vector<double>;


template<typename Type>
class Vector: public BaseVector
{
public:
    friend class Iterator<Type>;
    friend class ConstIterator<Type>;

    Vector();
    explicit Vector(int len);
    Vector(int len, Type* array);
    Vector(int len, Type vector, ...);
    Vector(initializer_list<Type> args);
//    explicit Vector(const Vector<Type> &vector);
    Vector(const Vector<Type> &vector);
    Vector(Vector<Type>&& vector) noexcept;

    virtual ~Vector();

    Vector<Type> &operator =(const Vector<Type> &vector);
    Vector<Type> &operator =(initializer_list<Type> args);
    Vector<Type> &operator =(Vector<Type> &&vector);

    bool setItem(int index, const Type &item);
    Type &getItem(int index);
    const Type &getItem(int index) const;

    Type &operator [](int index);
    const Type &operator [](int index) const;

    Type getLength() const;
    int  getSize() const noexcept override;
    bool isEmpty() const noexcept override;

    bool isZero() const; // проверка на нулевой вектор
    bool isSingle() const; // проверка единичный вектор

    bool isCollinear(const Vector<Type>&) const;
    bool isOrthgonal(const Vector<Type> &) const;

    Vector<Type> getSingle() const; // нормированием вектора

    Vector<Type> neg() const;
    Vector<Type> operator-() const;

    // Сумма вектора и числа
    template<typename U>
    decltype(auto) operator +(const U &) const;
    Vector<Type>  &operator +=(const Type &);
    template<typename U>
    decltype(auto) sumNum(const U &) const;
    Vector<Type>  &sumNumEqual(const Type &);

    // Сумма двух векторов
    template<typename U>
    decltype(auto) operator +(const Vector<U> &) const;
    Vector<Type> operator +(const Vector<Type> &) const;
    Vector<Type> &operator +=(const Vector<Type> &);
    template<typename U>
    decltype(auto) sum(const Vector<U> &) const;
    Vector<Type>  &sumEqual(const Vector<Type> &);

    // Разность вектора и числа
    template<typename U>
    decltype(auto) operator -(const U &) const;
    Vector<Type>  &operator -=(const Type &);
    template<typename U>
    decltype(auto) subNum(const U &) const;
    Vector<Type>  &subNumEqual(const Type &);

    // Разность двух векторов
    template<typename U>
    decltype(auto) operator -(const Vector<U> &) const;
    Vector<Type> operator -(const Vector<Type> &) const;
    Vector<Type>  &operator -=(const Vector<Type> &);
    template<typename U>
    decltype(auto) sub(const Vector<U> &) const;
    Vector<Type>  &subEqual(const Vector<Type> &);
    Vector<Type> operator -();
    Vector<Type> reverse();

    // Умножение на число
//    template<typename U>
//    decltype(auto) operator *(const U &number) const;
    Vector<Type> operator *(const Type &number) const;
    Vector<Type> &operator *=(const Type &number);
    template<typename U>
    decltype(auto) mulNum(const U &number) const;
    Vector<Type> &mulNumEqual(const Type &number);

    //Умножение элементов двух веткоров
    template<typename U>
    decltype(auto) operator ^(const Vector<U> &) const;
    Vector<Type> operator ^(const Vector<Type> &) const;
    Vector<Type> &operator ^=(const Vector<Type>&);
    template<typename U>
    decltype(auto) mulElems(const Vector<U> &) const;
    Vector<Type>  &mulElemsEqual(const Vector<Type> &);

    // Скалярное произведение
    template<typename U>
    auto operator *(const Vector<U> &) const;
    Type  operator *=(const Vector<Type> &);
    template<typename U>
    auto ScalarProd(const Vector<U> &) const;
    Type ScalarProd(const Vector<Type> &) const;
    Type  ScalarProdEqual(const Vector<Type> &);

    // Векторное произведение
    template<typename U>
    decltype(auto) operator &(const Vector<U> &) const;
    Vector<Type> &operator &=(const Vector<Type> &);
    template<typename U>
    decltype(auto) VectorProd(const Vector<U> &) const;
    Vector<Type> VectorProd(const Vector<Type> &) const;
    Vector<Type> &VectorProdEqual(const Vector<Type> &);

    // Деление вектора на число
    template<typename U>
    decltype(auto) operator /(const U& number) const;
    Vector<Type>  &operator /=(const Type& number);
    template<typename U>
    decltype(auto) divNum(const U&) const;
    Vector<Type>  &divNumEqual(const Type& number);

    // Деление двух векторов
    template<typename U>
    decltype(auto) operator /(const Vector<U>&) const;
    Vector<Type>  &operator /=(const Vector<Type>&);
    template<typename U>
    decltype(auto) div(const Vector<U>&) const;
    Vector<Type>  &divEqual(const Vector<Type>&);

    // Логические операции
    bool operator ==(const Vector<Type> &) const;
    bool operator !=(const Vector<Type> &) const;

    // угол между векторами
    double angleBetweenVectors(const Vector<Type>&) const;

    Iterator<Type> begin() noexcept;
    Iterator<Type> end() noexcept;

    ConstIterator<Type> begin() const noexcept;
    ConstIterator<Type> end() const noexcept;
    ConstIterator<Type> cbegin() const noexcept;
    ConstIterator<Type> cend() const noexcept;

    // новое
    Type &getX();
    Type &getY();
    Type &getZ();
    Type &getW();

    const Type &getX() const;
    const Type &getY() const;
    const Type &getZ() const;
    const Type &getW() const;

    void setX(Type x);
    void setY(Type y);
    void setZ(Type z);
    void setW(Type w);

    Vector<Type> VecNormalize() const;

    Vector<Type> VecRefract(Vector<Type> &direction, Vector<Type> &normal, double eta);
    Vector<Type> VecReflect(Vector<Type> &direction, Vector<Type> &normal);
    Vector<Type>& VecSaturate();
    Vector<Type> HadamardProd(const Vector<Type> &vec);

    Vector<Type> VecProjection(const Vector<Type> &b);

    double AngleBetweenVecs(const Vector<Type> b);

protected:
    Type sumValue();
    void allocNewVectorMem(int amount);
private:
    shared_ptr<Type[]> values; // Type[] - передача болле сложных типов (классов, объектов)
};

// создан для быстрого вывода вектора
template<typename Type>
ostream& operator <<(ostream& os, const Vector<Type>& vec)
{
    Iterator<Type> iter(vec);
    os << '(';
    for (; iter; iter++)
        if (iter + 1)
            os << *iter <<  ", ";
        else
            os << *iter;
    os << ')';

    return os;
}

#endif // VECTOR_H
