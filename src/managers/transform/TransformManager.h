#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <BaseManager.h>
#include <BaseObject.h>
#include <../../adapters/transform/BaseTransformAdapter.h>
#include <matrix.h>
#include <Transform.h>


class TransformManager : public BaseManager
{
public:
    TransformManager() = default;
    TransformManager(const TransformManager &manager) = delete;
    TransformManager &operator = (const TransformManager &manager) = delete;

    ~TransformManager() = default;

	void setAdapter(std::shared_ptr<BaseTransformAdapter> adapter);

    void moveObject(const std::shared_ptr<BaseObject> &object,
                           const double &dx,
                           const double &dy,
                           const double &dz);
    void scaleObject(const std::shared_ptr<BaseObject> &object,
                            const double &kx,
                            const double &ky,
                            const double &kz);
    void rotateObject(const std::shared_ptr<BaseObject> &object,
                             const double &ox,
                             const double &oy,
                             const double &oz);

    void multipleTransform(const std::shared_ptr<BaseObject> &object,
                         const double &dx,
                         const double &dy,
                         const double &dz,
                         const double &ox,
                         const double &oy);

    void transformObject(const std::shared_ptr<BaseObject> &object,
                         Transform &transform);
private:
	std::shared_ptr<BaseTransformAdapter> _adapter;
};


#endif //TRANSFORMMANAGER_H
