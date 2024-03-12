#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "BaseObject.h"

class Composite : public BaseObject
{
    friend class DrawCompositeAdapter;
	friend class CompositeTransformAdapter;

public:
    Composite() = default;
    explicit Composite(std::shared_ptr<BaseObject> &element);
    explicit Composite(const std::vector<std::shared_ptr<BaseObject>> &vector);
//    explicit Composite(std::vector<std::shared_ptr<BaseObject>> &vector);

    virtual bool add(const std::shared_ptr<BaseObject> &element) override;
    virtual bool remove(const ObjIterator &iter) override;

    virtual bool isVisible() override;
    virtual bool isComposite() override;

    virtual VecD getCenter() const override;

    virtual ObjIterator begin() override;
    virtual ObjIterator end() override;

private:
    std::vector<std::shared_ptr<BaseObject>> _elements;
    VecD _center;
};

#endif //COMPOSITE_H
