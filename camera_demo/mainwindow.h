#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QFileDialog>
#include <QList>
#include <QDebug>


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
    void on_pushButton_start_clicked();

    void on_pushButton_screen_clicked();

    void onImageCaptured(int idx,QImage img);

    void on_pushButton_quit_clicked();

private:
    Ui::MainWindow *ui;

    QCamera *camera;                   //相机
    QCameraViewfinder *viewfinder;     //取景器
    QCameraImageCapture *imageCapture; //图像捕获
    QList<QCameraInfo> cameras;        //相机列表
    QList<QSize> mResSize = {};        //分辨率列表

};
#endif // MAINWINDOW_H
