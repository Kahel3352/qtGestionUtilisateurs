#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableUser, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(changeUser(QTableWidgetItem* )));
    qDebug()<<"MainWindow Créée";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeUser(QTableWidgetItem user)
{
    //this->currentUser = user;
    qDebug()<<"changeUser";
}

void MainWindow::addUser()
{

}

void MainWindow::deleteUser()
{

}

void MainWindow::modifyUser()
{

}
