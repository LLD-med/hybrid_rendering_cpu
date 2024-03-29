#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <Vector.h>
#include "VectorExceptions.hpp"
#include <QDebug>

// Конструктор инициализации.
template<typename Type>
Vector<Type>::Vector()
{
    size = 0;
    allocNewVectorMem(size);
}

// Конструктор вектора нужной длины
template<typename Type>
Vector<Type>::Vector(int len)
{
    time_t curTime = time(NULL);
    if (len < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    size = len;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator = 0;
}

// Конструктор на основе массива.
template<typename Type>
Vector<Type>::Vector(int len, Type* array)
{
    time_t curTime = time(NULL);
    if (len <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (!array)
        throw InvalidCopyArrayPointer(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    size = len;
    allocNewVectorMem(size);
    if(!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> iterator(*this);
    for (int i = 0; iterator; i++, iterator++)
        *iterator = array[i];
}

// Конструктор на основе элементов.
template<typename Type>
Vector<Type>::Vector(int len, Type vector, ...)
{
    time_t currentTime = time(NULL);
    if (len < 1)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    size = len;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    va_list var;
    va_start(var, vector);
    for (; iterator; iterator++)
    {
        *iterator = vector;
        vector = va_arg(var, Type);
    }
    va_end(var);
}

// Конструктор с инициализацией.
template<typename Type>
Vector<Type>::Vector(std::initializer_list<Type> args)
{
    if (args.size() == 0)
    {
        Vector();
        return;
    }

    time_t currentTime = time(NULL);
    size = int(args.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    for (auto &currentItem : args)
    {
        *iterator = currentItem;
        iterator++;
    }
}

// Конструктор от вектора.
template<typename Type>
Vector<Type>::Vector(const Vector<Type> &vector)
{
    time_t currentTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iteratorTo(*this);
    Iterator<Type> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;
}

// Конструктор переносом.
template<typename Type>
Vector<Type>:: Vector(Vector<Type> &&vector) noexcept
{
    size = vector.size;
    allocNewVectorMem(size);
    values = vector.values;
    vector.values = nullptr;
}

// Деструктор.
template<typename Type>
Vector<Type>::~Vector()
{
    if (values)
        values.reset();
}

// Операторы присваивания
template<typename Type>
Vector<Type> &Vector<Type>::operator =(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> iteratorTo(*this);
    Iterator<Type> iteratorFrom(vector);
    for (; iteratorTo; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator =(initializer_list<Type> args)
{
    time_t currentTime = time(NULL);
    size = int(args.size());
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    for (auto &currentItem : args)
    {
        *iterator = currentItem;
        iterator++;
    }

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator =(Vector<Type> &&vector)
{
    time_t curTime = time(NULL);
    size = vector.size;
    allocNewVectorMem(size);
    if (!values)
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    values = vector.values;
    vector.values = nullptr;

    return *this;
}

// Получение элемента по индексу.
template<typename Type>
Type &Vector<Type>::getItem(int index) {
    time_t currentTime = time(NULL);
    if (index < 0 || index >= size)
        throw IndexVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    for (int i = 0; i < index; i++, iterator++);

    return *iterator;
}

// Получение элемента по индексу Const.
template<typename Type>
const Type &Vector<Type>::getItem(int index) const {
    time_t currentTime = time(NULL);
    if (index < 0 || index >= size)
        throw IndexVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    for (int i = 0; i < index; i++, iterator++) { }

    return *iterator;
}

template<typename Type>
int Vector<Type>::getSize() const noexcept
{
    return size;
}

template<typename Type>
bool Vector<Type>::isEmpty() const noexcept
{
    return bool(size);
}

// Установить значени по индексу
template<typename Type>
bool Vector<Type>::setItem (int index, const Type &item)
{
    bool res = true;
    if (index < 0 || index >= size)
            res = false;
    else
    {
        Iterator<Type> iterator(*this);
        for (int i = 0; i < index; i++, iterator++);
        (*iterator) = item;
    }
    return res;
}

// Оператор индексации.
template<typename Type>
Type &Vector<Type>::operator[] (int index)
{
    return getItem(index);
}

// Оператор индексации Const.
template<typename Type>
const Type &Vector<Type>::operator [](int index) const
{
    return getItem(index);
}

// Проверка на нулевой вектор - длина равная 0
template<typename Type>
bool Vector<Type>::isSingle() const
{
    if (fabs(getLength() - 1) < __DBL_EPSILON__)
        return true;
    return false;
}

// Проверка на единичный вектор - длина равная 1
template<typename Type>
bool Vector<Type>::isZero() const
{
    if (getLength() == 0)
        return true;
    return false;
}

// вычисление длины вектора
template<typename Type>
Type Vector<Type>::getLength() const
{
    time_t curTime = time(NULL);
    if (size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> iterator(*this);
    Type sum = 0.;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;
    sum = sqrt(sum);
    return sum;
}

// получение единичного вектора
template<typename Type>
Vector<Type> Vector<Type>::getSingle() const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> singleVector(*this);

    Type len = getLength();
    Iterator<Type> iterator(singleVector);

    for (; iterator; iterator++)
        *iterator /= len;
    return singleVector;
}

template <typename Type>
Vector<Type> Vector<Type>::neg() const
{
    Vector<Type> res(*this);

    for (int i = 0; i < size; i++)
        res[i] = -res[i];

    return res;
}

template <typename Type>
Vector<Type> Vector<Type>::operator-() const
{
    return neg();
}

// Опредление угла между векторами
template<typename Type>
double Vector<Type>::angleBetweenVectors(const Vector<Type> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (!this->getLength() || !vector.getLength())
        throw ZeroDivException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    double angle = (*this * vector) / (this->getLength() * vector.getLength());
    if (angle > 1) angle = 1.0;

    return acos(angle) * 180 / M_PI;
}

// Проверка на коллинерность вектора
template<typename Type>
bool Vector<Type>::isCollinear(const Vector<Type>& vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (angleBetweenVectors(vector) < 1e-05)
        return true;
    return false;
}

// Проверка на ортогональность вектора
template<typename Type>
bool Vector<Type>::isOrthgonal(const Vector<Type>& vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (fabs(angleBetweenVectors(vector) - 90) < __DBL_EPSILON__)
        return true;
    return false;
}

// Умножить на число
//template<typename Type>
//template<typename U>
//decltype(auto) Vector<Type>::operator *(const U &num) const
//{
//    time_t curTime = time(NULL);
//    if (size <= 0)
//        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

//    Vector<decltype((*this)[0] * num)> newVector(*this);
//    Iterator<Type> iterator(newVector);
//    for (; iterator; iterator++)
//        *iterator *= num;

//    return newVector;
//}

template<typename Type>
Vector<Type> Vector<Type>::operator *(const Type &num) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> newVector(*this);
    Iterator<Type> iterator(newVector);
    for (; iterator; iterator++)
        *iterator *= num;

    return newVector;
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::mulNum(const U &num) const
{
    return operator*(num);
}

template<typename Type>
Vector<Type> &Vector<Type>::operator *=(const Type &num)
{
    time_t currentTime = time(NULL);
    if (size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    for (; iterator; iterator++)
        *iterator *= num;
    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::mulNumEqual(const Type &num)
{
    return operator*=(num);
}

// Умножение элементов двух векторов
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator ^(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] * vector[0])> newVector(size);

    Iterator<decltype((*this)[0] * vector[0])> resIter(newVector);
    Iterator<Type> fIter(*this);
    Iterator<U> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        *resIter = *fIter * *sIter;
    }

    return newVector;
}

template<typename Type>
Vector<Type> Vector<Type>::operator ^(const Vector<Type> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> newVector(size);

    Iterator<Type> resIter(newVector);
    Iterator<Type> fIter(*this);
    Iterator<Type> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        *resIter = *fIter * *sIter;
    }

    return newVector;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator ^=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> fIter(*this);
    Iterator<Type> sIter(vector);

    for (int i = 0; fIter; i++, fIter++, sIter++)
    {
        *fIter = *fIter * *sIter;
    }

    return (*this);
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::mulElems(const Vector<U> & vector) const
{
    return operator^(vector);
}

template<typename Type>
Vector<Type> &Vector<Type>::mulElemsEqual(const Vector<Type> &vector)
{
    return operator^=(vector);
}

// Скалярное произведение
template<typename Type>
template<typename U>
auto Vector<Type>::operator *(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype ((*this)[0] * vector[0])> newVector(size);
    newVector = (*this) ^ vector;
    return newVector.sumValue();
}

template<typename Type>
Type Vector<Type>::operator *=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    (*this) ^= vector;
    return this->sumValue();
}

template<typename Type>
template<typename U>
auto Vector<Type>::ScalarProd(const Vector<U> &vector) const
{
    return operator*(vector);
}

template<typename Type>
Type Vector<Type>::ScalarProd(const Vector<Type> &vector) const
{
    return operator*(vector);
}

template<typename Type>
Type Vector<Type>::ScalarProdEqual(const Vector<Type> &vector)
{
    return operator*=(vector);
}

// Векторное произведение
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator &(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (size != 3)
        return Vector<Type>();

    decltype((*this)[0] * vector[0]) x = (*this)[1] * vector[2] - (*this)[2] * vector[1];
    decltype((*this)[0] * vector[0]) y = (*this)[2] * vector[0] - (*this)[0] * vector[2];
    decltype((*this)[0] * vector[0]) z = (*this)[0] * vector[1] - (*this)[1] * vector[0];

    Vector<decltype((*this)[0] * vector[0])> new_vector(3, x, y, z);
    return new_vector;
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::VectorProd(const Vector<U> &vector) const
{
    return operator&(vector);
}

template<typename Type>
Vector<Type> Vector<Type>::VectorProd(const Vector<Type> &vector) const
{
    return operator&(vector);
}

template<typename Type>
Vector<Type>& Vector<Type>::operator &=(const Vector<Type>& vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.size <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    if (size != 3)
        return *(new Vector<Type>);

    Type x = (*this)[1] * vector[2] - (*this)[2] * vector[1];
    Type y = (*this)[2] * vector[0] - (*this)[0] * vector[2];
    Type z = (*this)[0] * vector[1] - (*this)[1] * vector[0];

    *this = Vector<Type>(3, x, y, z);
    return *this;
}

template<typename Type>
Vector<Type>& Vector<Type>::VectorProdEqual(const Vector<Type>& vector)
{
    return operator&=(vector);
}

// Деление двух векторов
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator /(const Vector<U>& vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + vector[0])> newVector(size);

    Iterator<decltype((*this)[0] + vector[0])> resIter(newVector);
    Iterator<Type> fIter((*this));
    Iterator<U> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
    {
        if (fabs(*sIter) < __DBL_EPSILON__)
        {
            curTime = time(NULL);
            throw ZeroDivException (__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
        }
        *resIter = *fIter / *sIter;
    }

    return newVector;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator /=(const Vector<Type>& vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> fIter((*this));
    Iterator<Type> sIter(vector);

    for (int i = 0; fIter; i++, fIter++, sIter++)
    {
        if (fabs(*sIter) < __DBL_EPSILON__)
        {
            curTime = time(NULL);
            throw ZeroDivException (__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
        }
        *fIter /= *sIter;
    }

    return *this;
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::div(const Vector<U>& vector) const
{
    return operator/(vector);
}

template<typename Type>
Vector<Type> &Vector<Type>::divEqual(const Vector<Type>& vector)
{
    return operator/=(vector);
}

// Деление вектора на число
template<typename Type>
Vector<Type> &Vector<Type>::operator /=(const Type& number)
{
    time_t curTime = time(NULL);
    if (size <= 0)
       throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (number == 0)
        throw ZeroDivException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> iterator(*this);
    for (; iterator; iterator++)
       *iterator /= number;
    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::divNumEqual(const Type& number)
{
    return operator/=(number);
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator /(const U& number) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
       throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (number == 0)
        throw ZeroDivException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] / number)> new_vector(*this);
    Iterator<decltype((*this)[0] / number)> iterator(new_vector);
    for (; iterator; iterator++)
       *iterator /= number;
    return new_vector;
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::divNum(const U& number) const
{
    return operator/(number);
}


// Равны ли вектора.
template<typename Type>
bool Vector<Type>::operator ==(const Vector<Type> &vector) const {
    bool res = true;
    time_t currentTime = time(NULL);
    if (size < 0 || vector.size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    if (size != vector.size)
        res = true;
    else
    {
        Iterator<Type> fIter(*this);
        Iterator<Type> sIter(vector);
        for (; res && fIter; sIter++, fIter++)
            if (fabs(*fIter - *sIter) > __DBL_EPSILON__)
                res = false;
    }

    return res;
}

// Различны ли вектора.
template<typename Type>
bool Vector<Type>::operator !=(const Vector<Type> &vector) const {
    bool res = false;
    time_t currentTime = time(NULL);
    if (size < 0 || vector.size < 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    if (size != vector.size)
        res = true;
    else
    {
        Iterator<Type> fIter(*this);
        Iterator<Type> sIter(vector);

        for (; !res && fIter; fIter++, sIter++)
            if (fabs(*fIter - *sIter) > 1e-6)
                res = true;
    }

    return res;
}

// Суммирование всех элементов.
template<typename Type>
Type Vector<Type>::sumValue()
{
    time_t currentTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));

    Iterator<Type> iterator(*this);
    Type summary = 0;
    for (; iterator; iterator++)
        summary += *iterator;

    return summary;
}

// Сумма векторов
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator +(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + vector[0])> newVector(size);

    Iterator<decltype((*this)[0] + vector[0])> resIter(newVector);
    Iterator<Type> fIter((*this));
    Iterator<U> sIter(vector);
    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter + *sIter;

    return newVector;
}

template<typename Type>
Vector<Type> Vector<Type>::operator +(const Vector<Type> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> newVector(size);

    Iterator<Type> resIter(newVector);
    Iterator<Type> fIter((*this));
    Iterator<Type> sIter(vector);
    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter + *sIter;

    return newVector;
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::sum(const Vector<U> &vector) const
{
    return operator+(vector);
}

template<typename Type>
Vector<Type> &Vector<Type>::operator +=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> fIter((*this));
    Iterator<Type> sIter(vector);
    for (int i = 0; fIter; i++, fIter++, sIter++)
        *fIter = *fIter + *sIter;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::sumEqual(const Vector<Type> &vector)
{
    return operator+=(vector);
}

// Cумма вектора и числа
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator +(const U &number) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + number)> newVector(size);

    Iterator<decltype((*this)[0] + number)> resIter(newVector);
    Iterator<Type> fIter((*this));
    for (int i = 0; resIter; i++, resIter++, fIter++)
        *resIter = *fIter + number;

    return newVector;
}

template<typename Type>
 Vector<Type> &Vector<Type>::operator +=(const Type &number)
 {
     time_t curTime = time(NULL);
     if (size <= 0)
         throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

     Iterator<Type> fIter((*this));
     for (int i = 0; fIter; i++, fIter++)
         *fIter += number;

     return (*this);
 }

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::sumNum(const U &number) const
{
   return operator +(number);
}

template<typename Type>
Vector<Type> &Vector<Type>::sumNumEqual(const Type &number)
{
    return operator+=(number);
}

// Разность векторов.
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator -(const Vector<U> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] - vector[0])> newVector(size);
    Iterator<decltype((*this)[0] - vector[0])> resIter(newVector);
    Iterator<Type> fIter((*this));
    Iterator<U> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter - *sIter;

    return newVector;
}

template<typename Type>
Vector<Type> Vector<Type>::operator -(const Vector<Type> &vector) const
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> newVector(size);
    Iterator<Type> resIter(newVector);
    Iterator<Type> fIter((*this));
    Iterator<Type> sIter(vector);

    for (int i = 0; resIter; i++, resIter++, fIter++, sIter++)
        *resIter = *fIter - *sIter;

    return newVector;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator -=(const Vector<Type> &vector)
{
    time_t curTime = time(NULL);
    if (size <= 0 || vector.getSize() <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));
    if (size != vector.getSize())
        throw DifferentSizeVectors(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Iterator<Type> fIter((*this));
    Iterator<Type> sIter(vector);

    for (int i = 0; fIter; i++, fIter++, sIter++)
        *fIter = *fIter - *sIter;

    return *this;
}

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::sub(const Vector<U> &vector) const
{
    return operator-(vector);
}

template<typename Type>
Vector<Type> &Vector<Type>::subEqual(const Vector<Type> &vector)
{
    return operator-=(vector);
}

// Cумма вектора и числа
template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::operator -(const U &number) const
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<decltype((*this)[0] + number)> newVector(size);

    Iterator<decltype((*this)[0] + number)> resIter(newVector);
    Iterator<Type> fIter((*this));
    for (int i = 0; resIter; i++, resIter++, fIter++)
        *resIter = *fIter - number;

    return newVector;
}

template<typename Type>
 Vector<Type> &Vector<Type>::operator -=(const Type &number)
 {
     time_t curTime = time(NULL);
     if (size <= 0)
         throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

     Iterator<Type> fIter((*this));
     for (int i = 0; fIter; i++, fIter++)
         *fIter -= number;

     return (*this);
 }

template<typename Type>
template<typename U>
decltype(auto) Vector<Type>::subNum(const U &number) const
{
   return operator -(number);
}

template<typename Type>
Vector<Type> &Vector<Type>::subNumEqual(const Type &number)
{
   return operator -=(number);
}


// Оператор вычитания - обратный вектор
template<typename Type>
Vector<Type> Vector<Type>::operator -()
{
    time_t curTime = time(NULL);
    if (size <= 0)
        throw EmptyVectorException(__FILE__, typeid(*this).name(), __LINE__, ctime(&curTime));

    Vector<Type> newVector(*this);
    Iterator<Type> iterator(newVector);
    for (; iterator; iterator++)
        *iterator = -*iterator;

    return newVector;
}

template<typename Type>
Vector<Type> Vector<Type>::reverse()
{
    return operator-();
}


// Выделение памяти под новый вектор.
template<typename Type>
void Vector<Type>::allocNewVectorMem(int amount)
{
    time_t currentTime = time(NULL);
    try
    {
        values.reset();
    }
    catch (std::bad_alloc &exception)
    {
        throw MemoryException(__FILE__, typeid(*this).name(), __LINE__, ctime(&currentTime));
    }
    std::shared_ptr<Type[]> temp(new Type[amount], std::default_delete<Type[]>());
    values = temp;
}


template<typename Type>
Iterator<Type> Vector<Type>::begin() noexcept
{
    Iterator<Type> iterator(*this);
    return iterator;
}

template<typename Type>
Iterator<Type> Vector<Type>::end() noexcept
{
    Iterator<Type> iterator(*this);
    return iterator + size;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::begin() const noexcept
{
    ConstIterator<Type> iterator(*this);
    return iterator;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::end() const noexcept
{
    ConstIterator<Type> iterator(*this);
    return iterator + size;
}


template <typename Type>
Type& Vector<Type>::getX()
{
    return this->getItem((int)X);
}

template <typename Type>
Type& Vector<Type>::getY()
{
    return this->getItem((int)Y);
}

template <typename Type>
Type& Vector<Type>::getZ()
{
    return this->getItem((int)Z);
}

template <typename Type>
Type& Vector<Type>::getW()
{
    return this->getItem((int)W);
}

template <typename Type>
const Type &Vector<Type>::getX() const
{
    return this->getItem((int)X);
}

template <typename Type>
const Type &Vector<Type>::getY() const
{
    return this->getItem((int)Y);
}

template <typename Type>
const Type &Vector<Type>::getZ() const
{
    return this->getItem((int)Z);
}

template <typename Type>
const Type &Vector<Type>::getW() const
{
    return this->getItem((int)W);
}

template <typename Type>
void Vector<Type>::setX(Type x)
{
    this->setItem((int)X, x);
}

template <typename Type>
void Vector<Type>::setY(Type y)
{
    this->setItem((int)Y, y);
}

template <typename Type>
void Vector<Type>::setZ(Type z)
{
    this->setItem((int)Z, z);
}

template <typename Type>
void Vector<Type>::setW(Type w)
{
    this->setItem((int)W, w);
}

template <typename Type>
Vector<Type> Vector<Type>::VecNormalize() const
{
    auto len = this->getLength();

    return this->divNum(len);
}

template <typename Type>
Vector<Type>& Vector<Type>::VecSaturate()
{
    setX(std::min((Type)1., std::max((Type)0., getX())));
    setY(std::min((Type)1., std::max((Type)0., getY())));
    setZ(std::min((Type)1., std::max((Type)0., getZ())));

    return *this;
}

template <typename Type>
Vector<Type> Vector<Type>::HadamardProd(const Vector<Type> &vec)
{
    Vector<Type> *res = new Vector<Type>(*this);
    for (int i = 0; i < this->size; i++)
        res->setItem(i, res->getItem(i) * vec.getItem(i));

    return *res;
}

template <typename Type>
Vector<Type> Vector<Type>::VecProjection(const Vector<Type> &b)
{
    Vector<Type> tmp = b / b.getLength();

    return tmp * this->ScalarProd(tmp);
}

template <typename Type>
double Vector<Type>::AngleBetweenVecs(const Vector<Type> b)
{
    double angle = this->ScalarProd(b);
    angle /= (this->getLength() * b.getLength());
    return acos(angle);
}

#endif // VECTOR_HPP
