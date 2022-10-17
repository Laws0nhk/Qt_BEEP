#include "mainwindow.h"
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
        QList<QScreen *> list = QGuiApplication::screens();         //获取所有屏幕
#if __arm__
    this->resize(list.at(0)->geometry().width(),
                 list.at(0)->geometry().height());
#else
    this->resize(800, 480);
#endif

    pushButton = new QPushButton(this);
    pushButton->setMinimumSize(200, 50);
    pushButton->setGeometry((this->width() - pushButton->width()) / 2,
                           (this->height() - pushButton->height()) / 2,
                           pushButton->width(), pushButton->height());

    file.setFileName("/sys/devices/platform/leds/leds/beep/brightness");    //寻找蜂鸣器的控制接口
    if(!file.exists()) {
        pushButton->setText("未获取到BEEP设备");
    }
    getBeepState();
    connect(pushButton, &QPushButton::clicked, this, &MainWindow::pushButtonClicked);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setBeepState()
{
    bool state = getBeepState();
    if (!file.exists())
        return;
    if (!file.open(QIODevice::ReadWrite))
        qDebug() << file.errorString();

    QByteArray buf[2] = {"0", "1"};
    if (state)
       file.write(buf[0]);
    else
        file.write(buf[1]);
    file.close();
    getBeepState();
}

bool MainWindow::getBeepState()
{
    if (!file.exists())
        return false;
    if (!file.open(QIODevice::ReadWrite))
        qDebug() << file.errorString();

    QTextStream in(&file);
    QString buf = in.readLine();
    qDebug() << "buf: " << buf << endl;
    if (buf == 1) {
        pushButton->setText("BEEP 开");
        return true;
    } else {
        pushButton->setText("BEEP 关");
        return false;
    }
}

void MainWindow::pushButtonClicked()
{
    setBeepState();
}
