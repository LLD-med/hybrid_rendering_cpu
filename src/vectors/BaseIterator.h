#ifndef BASEITERATOR_H
#define BASEITERATOR_H

class BaseIterator
{
public:
    virtual ~BaseIterator() = 0;
protected:
    int index = 0;
    int size = 0;
};

#endif // BASEITERATOR_H
