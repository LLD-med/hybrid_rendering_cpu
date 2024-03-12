#ifndef SURFACEMODELIMPL_H
#define SURFACEMODELIMPL_H

#include <vector>
#include "Face.h"
#include "Mesh.h"
#include <QImage>
#include "Material.h"
#include "BoundingBox.h"
#include "Transform.h"
#include "IntersectionData.h"

class SurfaceModelImpl
{
public:
    SurfaceModelImpl() = default;

    SurfaceModelImpl(Mesh &mesh, Material &material, std::vector<Face> &faces);
//    SurfaceModelImpl(std::vector<Face> &faces, Mesh &mesh, BoundingBox &bindBox);

    ~SurfaceModelImpl() = default;

    void setCenter(const VecD &center);
    const VecD getCenter() const;

    std::vector<Face> &getFaces();
    Mesh &getMesh();
    Material &getMaterial();
    VecD &getColor();
    QImage getTexture();
    bool getSurfaceType();

    void addFace(const Face &face);
    void setMesh(const Mesh &mesh);
    void setMaterial(const Material &material);
    void setTexture(const QImage &texture);
    void setColor(const VecD &color);

    void setProperties(const VecD &properties);

    void setCenter(VecD &center);
    VecD getCenter();

    void createBoundingBox(Transform objToWorld);

    bool triangleIntersect(const Face& face, const Ray &ray,
                           const Transform &objToWorld, const Transform &rotMatrix,
                           IntersectionData &data);

    bool rayIntersect(const Ray &ray, const Transform &objToWorld,
                      const Transform &rotMatrix, IntersectionData &data);

private:
    std::vector<Face> _faces;
    Mesh _mesh;
    Material _material;

    VecD _center;

    bool has_texture = false;

    BoundingBox _boundBox;
    QImage _texture;
    VecD _color;
};

#endif // SURFACEMODELIMPL_H
