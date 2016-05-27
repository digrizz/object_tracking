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
//    if(_capture->isOpened())
//        _capture->release();

    _timer->deleteLater();
//    delete _capture;
    delete ui;
}

void MainWindow::initialize()
{
    _videoPath = QString();

    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()),
            this, SLOT(updateGUI()));

    _timer->start(20);
}

QString MainWindow::openFile()
{
    auto fileName = QFileDialog::getOpenFileName(this,tr("Open Video File"), "'C:\'", tr("Video Files (*.mp4 *.mkv)"));
    return fileName;
}

void MainWindow::setVideoCapture()
{
    QFileInfo video(_videoPath);
    if(video.exists())
    {
        const std::string path = _videoPath.toUtf8().constData();
        _capture = cv::VideoCapture(path);

        if(!_capture.isOpened())
            qDebug() << "error: capture not accessed successfuly";
    }
}

void MainWindow::updateGUI()
{
    (_capture) >> _frameOrginal;

    if(_frameOrginal.empty())
        return;

    _capture.read(_frameOrginal);

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

void MainWindow::on_btnOpenFile_clicked()
{
    _videoPath = openFile();
    setVideoCapture();
}
