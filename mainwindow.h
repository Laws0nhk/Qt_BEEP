#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFile>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QPushButton *pushButton;
    QFile file;
    void setBeepState();
    bool getBeepState();

private slots:
    void pushButtonClicked();
};

#endif // MAINWINDOW_H
