#include "gBuffer.h"

void gBuffer::setColor(int x, int y, VecD &color)
{
    g_color[y * w_width + x] = color;
}

void gBuffer::setPosition(int x, int y, double posX, double posY, double posZ)
{
    g_position[y * w_width + x] = VecD({ posX, posY, posZ });
}

void gBuffer::setPosition(int x, int y, VecD &pos)
{
    g_position[y * w_width + x] = pos;
}

void gBuffer::setNormal(int x, int y, VecD &norm)
{
    g_normal[y * w_width + x] = norm;
}


void gBuffer::setProperties(int x, int y, VecD &prop)
{
    g_properties[y * w_width + x] = prop;
}


void gBuffer::setNormal(int x, int y, double normalX, double normalY, double normalZ)
{
    g_normal[y * w_width + x] = VecD({normalX, normalY, normalZ});
}

void gBuffer::setDepth(int x, int y, float value)
{
    g_depth[y * w_width + x] = value;
}

float gBuffer::getZdepth(int x, int y)
{
    return g_depth[y * w_width + x];
}

VecD gBuffer::getPosition(int x, int y)
{
    return g_position[y * w_width + x];
}

VecD gBuffer::getNormal(int x, int y)
{
    return g_normal[y * w_width + x];
}

VecD gBuffer::getColor(int x, int y)
{
    return g_color[y * w_width + x];
}

double gBuffer::getProperty(int x, int y, int type)
{
    // types:
    // 0 = specularity
    // 1 = reflectivity
    // 2 = refraction
    return g_properties[y * w_width + x].getItem(type);
}

VecD gBuffer::getProperties(int x, int y)
{
    return g_properties[y * w_width + x];
}
