#ifndef QTDRAWER_H
#define QTDRAWER_H

#include <QGraphicsScene>

#include <BaseDrawer.h>

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = delete;
	explicit QtDrawer(QGraphicsScene *scene);
    QtDrawer(const QtDrawer &drawer);

    void setPixmap() override;
    void putPixel(int x, int y, VecD &color) override;

    void clearScene() override;

    int sceneHeight() override;
    int sceneWidth() override;

//    std::shared_ptr<gBuffer> getBuffer() override;

private:
    QGraphicsScene *_scene;
    QImage _scenePixMap;
//    std::shared_ptr<gBuffer> _gBuffer;
};

#endif // QTDRAWER_H
