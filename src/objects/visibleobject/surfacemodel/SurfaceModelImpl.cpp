#include "SurfaceModelImpl.h"
#include "baryFuncs/BaryFuncs.h"

SurfaceModelImpl::SurfaceModelImpl(Mesh &mesh, Material &material, std::vector<Face> &faces) :
    _faces(faces), _mesh(mesh), _material(material) { }

//SurfaceModelImpl(std::vector<Face> &faces, Mesh &mesh, BoundingBox &bindBox);


std::vector<Face> &SurfaceModelImpl::getFaces()
{
    return _faces;
}

Mesh &SurfaceModelImpl::getMesh()
{
    return _mesh;
}

VecD &SurfaceModelImpl::getColor()
{
    return _color;
}

QImage SurfaceModelImpl::getTexture()
{
    return _texture;
}

bool SurfaceModelImpl::getSurfaceType()
{
    return has_texture;
}

Material &SurfaceModelImpl::getMaterial()
{
    return _material;
}

void SurfaceModelImpl::addFace(const Face &face)
{
    _faces.push_back(face);
}

void SurfaceModelImpl::setMesh(const Mesh &mesh)
{
    _mesh = mesh;
}

void SurfaceModelImpl::setMaterial(const Material &material)
{
    _material = material;
}

void SurfaceModelImpl::setProperties(const VecD &properties)
{
    _material.setSpecularity(properties.getX());
    _material.setReflectivity(properties.getY());
    _material.setRefraction(properties.getZ());
}


void SurfaceModelImpl::setTexture(const QImage &texture)
{
    _texture = texture;
}

void SurfaceModelImpl::setColor(const VecD &color)
{
    _color = color;
    for (auto &elem : _mesh.getVertices())
    {
        elem.setColor(color);
    }
    for (auto &face : _faces)
    {
        face.setColorA(color);
        face.setColorB(color);
        face.setColorC(color);
    }
}

void SurfaceModelImpl::setCenter(VecD &center)
{
    _center = center;
}

VecD SurfaceModelImpl::getCenter()
{
    return _center;
}

Vertex transform_position(const Vertex &vert, const Transform &objToWorld,
                          const Transform &rotationMatrix)
{
    auto vertPos = vert.getPosition();
    VecD pos({vertPos.getX(), vertPos.getY(), vertPos.getZ(), 1});
//    pos = objToWorld.VectorByTransform(pos);
    pos = pos * objToWorld;

    Vertex res = vert;
    auto vert_norm = res.getNormal();
    VecD normal({vert_norm.getX(), vert_norm.getY(), vert_norm.getZ(), 1});

//    normal = rotationMatrix.VectorByTransform(normal);
    normal = normal * rotationMatrix;

    res.setNormal(VecD({normal.getX(), normal.getY(), normal.getZ()}));
    res.setPosition(VecD({pos.getX(), pos.getY(), pos.getZ()}));

    return res;
}

bool SurfaceModelImpl::triangleIntersect(const Face& face, const Ray &ray,
                                         const Transform &objToWorld, const Transform &rotMatrix,
                                         IntersectionData &data)
{
    Vertex p0 = transform_position(face.getA(), objToWorld, rotMatrix);
    Vertex p1 = transform_position(face.getB(), objToWorld, rotMatrix);
    Vertex p2 = transform_position(face.getC(), objToWorld, rotMatrix);

    auto edge1 = p1.getPosition() - p0.getPosition();
    auto edge2 = p2.getPosition() - p0.getPosition();

    VecD h = ray.direction.VectorProd(edge2);
    double a = edge1.ScalarProd(h);

    bool intersected = false;

    if (fabs(a) < std::numeric_limits<float>::epsilon())
        return intersected;

    double f = 1. / a;
    auto s = ray.origin - p0.getPosition();
    auto u = s.ScalarProd(h) * f;

    if (u < 0. || u > 1.)
        return intersected;

    auto q = s.VectorProd(edge1);
    auto v = f * ray.direction.ScalarProd(q);

    if (v < 0. || u + v > 1.)
        return intersected;

    double cur_t = f * edge2.ScalarProd(q);

    if (cur_t > 0)
    {
        auto bary = VecD({ 1 - u - v, u, v });
        VecD pos = VecD(ray.origin + ray.direction * cur_t);
        data.setPosition(ray.origin + ray.direction * cur_t);
        data.setNormal(baryCentricInterpolation(p0.getNormal(), p1.getNormal(), p2.getNormal(), bary).VecNormalize());

        data.setT(cur_t);
        intersected = true;
        if (has_texture)
        {
            float pixel_u = interpolateCoord(p0.getU() , p1.getU(), p2.getU(), bary);
            float pixel_v = interpolateCoord(p0.getV(), p1.getV(), p2.getV(), bary);

            int x = std::floor(pixel_u * (_texture.width()) - 1);
            int y = std::floor(pixel_v * (_texture.height() - 1));

            if (x < 0)
                x = 0;
            if (y < 0)
                y = 0;
            auto color = _texture.pixelColor(x, y);
            auto red = (float)color.red();
            auto green = (float)color.green();
            auto blue = (float)color.blue();
            data.setColor(VecD({red / 255., green / 255., blue / 255.}));
        }
        else
            data.setColor(baryCentricInterpolation(p0.getColor(), p1.getColor(), p2.getColor(), bary));
    }
    return intersected;
}

bool SurfaceModelImpl::rayIntersect(const Ray &ray, const Transform &objToWorld,
                                    const Transform &rotMatrix, IntersectionData &data)
{
    if (!this->_boundBox.checkIntersection(ray))
        return false;

    float modelDist = std::numeric_limits<float>::max();
    bool intersected = false;

    for (auto& face: _faces)
    {
        IntersectionData tmpData;
        if (triangleIntersect(face, ray, objToWorld, rotMatrix, tmpData) && tmpData.getT() < modelDist)
        {
            modelDist = tmpData.getT();
            data = tmpData;
            intersected = true;
        }
    }

    return intersected;
}


void SurfaceModelImpl::createBoundingBox(Transform objToWorld)
{
    float inf = std::numeric_limits<float>::infinity();
    VecD min = {inf, inf, inf};
    VecD max = {-inf, -inf, -inf};

    auto vertices = _mesh.getVertices();
    for (auto &cur_vertex: vertices)
    {
//        VecD tmp(cur_vertex.getPosition());
        VecD tmp({cur_vertex.getPosition().getX(), cur_vertex.getPosition().getY(), cur_vertex.getPosition().getZ(), 1});
        auto tmp_x = tmp.getX();
        auto tmp_y = tmp.getY();
        auto tmp_z = tmp.getZ();

//        tmp = objToWorld.VectorByTransform(tmp);
        tmp = tmp * objToWorld;
        if (tmp_x < min.getX())
            min.setX(tmp_x);
        if (tmp_y < min.getY())
            min.setY(tmp_y);
        if (tmp_z < min.getZ())
            min.setZ(tmp_z);

        if (tmp_x > max.getX())
            max.setX(tmp_x);
        if (tmp_y > max.getY())
            max.setY(tmp_y);
        if (tmp_z > max.getZ())
            max.setZ(tmp_z);
    }
    _boundBox = BoundingBox(min, max);
}
