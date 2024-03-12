#include <DrawCompositeAdapter.h>
#define GL_SILENCE_DEPRECATION
#include "shaders/Shader.h"
#include <GLFW/glfw3.h>
#include "Transform.h"
#include "surfacemodel/SurfaceModel.h"
#include "LightImpl.h"
#include "shaders/TextureShader.h"
#include "shaders/GeometryShader.h"
#include "shaders/VertexShader.h"
#include "shaders/PixelShader.h"

void DrawCompositeAdapter::setCamera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

void DrawCompositeAdapter::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

void DrawCompositeAdapter::setLightsManager(std::shared_ptr<LightsManager> lights)
{
    _lights = lights;
}

void DrawCompositeAdapter::cpuHybridWrapper()
{
    vertex_shader = std::make_shared<VertexShader>();
    geom_shader = std::make_shared<GeometryShader>();
    for (auto &elem : _adaptee->_elements)
    {
        if (elem->isComposite())
        {
            auto adapter = std::make_shared<DrawCompositeAdapter>(DrawCompositeAdapter());
            auto com_sh_ptr = std::dynamic_pointer_cast<Composite>(elem);

            adapter->setAdaptee(com_sh_ptr);
            adapter->setCamera(_camera);
            adapter->setDrawer(_drawer);
            adapter->request();
        }
        else
        {
            auto adapter = std::make_shared<DrawSurfaceModelAdapter>(DrawSurfaceModelAdapter());
            auto model_sh_ptr = std::dynamic_pointer_cast<SurfaceModel>(elem);

            if (model_sh_ptr->_modelImpl->getSurfaceType())
                pixel_shader = std::make_shared<TextureShader>(model_sh_ptr->_modelImpl->getTexture());
            else
                pixel_shader = std::make_shared<PixelShader>();

            adapter->setAdaptee(model_sh_ptr);
            adapter->setCamera(_camera);
            adapter->setDrawer(_drawer);
            adapter->setShaders(geom_shader, vertex_shader, pixel_shader);
            adapter->setBuffer(_gBuffer);
            adapter->request();
        }
    }
}


VecD toWorld(const VecD &u, const VecD &v, const VecD &w, int x, int y)
{
    return u * double(x) - v * double(y) + w;
}

VecD reflect(const VecD &L, const VecD &N)
{
    return (L - (N * 2. * N.ScalarProd(L))).VecNormalize();
}

VecD refract(const VecD &I, const VecD &N, double eta_t, double eta_i=1.f)
{
    float cosi = - std::max(-1., std::min(1., I.ScalarProd(N)));
    if (cosi < 0)
        return refract(I, -N, eta_i, eta_t);
    float eta = eta_i / eta_t;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    if (k < 0)
        return VecD(0,0,0);
    else
        return I * eta + N * (eta * cosi - sqrtf(k));
}

bool DrawCompositeAdapter::sceneIntersect(const Ray &ray, IntersectionData &data)
{
    float closeset_t = std::numeric_limits<float>::max();
    bool intersected = false;
    for (auto &elem : _adaptee->_elements)
    {
        if (elem->isComposite())
        {
            auto adapter = std::make_shared<DrawCompositeAdapter>(DrawCompositeAdapter());
            auto com_sh_ptr = std::dynamic_pointer_cast<Composite>(elem);

            adapter->setAdaptee(com_sh_ptr);
            adapter->setCamera(_camera);
            adapter->setDrawer(_drawer);
            adapter->request();
        }
        else
        {
            auto adapter = std::make_shared<DrawSurfaceModelAdapter>(DrawSurfaceModelAdapter());
            auto model_sh_ptr = std::dynamic_pointer_cast<SurfaceModel>(elem);

            std::shared_ptr<SurfaceModelImpl> modelImpl = model_sh_ptr->_modelImpl;
            auto objMat = model_sh_ptr->getObjToWorld();
            auto rotateMat = model_sh_ptr->getRotationMatrix();
            IntersectionData tmpData;
            if (modelImpl->rayIntersect(ray, objMat, rotateMat, tmpData) && tmpData.getT() < closeset_t)
            {
                closeset_t = tmpData.getT();
                intersected = true;
                data = tmpData;
            }
        }
    }

    return intersected;
}

