#ifndef DRAWSURFACEMODELADAPTER_H
#define DRAWSURFACEMODELADAPTER_H

#include "BaseDrawer.h"
#include "Camera.h"
#include "shaders/PixelShaderImpl.h"
#include "shaders/GeometryShaderImpl.h"
#include "shaders/VertexShaderImpl.h"
#include <SurfaceModelAdapter.h>

class DrawSurfaceModelAdapter : public SurfaceModelAdapter
{
public:
    void setCamera(std::shared_ptr<Camera> camera);
    void setDrawer(std::shared_ptr<BaseDrawer> darwer);
    void setBuffer(std::shared_ptr<gBuffer> buffer);
    void setShaders(std::shared_ptr<GeometryShaderImpl> geom_shader,
                    std::shared_ptr<VertexShaderImpl> vertex_shader,
                    std::shared_ptr<PixelShaderImpl> pixel_shader);

    virtual void request() override;

protected:
    void trasformModel(std::shared_ptr<SurfaceModelImpl> &model);

    bool backfaceCulling(const Vertex &a, const Vertex &b, const Vertex &c);
    void rasterBarTriangle(Vertex &_p1, Vertex &_p2, Vertex &_p3, VecD &props);
    bool testZbuffer(const VecD &p);

    void cpu_GbufferFill(std::shared_ptr<SurfaceModel> model);

private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<BaseDrawer> _drawer;

    std::shared_ptr<gBuffer> _buffer; // убрать, будет находиться в _drawer

    std::shared_ptr<GeometryShaderImpl> _geom_shader;
    std::shared_ptr<VertexShaderImpl> _vertex_shader;
    std::shared_ptr<PixelShaderImpl> _pixel_shader;
};

#endif // DRAWSURFACEMODELADAPTER_H
