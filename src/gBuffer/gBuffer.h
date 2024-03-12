#ifndef GBUFFER_H
#define GBUFFER_H

#include "Vector.hpp"

class gBuffer
{
public:
    gBuffer(int width, int height) : w_width(width), w_height(height)
    {
        g_depth.resize(w_width * w_height, std::numeric_limits<float>::max());
        g_position.resize(w_width * w_height, VecD({0., 0., 0.}));
        g_normal.resize(w_width * w_height, VecD({0., 0., 1.}));
        g_color.resize(w_width * w_height, VecD({0., 0., 0.}));
        g_properties.resize(w_width * w_height, VecD({0., 0., 0.}));
    }
    ~gBuffer() { }

    void setColor(int x, int y, VecD &color);
    void setPosition(int x, int y, double posX, double posY, double posZ);
    void setPosition(int x, int y, VecD &pos);
    void setNormal(int x, int y, double normalX, double normalY, double normalZ);
    void setNormal(int x, int y, VecD &norm);
    void setDepth(int x, int y, float value);
    void setProperties(int x, int y, VecD &prop);

    float getZdepth(int x, int y);
    VecD getPosition(int x, int y);
    VecD getNormal(int x, int y);
    VecD getColor(int x, int y);
    double getProperty(int x, int y, int type);
    VecD getProperties(int x, int y);

    void clearData()
    {
        g_depth.clear();
        g_position.clear();
        g_normal.clear();
        g_color.clear();
        g_properties.clear();
    }

private:
    int w_width;
    int w_height;
    std::vector<float> g_depth;
    std::vector<VecD> g_position;
    std::vector<VecD> g_normal;
    std::vector<VecD> g_color;
    std::vector<VecD> g_properties;
};

#endif // GBUFFER_H
