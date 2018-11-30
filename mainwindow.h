#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "button.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Button *but;

public slots:
    void show_message();
    void setEnableBut();

};

#endif // MAINWINDOW_H
