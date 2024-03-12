#include <Composite.h>

Composite::Composite(std::shared_ptr<BaseObject> &element)
{
    _elements.push_back(element);
}


Composite::Composite(const std::vector<std::shared_ptr<BaseObject>> &vector)
//Composite::Composite(std::vector<std::shared_ptr<BaseObject>> &vector)
{
    _elements = vector;
}


bool Composite::add(const std::shared_ptr<BaseObject> &element)
{
    _elements.push_back(element);

    return true;
}


bool Composite::remove(const ObjIterator &iter)
{
    _elements.erase(iter);

    return true;
}


bool Composite::isVisible()
{
    return false;
}

bool Composite::isComposite()
{
    return true;
}

VecD Composite::getCenter() const
{
    return _center;
}

ObjIterator Composite::begin()
{
    return _elements.begin();
}


ObjIterator Composite::end()
{
    return _elements.end();
}
