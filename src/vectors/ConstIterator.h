#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include <memory>
#include <iostream>
#include <ctime>

#include "BaseIterator.h"
#include "VectorExceptions.hpp"

template<typename Type>
class Vector;

template<typename Type>
class ConstIterator: public BaseIterator
{
public:

   ConstIterator(const ConstIterator<Type>&);
   ConstIterator(const Vector<Type>&);

   const Type& operator *() const;
   const Type* operator ->() const;

   const Type &operator [](int index) const;
   operator bool() const;

   ConstIterator<Type>& operator =(const ConstIterator<Type>& iterator);

   ConstIterator<Type>& operator +=(int number);
   ConstIterator<Type>& operator ++();     // префиксный инкремент
   ConstIterator<Type>  operator ++(int);  // постфиксный инкремент
   ConstIterator<Type>  operator + (int number) const;

   ConstIterator<Type>& operator -=(int number);
   ConstIterator<Type>& operator --();    // префиксный декремент
   ConstIterator<Type>  operator --(int); // постфиксный декремент
   ConstIterator<Type>  operator - (int number) const;

   bool operator <=(const ConstIterator<Type>& iterator) const;
   bool operator <(const ConstIterator<Type>& iterator) const;
   bool operator >=(const ConstIterator<Type>& iterator) const;
   bool operator >(const ConstIterator<Type>& iterator) const;
   bool operator ==(const ConstIterator<Type>& iterator) const;
   bool operator !=(const ConstIterator<Type>& iterator) const;

protected:
    Type* get_cur_ptr() const;

    void check_object(int) const;   // проверка объекта на null
    void check_validity(int) const; // проверака

private:
    std::weak_ptr<Type[]> weakPtr;
};

#endif // CONSTITERATOR_H