VecD DrawCompositeAdapter::castRay(const Ray &ray, int depth, const int x, const int y)
{
    IntersectionData data;
    if (ray.getType() == RayType::primary)
    {
        if (_gBuffer->getZdepth(x, y) == std::numeric_limits<float>::max())
            return _gBuffer->getColor(x, y);
        data = IntersectionData(*_gBuffer, x, y);
    }
    else
    {
        if (depth > MAX_RECURSION_DEPTH || ! sceneIntersect(ray, data))
            return VecD({0., 0., 0.});
    }

    VecD ambient = {0., 0., 0.};
    VecD diffuse = {0., 0., 0.};
    VecD spec = {0., 0., 0.};
    VecD lightDir = {0., 0., 0.};
    VecD reflect_color = {0., 0., 0.};
    VecD refract_color = {0., 0., 0.};

    double specularity_coef = data.getProperty(0);
    double reflectivity_coef = data.getProperty(1);
    double refraction_coef = data.getProperty(2);

    VecD pos = data.getPosition();
    VecD norm = data.getNormal();;
    VecD color = data.getColor();

    double di = 1 - specularity_coef;

    if (fabs(refraction_coef) > 1e-5)
    {
        VecD refract_dir = refract(ray.getDirection(), norm, 1., refraction_coef).VecNormalize();
        VecD refract_orig;
        if (refract_dir.ScalarProd(norm) < 0)
            refract_orig = pos - norm * 1e-3;
        else
            refract_orig = pos + norm * 1e-3;
        refract_color = castRay(Ray(refract_orig, refract_dir), ++depth);
    }

    if (fabs(reflectivity_coef) > 1e-5)
    {
        VecD reflect_dir = reflect(ray.getDirection(), norm).VecNormalize();
        VecD reflect_orig;
        if (reflect_dir.ScalarProd(norm) < 0)
            reflect_orig = pos - norm * 1e-3;
        else
            reflect_orig = pos + norm * 1e-3;
        reflect_color = castRay(Ray(reflect_orig, reflect_dir), ++depth);
    }

    qDebug() << "test1";

    double lightDist;
    double occlusion = 1e-4;
    auto lights_holder = _lights->getHolder();

    for (int i = 0; i < lights_holder->getCount(); i++)
    {
        std::shared_ptr<Light> cur_light = dynamic_pointer_cast<Light>(lights_holder->getLight(i));
        auto light = cur_light->_light;
        if (light->getType() != lightType::ambient)
        {
            if (light->getType() == lightType::point)
            {
                lightDir = (light->getLocation() - pos);
                lightDist = lightDir.getLength();
                lightDir = lightDir.VecNormalize();
            }
            else // directional
            {
                lightDir = light->getDirection();
                lightDist = std::numeric_limits<float>::infinity();
            }

            auto lightAngle = lightDir.ScalarProd(norm);

            VecD shadowOrigin;
            if (lightAngle < 0)
                shadowOrigin = pos - norm * occlusion;
            else
                shadowOrigin = pos + norm * occlusion;

            IntersectionData shadowRayData;
            if (sceneIntersect(Ray(shadowOrigin, lightDir), shadowRayData))
                if ((shadowRayData.getPosition() - shadowOrigin).getLength() < lightDist)
                    continue;

            diffuse += (light->getIntensity() * std::max(0., norm.ScalarProd(lightDir)) * di);

            if (fabs(specularity_coef) < 1e-5)
                continue;
            auto r = reflect(lightDir, norm);
            auto r_dot = r.ScalarProd(ray.getDirection());

            auto power = powf(std::max(0., r_dot), 20);
            spec += light->getIntensity() * power * specularity_coef;
        }
        else
            ambient = light->getIntensity();
    }
    qDebug() << ambient.getSize() << diffuse.getSize() << spec.getSize() << reflect_color.getSize();
    return data.getColor().HadamardProd(ambient +
                                        diffuse +
                                        spec +
                                        reflect_color * reflectivity_coef +
                                        refract_color * refraction_coef);
}


void DrawCompositeAdapter::request()
{
    if (_adaptee && _camera && _drawer && _lights && ! _adaptee->_elements.empty())
    {
        int x_end = _drawer->sceneWidth();
        int y_end = _drawer->sceneHeight();

        _gBuffer = std::make_shared<gBuffer>(x_end, y_end);

        cpuHybridWrapper();

        auto cam = _camera->_cameraImpl;
        VecD u = cam->getUp().VectorProd(cam->getDirection()).VecNormalize();
        VecD v = cam->getUp().VecNormalize();
        VecD w = -cam->getDirection().VecNormalize();

        auto w_ = u * double(-(x_end >> 1)) + v * double(y_end >> 1) - w * (double((y_end >> 1)) / tan(cam->getFOV() / 2 * M_PI / 180));

        for (int x = 0; x < x_end; x++)
        {
            for (int y = 0; y < y_end; y++)
            {
                auto direction = toWorld(u, v, w_, x, y).VecNormalize();
                qDebug() << cam->getLocation().getSize() << direction.getSize();
                auto color = castRay(Ray(cam->getLocation(), direction), 0, x, y) * 255.;
                _drawer->putPixel(x, y, color);
            }
        }
        _drawer->setPixmap();
        _gBuffer->clearData();
    }
}


