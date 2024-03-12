#include <cmath>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Exceptions.hpp"
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupScene();

    ui->colorPreview->setScene(new QGraphicsScene);
    ui->texturePreview->setScene(new QGraphicsScene(0, 0, ui->texturePreview->width(), ui->texturePreview->height()));
    ui->colorLightPreview->setScene(new QGraphicsScene);
    ui->colorAmbientPreview->setScene(new QGraphicsScene);

    ui->label_refraction->setNum(0);
    ui->label_transparency->setNum(0);
    ui->label_reflectivity->setNum(0);

    ui->label_intensity->setNum(0);
    ui->label_density->setNum(0);

    _facade = std::make_shared<Facade>(Facade());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScene()
{
    _scene = std::make_shared<QGraphicsScene>(this);

    ui->graphicsView->setScene(_scene.get());

    auto cont = ui->graphicsView->contentsRect();
    _scene->setSceneRect(0, 0, cont.width(), cont.height());

    ui->tabWidget->setTabText(2, "Модели");
    ui->tabWidget->setTabText(0, "Камеры");
    ui->tabWidget->setTabText(1, "Свет и среда");

    _camInd = 1;
    _lightInd = 1;

    auto solution(new DrawerSolution<QtFactory, QGraphicsScene>());
    _drawer = solution->createDrawer(_scene.get());
}

void MainWindow::updateScene()
{
    auto scene = std::make_shared<Scene>();
    ClearScene clear_cmd(_drawer);
    _facade->execute(clear_cmd);

    GetScene get_scene_cmd(scene);
    _facade->execute(get_scene_cmd);


    DrawScene draw_cmd(scene, _drawer);
    _facade->execute(draw_cmd);

}

void MainWindow::checkCamExist()
{
    if (!_cameras.size())
    {
        std::string msg = "Камеры не найдены";
        throw CameraException(msg);
    }
}

void MainWindow::checkLightExist()
{
    if (!_cameras.size())
    {
        std::string msg = "Источники света не найдены";
        throw LightException(msg);
    }
}

void MainWindow::checkModelsExist()
{
    if (!_models.size())
    {
        std::string msg = "Модели не найдены";
        throw ModelException(msg);
    }
}

void MainWindow::checkCamDelete()
{
    if (_cameras.size() <= 1 && _models.size())
    {
        std::string msg = "Имеются объекты на сцене";
        throw CameraException(msg);
    }
}

void MainWindow::checkLightDelete()
{
    if (_lights.size() <= 1 && _models.size())
    {
        std::string msg = "Имеются объекты на сцене";
        throw LightException(msg);
    }
}

void MainWindow::on_addCameraBtn_clicked()
{
    auto cont = ui->graphicsView->contentsRect();

    auto id = std::make_shared<size_t>(0);
    AddCamera addCMD(id, cont.width(), cont.height());

    _facade->execute(addCMD);
    _cameras.push_back(*id);

    updateScene();

    auto cam = ui->cameraCB;

    std::string camName = std::string("Camera") + std::to_string(_camInd++);
    cam->addItem(QString(camName.data()));

    ui->cameraCB->setCurrentIndex(ui->cameraCB->count() - 1);
}

void MainWindow::on_addLightBtn_clicked()
{
    auto cont = ui->graphicsView->contentsRect();

    auto id = std::make_shared<size_t>(0);
    VecD location({cont.width() / 2.0, cont.height() / 2.0, 1000});
    VecD direction({0, 0, 0});
    // !!!
    AddLight addCMD(id, location, direction, lightType::ambient);

    _facade->execute(addCMD);
    _lights.push_back(*id);

    updateScene();

    auto light = ui->lightCB;

    std::string lightName = std::string("Light") + std::to_string(_lightInd++);
    light->addItem(QString(lightName.data()));

    ui->lightCB->setCurrentIndex(ui->lightCB->count() - 1);
}

