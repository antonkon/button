#include "mainwindow.h"
#include <QMessageBox>
#include <QPoint>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(640, 200);
    this->setWindowTitle("Проверка класса Button");

    but = new Button("кнопка", this);
    but->setEnabled(false);
    connect(but, SIGNAL(clicked()),
        this, SLOT(show_message()));

    Button *but1 = new Button("кнопка", this);
    but1->move(150, 0);
    connect(but1, SIGNAL(clicked()), this, SLOT(setEnableBut()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::show_message() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Проверка");
    msgBox.setText("Кнопка нажалась и заблокировалась");
    msgBox.exec();

    this->but->setEnabled(false);
}

void MainWindow::setEnableBut() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Проверка");
    msgBox.setText("Разблокировали первую кнопку");
    msgBox.exec();

    this->but->setEnabled(true);
}
