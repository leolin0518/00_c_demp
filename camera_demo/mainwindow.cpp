#include "mainwindow.h"
#include "ui_mainwindow.h"

//参考代码来自:
//https://blog.csdn.net/Star_ID/article/details/127195698
//https://blog.csdn.net/Star_ID/article/details/127195698

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("调用摄像头demo");
    ui->pushButton_start->setText("打开摄像头");
    ui->pushButton_screen->setText("截图");
    ui->pushButton_quit->setText("关闭摄像头");

    cameras = QCameraInfo::availableCameras();   //获取所有相机的列表
    qDebug() << __LINE__ << "this is camera: ";

    if (cameras.count() > 0) {
        for(const QCameraInfo &cameraInfo:cameras) {
            qDebug() << cameraInfo.description();
        }
        camera = new QCamera(cameras.at(0));     //初始化实例化一个相机对象
    }



//设置取景器
    viewfinder = new QCameraViewfinder(this);    //创建一个取景器
    camera->setViewfinder(viewfinder);
    viewfinder->resize(600,350);                 //设置取景器显示大小



    imageCapture = new QCameraImageCapture(camera); //创建一个截图实例
    camera->setCaptureMode(QCamera::CaptureStillImage); //设定截图的捕获模式

    ui->verticalLayout->addWidget(viewfinder);
    connect(imageCapture,SIGNAL(imageCaptured(int,QImage)),this,SLOT(onImageCaptured(int,QImage)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_start_clicked()
{
    camera->start();

//注意：设置摄像头参数需要打开摄像头后才可设置

//设置默认摄像头参数
    QCameraViewfinderSettings set;
    set.setResolution(640, 480);                 //设置显示分辨率

//    set.setMaximumFrameRate(25);                 //设置帧率,注释掉，打开摄像头无法开启
//    set.setMinimumFrameRate(15.0);
//    set.setMaximumFrameRate(30.0);

    camera->setViewfinderSettings(set);

    //添加初始化的相机选项
    for(const QCameraInfo &cameraInfo:cameras)
    {
        qDebug() << __LINE__ <<  "CameraInfo:" << cameraInfo;
    }


    //添加初始化相机的分辨率选项
    mResSize = camera->supportedViewfinderResolutions();
    qDebug() <<  __LINE__ << "mResSize = " << mResSize;
    for (const QSize &msize:mResSize)
    {
           qDebug() <<  __LINE__ <<  msize; //摄像头支持分辨率打印
    }

}


void MainWindow::on_pushButton_screen_clicked()
{
    qDebug()<<"开始截图";
    ui->label_screenShot->clear();
    imageCapture->capture();

    //保存截图文件
//    QString fileName = QFileDialog::getSaveFileName();
//    camera->searchAndLock();
//    imageCapture->capture(fileName);
//    camera->unlock();
}

void MainWindow::onImageCaptured(int idx, QImage img)
{
    qDebug()<<idx;
    QImage scaledimg;
    scaledimg = img.scaled(ui->label_screenShot->width(), ui->label_screenShot->height(),Qt::KeepAspectRatio );

    ui->label_screenShot->setPixmap(QPixmap::fromImage(scaledimg));
}


void MainWindow::on_pushButton_quit_clicked()
{
     camera->stop();

     ui->label_screenShot->clear();

}

