#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tracker.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QPixmap>
#include <QFileDialog>
#include <QList>
#include <QCheckBox>
#include <QColorDialog>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private:
    void initialize();
    void setVideoCapture();
    void buttonGroup();
    void cbxConnections();
    void setEnabledButtons();
    void openColorPalette();


public slots:
    void updateGUI();
    QString openFile();
    void verifyButtonIsClicked(int id);
    void verifyCbxIsChecked();

private slots:
    void on_btnPause_clicked();
    void on_btnOpenFile_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture _capture;
    cv::Mat _frameOriginal;
    QImage _imgOrgianl;
    QTimer *_timer;
    QString _videoPath;

    ot::Tracker tracker;

};

#endif // MAINWINDOW_H