void MainWindow::on_loadModelBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Добавьте камеру!");
        return;
    }

    auto path = QFileDialog::getOpenFileName(nullptr, "Загрузка модели", "../course_cg/models/cube.obj");

    if (path.isNull())
        return;

    std::shared_ptr<BaseObject> model = std::make_shared<SurfaceModel>();
    auto id = std::make_shared<size_t>(0);
    std::string pathFileName = path.toStdString();

    try
    {
        LoadModel load_cmd(model, pathFileName);
        _facade->execute(load_cmd);

        AddModel add_cmd(id, model);
        _facade->execute(add_cmd);
    }
    catch (const BaseException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при загрузке файла!");
        return;
    }

    _models.push_back(*id);

    updateScene();

    _modInd++;
    auto fileName = QFileInfo(path.toUtf8().data()).fileName();
    QString figName = QString("SurfaceModel") + QString::number(_modInd) + QString(" load from ") + QString(fileName);
    ui->modelsCB->addItem(figName);
    ui->modelsCB->setCurrentIndex(ui->modelsCB->count() - 1);
}

void MainWindow::on_deleteModelBtn_clicked()
{
    try
    {
        checkModelsExist();
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    std::size_t id = _models.at(ui->modelsCB->currentIndex());
    RemoveModel cmd(id);
    _facade->execute(cmd);

    _models.erase(_models.begin() + ui->modelsCB->currentIndex());
    ui->modelsCB->removeItem(ui->modelsCB->currentIndex());

    updateScene();
}

void MainWindow::on_deleteModelsBtn_clicked()
{
    try
    {
        checkModelsExist();
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет загруженных моделей!");
        return;
    }

    for (int i = ui->modelsCB->count() - 1; i >= 0; --i)
    {
        std::size_t id = _models.at(i);
        RemoveModel cmd(id);
        _facade->execute(cmd);

        _models.erase(_models.begin() + i);
        ui->modelsCB->removeItem(i);
    }

    updateScene();
}


void MainWindow::on_cameraCB_currentIndexChanged(int index)
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        return;
    }

    std::size_t id = _cameras.at(index);
    SetCamera cmd(id);
    _facade->execute(cmd);

    updateScene();
}

void MainWindow::on_lightCB_currentIndexChanged(int index)
{
    try
    {
        checkLightExist();
    }
    catch (const LightException &error)
    {
        return;
    }

    std::size_t id = _lights.at(index);
    SetLight cmd(id);
    _facade->execute(cmd);

    updateScene();
}

void MainWindow::on_deleteLightBtn_clicked()
{
    try
    {
        checkLightExist();
    }
    catch (const LightException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет истончиков света!");
        return;
    }

    try
    {
        checkLightDelete();
    }
    catch (const LightException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Это последняя камера! Для удаления удалите модели!");
        return;
    }

    std::size_t id = _lights.at(ui->lightCB->currentIndex());
    RemoveCamera cmd(id);
    _facade->execute(cmd);

    _lights.erase(_lights.begin() + ui->lightCB->currentIndex());
    ui->lightCB->removeItem(ui->lightCB->currentIndex());

    try
    {
        checkLightExist();
    }
    catch (const LightException &error)
    {
        return;
    }

    updateScene();
}



void MainWindow::on_deleteCameraBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }

    try
    {
        checkCamDelete();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Это последняя камера! Для удаления удалите модели!");
        return;
    }

    std::size_t id = _cameras.at(ui->cameraCB->currentIndex());
    RemoveCamera cmd(id);
    _facade->execute(cmd);

    _cameras.erase(_cameras.begin() + ui->cameraCB->currentIndex());
    ui->cameraCB->removeItem(ui->cameraCB->currentIndex());

    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        return;
    }

    updateScene();
}

void MainWindow::on_upBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
    _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, 0, 10, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_downBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, 0, -10, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_rigthBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, -10, 0, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_rightUpBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, -10, 10, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_rigntDownBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, -10, -10, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_leftBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, 10, 0, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_leftUpBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();
    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, 10, 10, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}

