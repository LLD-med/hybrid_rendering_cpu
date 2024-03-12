#ifndef OBJECTSCONTAINER_H
#define OBJECTSCONTAINER_H

#include <memory>
#include "BaseObject.h"

using ContIterator = std::vector<std::shared_ptr<BaseObject>>::iterator;

class ObjectsContainer
{
public:
    ObjectsContainer() = default;
    ~ObjectsContainer() = default;

    std::size_t addObject(const std::shared_ptr<BaseObject> &object);
    void deleteObject(const std::size_t id);

    int getCount();

    ContIterator getObjectIter(const std::size_t id);
    std::shared_ptr<BaseObject> getObject(const std::size_t id);
    std::vector<std::shared_ptr<BaseObject>> getObjects();

    ContIterator begin();
    ContIterator end();

protected:
    std::vector<std::shared_ptr<BaseObject>> _objects;
};

#endif // OBJECTSCONTAINER_H
