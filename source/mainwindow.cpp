#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initialize();
    ui->setupUi(this);
    Logger::getInstance()->warning("test");
}

MainWindow::~MainWindow()
{
    if(_capture->isOpened())
        _capture->release();

    _timer->deleteLater();
    delete _capture;
    delete ui;
}

void MainWindow::initialize()
{
    _capture = new cv::VideoCapture(0);

    if(_capture->isOpened() == false)
    {
        qDebug() << "error: capture not accessed successfuly";
        return;
    }

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()),
            this, SLOT(updateGUI()));

    _timer->start(20);
}

void MainWindow::updateGUI()
{
    (*_capture) >> _frameOrginal;

    if(_frameOrginal.empty())
        return;

    _capture->read(_frameOrginal);

    cv::cvtColor(_frameOrginal, _frameOrginal, CV_BGR2RGB);

    QImage output((const unsigned char*) _frameOrginal.data, _frameOrginal.cols, _frameOrginal.rows, _frameOrginal.step, QImage::Format_RGB888);

    ui->lblImgOrginal->setPixmap(QPixmap::fromImage(output));

}

void MainWindow::on_btnPause_clicked()
{
    if(_timer->isActive() == true)
    {
        _timer->stop();
        ui->btnPause->setText("Resume");
    }
    else
    {
        _timer->start(20);
        ui->btnPause->setText("Pause");
    }
}