void MainWindow::on_leftDownBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    auto camera = make_shared<Camera>();

    GetMainCamera get_camera(camera);
   _facade->execute(get_camera);

    TransformCamera transform_cmd(camera, 10, -10, 0, 0, 0);
    _facade->execute(transform_cmd);

    updateScene();
}


void MainWindow::on_transformFigureBtn_clicked()
{
    try
    {
        checkCamExist();
        checkLightExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет каркасных фигур!");
        return;
    }

    shared_ptr<BaseObject> model = std::make_shared<SurfaceModel>();

    GetSceneObject get_object_cmd(model, _models.at(ui->modelsCB->currentIndex()));
    _facade->execute(get_object_cmd);

    MoveModel move_cmd(model, ui->dxDSB->value(), ui->dyDSB->value(), ui->dzDSB->value());
    _facade->execute(move_cmd);

    ScaleModel scale_cmd(model,
            ui->kxDSB->value(),
            ui->kyDSB->value(),
            ui->kzDSB->value());
    _facade->execute(scale_cmd);

    RotateModel rotate_cmd(model,
            ui->oxDSB->value() * M_PI / 180,
            ui->oyDSB->value() * M_PI / 180,
            ui->ozDSB->value() * M_PI / 180);
    _facade->execute(rotate_cmd);


    updateScene();
}

void MainWindow::on_transformAllBtn_clicked()
{
    try
    {
        checkCamExist();
        checkLightExist();
        checkModelsExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет камер!");
        return;
    }
    catch (const ModelException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Нет моделей!");
        return;
    }

    auto composite = std::make_shared<Composite>();
    GetSceneObjects get_objs(composite);
    _facade->execute(get_objs);

    MoveModels move_cmd(composite,
            ui->dxDSB->value(),
            ui->dyDSB->value(),
            ui->dzDSB->value());

    _facade->execute(move_cmd);

    ScaleModels scale_cmd(composite,
            ui->kxDSB->value(),
            ui->kyDSB->value(),
            ui->kzDSB->value());
    _facade->execute(scale_cmd);

    RotateModels rotate_cmd(composite,
            ui->oxDSB->value() * M_PI / 180,
            ui->oyDSB->value() * M_PI / 180,
            ui->ozDSB->value() * M_PI / 180);
    _facade->execute(rotate_cmd);
    updateScene();
}


void MainWindow::on_refractionSlide_valueChanged(int value)
{
//   ui->label_refraction->setNum(value / 100);
   ui->label_refraction->setText(QString::number(value / 100., 'f', 1));

//   ChangeModelProperties()
}


void MainWindow::on_transparencySlide_valueChanged(int value)
{
    ui->label_transparency->setText(QString::number(value / 100., 'f', 1));
}


void MainWindow::on_reflectanceSlide_valueChanged(int value)
{
    ui->label_reflectivity->setText(QString::number(value / 100., 'f', 1));
}


void MainWindow::on_intensitySlide_valueChanged(int value)
{
    ui->label_intensity->setText(QString::number(value / 100., 'f', 1));
}


void MainWindow::on_densitySlide_valueChanged(int value)
{
    ui->label_density->setText(QString::number(value / 100., 'f', 1));
}


void MainWindow::on_colorFlag_clicked()
{
    ui->changeModelColorBtn->setDisabled(false);
    ui->changeModelTextureBtn->setDisabled(true);
}


void MainWindow::on_textureFlag_clicked()
{
    ui->changeModelTextureBtn->setDisabled(false);
    ui->changeModelColorBtn->setDisabled(true);
}


