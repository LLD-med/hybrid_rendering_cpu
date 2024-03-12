#include "DrawSurfaceModelAdapter.h"
#include "baryFuncs/BaryFuncs.h"
//#include "SurfaceModelImpl.h"

#define EPS 1e-6

void DrawSurfaceModelAdapter::setCamera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

void DrawSurfaceModelAdapter::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

void DrawSurfaceModelAdapter::setBuffer(std::shared_ptr<gBuffer> buffer)
{
    _buffer = buffer;
}

void DrawSurfaceModelAdapter::setShaders(std::shared_ptr<GeometryShaderImpl> geom_shader,
                                        std::shared_ptr<VertexShaderImpl> vertex_shader,
                                        std::shared_ptr<PixelShaderImpl> pixel_shader)
{
    _geom_shader = geom_shader;
    _vertex_shader = vertex_shader;
    _pixel_shader = pixel_shader;
}

void denormolize(int width, int height, Vertex &v)
{
    auto tmp_x = v.getPosition().getX() * v.getInvW();
    auto tmp_y = v.getPosition().getY() * v.getInvW();
    auto tmp_z = v.getPosition().getZ() * v.getInvW();
    tmp_x = (tmp_x + 1.0f) * (width >> 1);
    tmp_y = (1.0f - tmp_y) * (height >> 1);
    v.setPosition({tmp_x, tmp_y, tmp_z});
}


bool DrawSurfaceModelAdapter::backfaceCulling(const Vertex &a, const Vertex &b, const Vertex &c)
{
    auto face_normal = (b.getPosition() - a.getPosition()).VectorProd(c.getPosition() - a.getPosition());
    auto cam = _camera->_cameraImpl;

    auto res1 = face_normal.ScalarProd(a.getPosition() - cam->getLocation());
    auto res2 = face_normal.ScalarProd(b.getPosition() - cam->getLocation());
    auto res3 = face_normal.ScalarProd(c.getPosition() - cam->getLocation());

    if ((res1 > 0) && (res2 > 0) && (res3 > 0))
        return true;
    return false;
}

bool clip(const Vertex& v)
{
    const float w = 1 / v.getInvW();
    auto v_x = v.getPosition().getX();
    auto v_y = v.getPosition().getY();
    auto v_z = v.getPosition().getZ();

    return (v_x > -w || fabs(v_x + w) < EPS) &&
           (v_x < w || fabs(v_x - w) < EPS) &&
           (v_y > -w || fabs(v_y + w) < EPS) &&
           (v_y < w || fabs(v_y - w) < EPS) &&
           (v_z > 0. || fabs(v_z) < EPS) &&
           (v_z < w || fabs(v_z - w) < EPS);
}


