#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logger.h"

#include "tracker.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    initialize();

    ot::Tracker t;          // it's here for test only
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
    ui->btnBlueEdit->setEnabled(false);
    ui->btnBlackEdit->setEnabled(false);
    ui->btnBrownEdit->setEnabled(false);
    ui->btnGreenEdit->setEnabled(false);
    ui->btnPinkEdit->setEnabled(false);
    ui->btnRedEdit->setEnabled(false);
    ui->btnWhiteEdit->setEnabled(false);
    ui->btnYellowEdit->setEnabled(false);

    buttonGroup();
    cbxConnections();

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

void MainWindow::buttonGroup()
{
    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->addButton(ui->btnWhiteEdit,0);
    btnGroup->addButton(ui->btnRedEdit,1);
    btnGroup->addButton(ui->btnYellowEdit,2);
    btnGroup->addButton(ui->btnGreenEdit,3);
    btnGroup->addButton(ui->btnBrownEdit,4);
    btnGroup->addButton(ui->btnBlueEdit,5);
    btnGroup->addButton(ui->btnPinkEdit,6);
    btnGroup->addButton(ui->btnBlackEdit,7);
    ui->btnBlackEdit->setEnabled(false);

    connect(btnGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(verifyButtonIsClicked(int)));

}

void MainWindow::cbxConnections()
{
    connect(ui->cbxWhiteBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxRedBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxYellowBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxGreenBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxBrownBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxBlueBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxPinkBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));

    connect(ui->cbxBlackBall, SIGNAL(clicked(bool)),
            this, SLOT(verifyCbxIsChecked()));
}

void MainWindow::setEnabledButtons()
{
    ui->btnBlueEdit->setEnabled(false);
    ui->btnBlackEdit->setEnabled(false);
    ui->btnBrownEdit->setEnabled(false);
    ui->btnGreenEdit->setEnabled(false);
    ui->btnPinkEdit->setEnabled(false);
    ui->btnRedEdit->setEnabled(false);
    ui->btnWhiteEdit->setEnabled(false);
    ui->btnYellowEdit->setEnabled(false);
}

void MainWindow::openColorPalette()
{
    QColor color = QColorDialog::getColor();
    qDebug() << "Red: " << color.red() << "\nGreen: " << color.green() << "\nBlue: " << color.blue();
}

void MainWindow::verifyButtonIsClicked(int id)
{
    openColorPalette();
}

void MainWindow::verifyCbxIsChecked()
{
    QList<QCheckBox *> listCbx = ui->groupBox->findChildren<QCheckBox*>();
    QList<int> listCbxElements;

    for(int i = 0; i < listCbx.size(); ++i)
    {
        if(listCbx.at(i)->isChecked())
        {
            switch (i)
            {
            case 0:
                ui->btnWhiteEdit->setEnabled(true);
                break;
            case 1:
                ui->btnRedEdit->setEnabled(true);
                //method
                break;
            case 2:
                ui->btnYellowEdit->setEnabled(true);
                //method
                break;
            case 3:
                ui->btnGreenEdit->setEnabled(true);
                //method
                break;
            case 4:
                ui->btnBrownEdit->setEnabled(true);
                //method
                break;
            case 5:
                ui->btnBlueEdit->setEnabled(true);
                //method
                break;
            case 6:
                ui->btnPinkEdit->setEnabled(true);
                //method
                break;
            case 7:
                ui->btnBlackEdit->setEnabled(true);
                //method
                break;
            default:
                setEnabledButtons();
                break;
            }
        }
        else
        {
            switch (i)
            {
            case 0:
                ui->btnWhiteEdit->setEnabled(false);
                //method
                break;
            case 1:
                ui->btnRedEdit->setEnabled(false);
                //method
                break;
            case 2:
                ui->btnYellowEdit->setEnabled(false);
                //method
                break;
            case 3:
                ui->btnGreenEdit->setEnabled(false);
                //method
                break;
            case 4:
                ui->btnBrownEdit->setEnabled(false);
                //method
                break;
            case 5:
                ui->btnBlueEdit->setEnabled(false);
                //method
                break;
            case 6:
                ui->btnPinkEdit->setEnabled(false);
                //method
                break;
            case 7:
                ui->btnBlackEdit->setEnabled(false);
                //method
                break;
            default:
                setEnabledButtons();
                break;
            }
        }
           listCbxElements << i;
    }
    qDebug() << "cbx chcecked: " << listCbxElements;
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
