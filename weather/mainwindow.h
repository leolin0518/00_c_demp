#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//菜单
#include <QContextMenuEvent>
//鼠标事件
#include <QMouseEvent>
//网络请求
#include <QNetworkAccessManager>
#include <QNetworkReply>
//提示框
#include <QMessageBox>
//Json
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>
#include <WeatherData.h>
//读取文件
#include <QFile>
//键值对
#include <QMap>
//绘制相关
#include <QPainter>
#include <QBrush>
#include <QPen>
//检查编译平台
#include <qglobal.h>
//一些参数宏increment
#define INCREMENT 1.5       //温度升高/降低1度 y轴移动的像素点增量
#define PAINT_RADIUS 3      //曲线描点的大小
#define TEXT_OFFSET_X 12    //温度文本X偏移
#define TEXT_OFFSET_Y 12    //温度文本Y偏移
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //退出的菜单
    QMenu* mExitMenu;
    //退出的行为
    QAction* mExitAction;
    //鼠标点击的pos距离左上角的pos的偏移
    QPoint mOffset;
    //网络请求
    QNetworkAccessManager* mNetworkAccessManager;
    //今天的数据
    Today mToday;
    //未来几天的数据
    Day mDay[6];
    //获取天气信息
    void getWeatherInfo(QString cityCode);
    //解析json数据
    void parseJson(QByteArray data);
    //去除多余内容,只保留int数据
    int parseString(QString str);
    //更新UI控件
    void updateUI();
    //UI的List 用于循环赋值
    QList<QLabel*> mDateList;
    QList<QLabel*> mWeekList;
    QList<QLabel*> mQulityList;
    QList<QLabel*> mTypeList;
    QList<QLabel*> mTypeIconList;
    QList<QLabel*> mFxList;
    QList<QLabel*> mFlList;
    QMap<QString, QString> mTypeMap;
    //检查空气质量
    int checkedQulity(int aqi);
    //高温曲线
    void paintHigtCurve();
    //低温曲线
    void paintLowCurve();
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *event);
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);
    //事件过滤器,默认无,需要重写
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    //请求成功后执行的槽函数,用于处理服务器返回的数据,例如解析等
    void onReplied(QNetworkReply* reply);
    //搜索按钮
    void onBtnSerchClicked();
};



//天气工具类
class weatherTool{
private:
    inline static QMap<QString, QString> mCityMap = {};
    static void initCityMap(){
        QFile fd(":/citycode.json");
        fd.open(QIODevice::ReadOnly | QIODevice::Text);
        //qDebug() << fd.isOpen();
        QByteArray json = fd.readAll();
        fd.close();
        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(json, &err);
        if (err.error != QJsonParseError::NoError || !doc.isArray()) {
            return;
        }
        QJsonArray rootArray = doc.array();
        //qDebug() << rootArray;
        for (int i = 0; i < rootArray.size(); ++i) {
           QString cityName = rootArray[i].toObject().value("city_name").toString();
           QString cityCode = rootArray[i].toObject().value("city_code").toString();
           //qDebug() << cityName << cityCode;
           //判断编号是否存在
           if (cityCode.size() > 0) {
               mCityMap.insert(cityName, cityCode);
           }
        }

    }
public:
    static QString getCityCode(QString cityName){
        //检查是否为空,为空先初始化
        if (mCityMap.isEmpty()) {
            initCityMap();
        }
        //在map寻找传入的城市名称,返回值可以遍历
        QMap<QString, QString>::iterator it = mCityMap.find(cityName);
        //到结尾了,未找到,加上市,再搜一遍
        if (it == mCityMap.end()) {
           it = mCityMap.find(cityName + "市");
        }
        //找到了
        if (it != mCityMap.end()) {
           return it.value();
        }
        //还是未找到,返回空值
        return "";
    }

};
#endif // MAINWINDOW_H
