#include "ObjectsContainer.h"

#include <QDebug>

std::size_t ObjectsContainer::addObject(const std::shared_ptr<BaseObject> &object)
{
    _objects.push_back(object);

    return object->getId();
}


void ObjectsContainer::deleteObject(const std::size_t id)
{
    auto iter = begin();
    for (; iter != end() && (*iter)-> getId() != id; iter++);

    _objects.erase(iter);
}

int ObjectsContainer::getCount()
{
    return _objects.size();
}

ContIterator ObjectsContainer::getObjectIter(const std::size_t id)
{
    auto iter = begin();
    for (; iter != end() && (*iter)->getId() != id; ++iter);

    return iter;
}

std::shared_ptr<BaseObject> ObjectsContainer::getObject(const std::size_t id)
{
    return *getObjectIter(id);
}

std::vector<std::shared_ptr<BaseObject>> ObjectsContainer::getObjects()
{
    return _objects;
}

ContIterator ObjectsContainer::begin()
{
    return _objects.begin();
}

ContIterator ObjectsContainer::end()
{
    return _objects.end();
}
