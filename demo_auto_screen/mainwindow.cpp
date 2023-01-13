#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDebug>
#include <QGuiApplication>
#include <QScreen>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QFont font;
//    font.setPointSize(40);
//    ui->label->setFont(font);
    ui->textEdit->clear();

    //获取主屏分辨率
    QRect mRect;
    mRect = QGuiApplication::primaryScreen()->geometry();
    qDebug()<<"width:"<<mRect.width()<<"  height:"<<mRect.height();
    QString current_sc = "主屏分辨率:" + QString::number(mRect.width()) + "*" + QString::number(mRect.height());
    ui->label->setText(current_sc);




    // 获取多显示器,通过list存储当前主机所有显示器
    QList<QScreen *> list_screen = QGuiApplication::screens();
    QString msg = QString("检测到一共") +  QString::number( list_screen.size() ) + QString("屏幕.");
    qDebug() << msg;
    // 通过循环可以遍历每个显示器
    for (int i = 0; i < list_screen.size(); i++)
    {
        QRect rect = list_screen.at(i)->geometry();
        int desktop_width = rect.width();
        int desktop_height = rect.height();
        // 打印屏幕分辨率
        qDebug() << desktop_width <<desktop_height;
        QString screen_info = QString::number(desktop_width) + "*" + QString::number (desktop_height);
        ui->textEdit->append(msg + "编号:" + QString::number(i) + ", " +  screen_info);
    }


    ui->label->setAlignment(Qt::AlignHCenter);
    ui->textEdit->setAlignment(Qt::AlignHCenter);

    this->resize(mRect.width(), mRect.height());

}

MainWindow::~MainWindow()
{
    delete ui;
}

