#ifndef BASEDRAWER_H
#define BASEDRAWER_H

//#include <Point.h>
#include "Vector.hpp"
//#include <QImage>
#include "gBuffer.h"

class BaseDrawer
{
public:
    BaseDrawer() = default;
    virtual ~BaseDrawer() = default;

//    virtual void drawLine(const Point &vertex1, const Point &vertex2) = 0;

    virtual void setPixmap() = 0;
    virtual void putPixel(int x, int y, VecD &color) = 0;
    virtual void clearScene() = 0;

    virtual int sceneHeight() = 0;
    virtual int sceneWidth() = 0;

//    virtual std::shared_ptr<gBuffer> getBuffer() = 0;
};

#endif // BASEDRAWER_H
