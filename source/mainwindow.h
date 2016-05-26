#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QPixmap>

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

public slots:
    void updateGUI();


private slots:
    void on_btnPause_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture *_capture;
    cv::Mat _frameOrginal;
    QImage _imgOrgianl;
    QTimer *_timer;

};

#endif // MAINWINDOW_H
