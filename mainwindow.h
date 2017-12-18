#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTableWidget currentUser;

private:
    Ui::MainWindow *ui;
    //ligne dans le tableau de l'utilisateur en cours d'édition

    void addUser();
    void deleteUser();
    void modifyUser();

public slots:

    //change l'utilisateur en cours d'édition
    void changeUser(QTableWidgetItem user);

};

#endif // MAINWINDOW_H
