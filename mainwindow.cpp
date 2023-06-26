#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
//    ui->quickWidget->show();

    QQuickWidget *view = new QQuickWidget;
    view->setSource(QUrl("qrc:/main.qml"));
    ui->horizontalLayout->addWidget(view);

    QQuickWidget *butt = new QQuickWidget;
    butt->setSource(QUrl("qrc:/buttons.qml"));
    //ui->horizontalLayoutWidget_2->setStyleSheet();
    ui->horizontalLayout_2->addWidget(butt);


    QQuickWidget *panel = new QQuickWidget;
    panel->setSource(QUrl("qrc:/panel.qml"));
    ui->horizontalLayout_4->addWidget(panel);

    QQuickWidget *camera = new QQuickWidget;
    camera->setSource(QUrl("qrc:/camera.qml"));
    ui->horizontalLayout_3->addWidget(camera);

//    this->setWindowOpacity(0.35);
//    this->setAttribute(Qt::WA_TranslucentBackground, false);
//    this->setStyleSheet("background-color: yellow;");


}

MainWindow::~MainWindow()
{
    delete ui;
}