void MainWindow::on_changeModelTextureBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите текстуру", "/Users/elizavetaladygina/Desktop/BMSTU/course_project/textures/",
                                                    "JPG (*.jpg);;PNG (*.png)");
    QImage img;
    if (!img.load(fileName))
        return;

    ui->texturePreview->scene()->addPixmap(QPixmap::fromImage(
                                            img.scaled(ui->texturePreview->width(), ui->texturePreview->height())
                                            ));

    shared_ptr<BaseObject> model = std::make_shared<SurfaceModel>();

    GetSceneObject get_object_cmd(model, _models.at(ui->modelsCB->currentIndex()));
    _facade->execute(get_object_cmd);

    ChangeModelTexture cmd(model, img);
    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_changeModelColorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::gray, this, QStringLiteral("Выберите цвет модели"));
    if (!color.isValid()) return;
    auto cred = QString::number(color.red()).toFloat();
    auto cgreen = QString::number(color.green()).toFloat();
    auto cblue = QString::number(color.blue()).toFloat();

    ui->colorPreview->scene()->setBackgroundBrush(QColor(cred, cgreen, cblue));
}

void MainWindow::on_transformFigurePropertyBtn_clicked()
{
    try
    {
        checkCamExist();
    }
    catch (const CameraException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одной камеры.");
        return;
    }

    shared_ptr<BaseObject> model = std::make_shared<SurfaceModel>();
    GetSceneObject get_object_cmd(model, _models.at(ui->modelsCB->currentIndex()));
    _facade->execute(get_object_cmd);

    if (ui->colorFlag->isChecked())
    {
        QColor color = ui->colorPreview->scene()->backgroundBrush().color();

        auto cred = QString::number(color.red()).toFloat();
        auto cgreen = QString::number(color.green()).toFloat();
        auto cblue = QString::number(color.blue()).toFloat();

        ChangeModelColor changeColor_cmd(model, cred, cgreen, cblue);
        _facade->execute(changeColor_cmd);
    }
    //
    if (ui->textureFlag->isChecked())
        ;

    ChangeModelProperties changeProperties_cmd(model, ui->transparencySlide->value(), ui->reflectanceSlide->value(), ui->intensitySlide->value());
    _facade->execute(changeProperties_cmd);

    updateScene();
}


void MainWindow::on_changeLightColorBtn_clicked()
{
    try
    {
        checkLightExist();
    }
    catch (const LightException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одного источника.");
        return;
    }
    auto light = make_shared<Light>();
    GetLight get_light(light);

    _facade->execute(get_light);

    QColor color = QColorDialog::getColor(Qt::gray, this, QStringLiteral("Выберите цвет источника"));
    if (!color.isValid()) return;
    auto cred = QString::number(color.red()).toFloat();
    auto cgreen = QString::number(color.green()).toFloat();
    auto cblue = QString::number(color.blue()).toFloat();
    ui->colorLightPreview->scene()->setBackgroundBrush(QColor(cred, cgreen, cblue));

    ChangeLightColor cmd(light, cred / 255., cgreen / 255., cblue / 255.);
    _facade->execute(cmd);
    updateScene();
}


void MainWindow::on_changeAmbientColorBtn_clicked()
{
    try
    {
        checkCamExist();
        checkLightExist();
    }
    catch (const LightException &error)
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не загружено ни одного источника.");
        return;
    }

    bool flag = false;

    QColor color = QColorDialog::getColor(Qt::gray, this, QStringLiteral("Выберите цвет источника"));
    if (!color.isValid()) return;
    auto cred = QString::number(color.red()).toFloat();
    auto cgreen = QString::number(color.green()).toFloat();
    auto cblue = QString::number(color.blue()).toFloat();
    ui->colorLightPreview->scene()->setBackgroundBrush(QColor(cred, cgreen, cblue));

    auto light = make_shared<Light>();
    for (auto &ind: _lights)
    {
        GetLightByInd cmd(light, ind);

        if (light->getType() == lightType::ambient)
        {
            flag = true;
            ChangeLightColor change_cmd(light, cred / 255., cgreen / 255., cblue / 255.);
            _facade->execute(cmd);
        }
    }

    if (flag)
        updateScene();
}