#define Min(val1, val2) std::min(val1, val2)
#define Max(val1, val2) std::max(val1, val2)
void DrawSurfaceModelAdapter::rasterBarTriangle(Vertex &_p1, Vertex &_p2, Vertex &_p3, VecD &props)
{
    if (!clip(_p1) && !clip(_p2) && !clip(_p3))
        return;

    int width = _drawer->sceneWidth();
    int height = _drawer->sceneHeight();

    denormolize(width, height, _p1);
    denormolize(width, height, _p2);
    denormolize(width, height, _p3);

    auto p1 = _p1.getPosition();
    auto p2 = _p2.getPosition();
    auto p3 = _p3.getPosition();

    double sx = std::floor(Min(Min(p1.getX(), p2.getX()), p3.getX()));
    double ex = std::ceil(Max(Max(p1.getX(), p2.getX()), p3.getX()));

    double sy = std::floor(Min(Min(p1.getY(), p2.getY()), p3.getY()));
    double ey = std::ceil(Max(Max(p1.getY(), p2.getY()), p3.getY()));

    for (int y = static_cast<int>(sy); y < static_cast<int>(ey); y++)
    {
        for (int x = static_cast<int>(sx); x < static_cast<int>(ex); x++)
        {
            auto bary = toBarycentric(p1, p2, p3, VecD({static_cast<double>(x), static_cast<double>(y)}));
            double bary_x = bary.getX();
            double bary_y = bary.getY();
            double bary_z = bary.getZ();
            if ( (bary_x > 0.0 || fabs(bary_x) < EPS) && (bary_x < 1.0 || fabs(bary_x - 1.0) < EPS) &&
                 (bary_y > 0.0 || fabs(bary_y) < EPS) && (bary_y < 1.0 || fabs(bary_y - 1.0) < EPS) &&
                 (bary_z > 0.0 || fabs(bary_z) < EPS) && (bary_z < 1.0 || fabs(bary_z - 1.0) < EPS))
            {
                auto interpolatedPos = baryCentricInterpolation(p1, p2, p3, bary);
                interpolatedPos.setX(x);
                interpolatedPos.setY(y);
                if (testZbuffer(interpolatedPos))
                {
                    VecD pixel_color = _pixel_shader->apply(_p1, _p2, _p3, bary) * 255.;
                    VecD newNormals = baryCentricInterpolation(_p1.getNormal(), _p2.getNormal(), _p3.getNormal(), bary).VecNormalize();
                    _buffer->setNormal(x, y, newNormals);
                    _buffer->setColor(x, y, pixel_color);
                    _buffer->setProperties(x, y, props);
                    _drawer->putPixel(x, y, pixel_color);
                }
            }
        }
    }
}

bool DrawSurfaceModelAdapter::testZbuffer(const VecD &p)
{
    int x = std::round(p.getX());
    int y = std::round(p.getY());
    int width = _drawer->sceneWidth();
    int height = _drawer->sceneHeight();
    bool flag = true;
    if (x >= width || y >= height || x < 0 || y < 0)
        flag = false;
    if (flag)
    {
        if (_buffer->getZdepth(x, y) > p.getZ() || fabs(_buffer->getZdepth(x, y) - p.getZ()) < EPS)
        {
            _buffer->setDepth(x, y, p.getZ());
            _buffer->setPosition(x, y, p.getX(), p.getY(), p.getZ());
        }
        else
            flag = false;
    }
    return flag;
}


void DrawSurfaceModelAdapter::cpu_GbufferFill(std::shared_ptr<SurfaceModel> model)
{
    auto cam = _camera->_cameraImpl;
    Transform viewMatrix = _camera->getView();
    Transform projectMatrix = _camera->getProjection();

    Transform toWordMatrix = model->getObjToWorld();
    Transform rotationMatrix = model->getRotationMatrix();

    std::shared_ptr<SurfaceModelImpl> modelImpl = model->_modelImpl;
    Material material = modelImpl->getMaterial();

    VecD modelProps = VecD({material.getSpecularity(), material.getReflectivity(), material.getRefraction()});

    for (auto& face: modelImpl->getFaces())
    {
        auto a = _vertex_shader->apply(face.getA(), rotationMatrix, toWordMatrix, cam);
        auto b = _vertex_shader->apply(face.getB(), rotationMatrix, toWordMatrix, cam);
        auto c = _vertex_shader->apply(face.getC(), rotationMatrix, toWordMatrix, cam);

        if (backfaceCulling(a, b, c))
            continue;

        a = _geom_shader->apply(a, projectMatrix, viewMatrix);
        b = _geom_shader->apply(b, projectMatrix, viewMatrix);
        c = _geom_shader->apply(c, projectMatrix, viewMatrix);

        rasterBarTriangle(a, b, c, modelProps);
    }
}


void DrawSurfaceModelAdapter::request()
{
    if (_adaptee && _camera && _drawer)
    {
        std::shared_ptr<SurfaceModelImpl> model = _adaptee->_modelImpl;
        model->createBoundingBox(_adaptee->getObjToWorld());

        cpu_GbufferFill(_adaptee);
    }
}
