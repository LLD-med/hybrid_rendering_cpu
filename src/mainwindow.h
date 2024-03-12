#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QFileDialog>
#include <BaseCommand.h>
#include <CameraCommand.h>
#include <LightCommand.h>
#include <LightPropertyCommand.h>
#include <ModelPropertyCommand.h>
#include <ModelCommand.h>
#include <ModelsCommand.h>
#include <SceneCommand.h>
#include <BaseDrawer.h>
#include <DrawerSolution.h>
#include <QtFactory.h>
#include <Facade.h>

//struct scene_data
//{
//    VecD color = {0.5, 0.5, 0.5};
//    double specular = 0., reflective = 0., refractive = 0.;
//};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addCameraBtn_clicked();
    void on_cameraCB_currentIndexChanged(int index);
    void on_deleteCameraBtn_clicked();

    void on_addLightBtn_clicked();
    void on_lightCB_currentIndexChanged(int index);
    void on_deleteLightBtn_clicked();



    void on_loadModelBtn_clicked();
    void on_deleteModelBtn_clicked();
    void on_deleteModelsBtn_clicked();

    void on_upBtn_clicked();
    void on_rigthBtn_clicked();
    void on_downBtn_clicked();
    void on_leftBtn_clicked();
    void on_rightUpBtn_clicked();
    void on_rigntDownBtn_clicked();
    void on_leftDownBtn_clicked();
    void on_leftUpBtn_clicked();

    void on_transformFigureBtn_clicked();
    void on_transformAllBtn_clicked();
//    void on_scaleBtn_clicked();
//    void on_rotateBtn_clicked();
//    void on_moveAllBtn_clicked();
//    void on_scaleAllBtn_clicked();
//    void on_rotateAllBtn_clicked();

    void on_refractionSlide_valueChanged(int value);
    void on_transparencySlide_valueChanged(int value);
    void on_reflectanceSlide_valueChanged(int value);

    void on_intensitySlide_valueChanged(int value);
    void on_densitySlide_valueChanged(int value);

    void on_colorFlag_clicked();
    void on_textureFlag_clicked();
    void on_changeModelTextureBtn_clicked();
    void on_changeModelColorBtn_clicked();
    void on_changeLightColorBtn_clicked();
    void on_transformFigurePropertyBtn_clicked();


    void on_changeAmbientColorBtn_clicked();

protected:
    void setupScene();
    void updateScene();
    void checkCamExist();
    void checkLightExist();
    void checkModelsExist();
    void checkCamDelete();
    void checkLightDelete();

private:
    Ui::MainWindow *ui;
    //QGraphicsScene *_scene;
    std::shared_ptr<QGraphicsScene> _scene;
    std::shared_ptr<Facade> _facade;
    std::shared_ptr<BaseDrawer> _drawer;

    std::vector<std::size_t> _models;
    std::vector<std::size_t> _cameras;
    std::vector<std::size_t> _lights;
    std::size_t _camInd = 0;
    std::size_t _lightInd = 0;
    std::size_t _modInd = 0;
};
#endif // MAINWINDOW_H
