#include <QtDrawer.h>

QtDrawer::QtDrawer(QGraphicsScene *scene)
{
    _scene = scene;
    _scenePixMap = QImage(_scene->width(), _scene->height(), QImage::Format_RGB32);
    _scenePixMap.fill(Qt::black);
}


QtDrawer::QtDrawer(const QtDrawer &drawer)
{
    _scene = drawer._scene;
    _scenePixMap = QImage(_scene->width(), _scene->height(), QImage::Format_RGB32);
    _scenePixMap.fill(Qt::black);
}

void QtDrawer::setPixmap()
{
    _scene->addPixmap(QPixmap::fromImage(_scenePixMap));
}

void QtDrawer::putPixel(int x, int y, VecD &color)
{
    _scenePixMap.setPixelColor(x, y, qRgb(color.getX(), color.getY(), color.getZ()));
}

void QtDrawer::clearScene()
{
    _scene->clear();
    _scenePixMap.fill(Qt::black);
}

int QtDrawer::sceneHeight()
{
    return int(_scene->height());
}

int QtDrawer::sceneWidth()
{
    return int(_scene->width());
}
