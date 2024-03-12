#ifndef DRAWCOMPOSITEADAPTER_H
#define DRAWCOMPOSITEADAPTER_H

#include <CompositeAdapter.h>
#include <Camera.h>
#include <BaseDrawer.h>
#include <DrawSurfaceModelAdapter.h>
#include "shaders/PixelShaderImpl.h"
#include "shaders/GeometryShaderImpl.h"
#include "shaders/VertexShaderImpl.h"
#include "gBuffer.h"
#include "LightsManager.h"
#include "Ray.h"

class DrawCompositeAdapter : public CompositeAdapter
{
public:
    void setCamera(std::shared_ptr<Camera> camera);
    void setDrawer(std::shared_ptr<BaseDrawer> drawer);
    void setLightsManager(std::shared_ptr<LightsManager> lights);

    virtual void request() override;

    void cpuHybridWrapper();
    bool sceneIntersect(const Ray &ray, IntersectionData &data);
    VecD castRay(const Ray &ray, int depth, const int x = 0, const int y = 0);

private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<BaseDrawer> _drawer;
    std::shared_ptr<LightsManager> _lights;

    std::shared_ptr<PixelShaderImpl> pixel_shader;
    std::shared_ptr<VertexShaderImpl> vertex_shader;
    std::shared_ptr<GeometryShaderImpl> geom_shader;

    std::shared_ptr<gBuffer> _gBuffer;
};


#endif // DRAWCOMPOSITEADAPTER_H
