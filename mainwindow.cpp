#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->tableUser, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(changeUser(QTableWidgetItem* )));

    //on défini le nom du fichier qui contient les utilisateurs
    userFileName = "/home/mvanlerberghe/qt/GestionUtilisateur/users.txt";

    //etendre la dernière collonne jusqu'au bout du tableau
    ui->tableUser->horizontalHeader()->setStretchLastSection(true);


    //quand on cliquer sur "ajouter" dans le menu groupe
    connect(ui->pushButtonAddGroup, SIGNAL(clicked()), this, SLOT(createGroup()));
    //quand on clique sur "ajouter" dans le menu utilisateur
    connect(ui->pushButtonAjouterUser, SIGNAL(clicked()), this, SLOT(createUser()));
    //quand on clique sur ">>" (ajouter un groupe à un utilisateur) dans le menu utilisateur
    connect(ui->pushButtonUserAddGroup, SIGNAL(clicked()), this, SLOT(addGroupToUser()));
    //quand on clique sur "<<" (enlever un groupe à un utilisateur) dans le menu utilisateur
    connect(ui->pushButtonUserRemoveGroup, SIGNAL(clicked()), this, SLOT(removeGroupFrommUser()));

    //quand on change un élément du formulaire des groupes on vérifie le formulaire
    connect(ui->lineEditGroupLibelle, SIGNAL(textChanged(QString)), this, SLOT(checkFormGroup()));
    connect(ui->spinBoxGroupNum, SIGNAL(valueChanged(int)), this, SLOT(checkFormGroup()));
    connect(ui->plainTextEditGroupe, SIGNAL(textChanged()), this, SLOT(checkFormGroup()));

    //quand on change un élément du formulaire des utilisateurs on vérifie le formulaire
    connect(ui->lineEditLogin, SIGNAL(textChanged(QString)), this, SLOT(checkFormUser()));
    connect(ui->lineEditMDP, SIGNAL(textChanged(QString)), this, SLOT(checkFormUser()));
    connect(ui->lineEditMDPConfirmation, SIGNAL(textChanged(QString)), this, SLOT(checkFormUser()));
    connect(ui->lineEditMail, SIGNAL(textChanged(QString)), this, SLOT(checkFormUser()));
    connect(ui->lineEditNom, SIGNAL(textChanged(QString)), this, SLOT(checkFormUser()));
    connect(ui->lineEditPrenom, SIGNAL(textChanged(QString)), this, SLOT(checkFormUser()));

    qDebug()<<"MainWindow Créée";

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkFormGroup()
{
    ui->pushButtonAddGroup->setEnabled(ui->lineEditGroupLibelle->text().length()>0 && ui->spinBoxGroupNum->text().length()>0 && ui->plainTextEditGroupe->toPlainText()>0);
}

void MainWindow::checkFormUser()
{
    ui->pushButtonAjouterUser->setEnabled(false);
    //on vérifie que tout les champs sont remplis
    if(ui->lineEditLogin->text().length()*ui->lineEditMail->text().length()*ui->lineEditMDP->text().length()*ui->lineEditMDPConfirmation->text().length()*ui->lineEditNom->text().length()*ui->lineEditPrenom->text().length()==0)
    {
        //QMessageBox::warning(this, "Champ(s) vide(s)","Tout les champs doivent être remplis");
    }
    else
    {
        //on verifie le mot de passe
        if(ui->lineEditMDP->text()!=ui->lineEditMDPConfirmation->text())
        {
            ui->lineEditMDPConfirmation->setStyleSheet("background-color: red");
        }
        else
        {
            ui->lineEditMDPConfirmation->setStyleSheet("background-color: white");
            //on vérifie le format de l'adresse mail
            if(!ui->lineEditMail->text().contains('@'))
            {
                ui->lineEditMail->setStyleSheet("background-color: red");
                //QMessageBox::warning(this, "Adresse mail","L'adresse mail doit contenir un arobase");
            }
            //si tout est ok dans le formulaire
            else
            {
                    ui->lineEditMail->setStyleSheet("background-color: white");
                    ui->pushButtonAjouterUser->setEnabled(true);
            }
        }
    }
}

void MainWindow::resetFormUser()
{
    //on vide les champs    //on vérifie qu'un groupe est sélectionnée
    if(ui->userGroups1->selectedItems().length()>0)
    {
        ui->userGroups2->addItem(ui->userGroups1->takeItem(ui->userGroups1->selectedItems().indexOf(ui->userGroups1->selectedItems()[0])));
    }
    ui->lineEditLogin->clear();
    ui->lineEditMail->clear();
    ui->lineEditMDP->clear();
    ui->lineEditMDPConfirmation->clear();
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();

    //on reset leurs couleurs au cas où il y'aurais eu des warnings
    ui->lineEditMDP->setStyleSheet("color: black");
    ui->lineEditMDPConfirmation->setStyleSheet("color: black");
    ui->lineEditMail->setStyleSheet("color: black");
}

void MainWindow::fillGroupsList()
{
    //on vide la liste
    /*ui->userGroups1->clear();

    for(uint i = 0; ui->tableGroups->rowCount()-1; i++)
    {
        ui->userGroups1->addItem(new QListItem);
    }*/
}

void MainWindow::changeUser(QTableWidgetItem* user)
{
    //this->currentUser = user;
    qDebug()<<"changeUser";
    qDebug()<<"x:"<<user->column();
    qDebug()<<"y:"<<user->row();
}

QStringList MainWindow::getGroupesFromForm()
{
    QStringList groupes;
    //on laisse la première place de la liste vide qui sera le groupe principal
    groupes.append("");
    //pour chaque item de la liste des groupes de l'utilisateur dans le formulaire
    for(int i = 0; i < ui->userGroups2->count();i++)
    {
        groupes.append(ui->userGroups2->item(i)->text());
    }

    return groupes;                ui->pushButtonAjouterUser->setEnabled(true);
}

void MainWindow::addGroupToUser()
{
    //on vérifie qu'un groupe est sélectionnée
    if(ui->userGroups1->selectedItems().length()>0)
    {
        //on l'enlève de la liste des groupes non ajouté et on le met dans la liste des groupes ajoutés
        ui->userGroups2->addItem(ui->userGroups1->takeItem(ui->userGroups1->row(ui->userGroups1->selectedItems()[0])));
    }

    //on met la couleur du premier item en jaune pour indiquer que c'est l'utilisateur principal
    ui->userGroups2->item(0)->setBackgroundColor(QColor("yellow"));
}

void MainWindow::removeGroupFrommUser()
{
    //on vérifie qu'un groupe est sélectionnée
    if(ui->userGroups2->selectedItems().length()>0)
    {
        QListWidgetItem* item = ui->userGroups2->takeItem(ui->userGroups2->row(ui->userGroups2->selectedItems()[0]));
        //on l'enlève de la liste des groupes ajouté et on le met dans la liste des groupes non ajoutés
        ui->userGroups1->addItem(item);

        //on change sa couleur en blanc
        item->setBackgroundColor(QColor("white"));

        //on change la couleur du premier élément de l'autre liste en jaune s'il existe
        if(ui->userGroups2->count()>0)
            ui->userGroups2->item(0)->setBackgroundColor(QColor("yellow"));
    }
}

void MainWindow::createUser()
{
    qDebug()<<"test";
    //on créer un QStringList contenant les infos de l'utilisateur
    QStringList user;
    user.append(ui->lineEditLogin->text()); //login
    user.append(ui->lineEditMail->text());  //mail
    user.append(ui->lineEditNom->text());   //nom
    user.append(ui->lineEditPrenom->text());    //prenom

    //ajout de l'utilistateur à l'interface avec la liste ses informations et la liste de ses groupes
    addUserToUi(user, getGroupesFromForm());

    //on vide le formulaire
    resetFormUser();

    //ajustement de la largeur des collones du tableau
    ui->tableUser->resizeColumnsToContents();
}

void MainWindow::createGroup()
{
    //on vérifie que tout les champs sont remplis
    if(ui->spinBoxGroupNum->text().length()==0||ui->lineEditGroupLibelle->text().length()==0)
    {
        QMessageBox::warning(this, "Champ(s) vide(s)","Tout les champs doivent être remplis");
    }
    else
    {
        //on vérifie que le groupe n'existe pas déjà
        bool existeDeja = false;
        int i = 0;
        while(i<ui->tableGroups->rowCount() && !existeDeja)
        {
            existeDeja = (ui->tableGroups->item(i, 0)->text() ==  ui->spinBoxGroupNum->text() || ui->tableGroups->item(i, 1)->text() == ui->lineEditGroupLibelle->text());
            i++;
        }
        if(existeDeja)
        {
            QMessageBox::warning(this, "Erreur", "Le groupe que vous essayer de créer existe déjà");
        }
        else
        {
            //on créer une QStringList qui contient les informations du groupe
            QStringList group;
            group.append(ui->spinBoxGroupNum->text());  //numéro du groupe
            group.append(ui->lineEditGroupLibelle->text()); //nom du groupe
            group.append(ui->plainTextEditGroupe->toPlainText()); //déscription du groupe

            //on ajoute le groupe contenu dans le QStringList à l'interface
            addGroupToUI(group);
        }
    }
}

void MainWindow::addGroupToUI(QStringList group)
{
    //dans le tableau des groupes
        //on ajoute une ligne
        ui->tableGroups->setRowCount(ui->tableGroups->rowCount()+1);

        //on remplit la ligne avec les données du formulaire
        ui->tableGroups->setItem(ui->tableGroups->rowCount()-1, 0, new QTableWidgetItem(group[0]));
        ui->tableGroups->setItem(ui->tableGroups->rowCount()-1, 1, new QTableWidgetItem(group[1]));
        ui->tableGroups->setItem(ui->tableGroups->rowCount()-1, 2, new QTableWidgetItem(group[2]));

    //dans la liste des groupes du formulaire de création des utilisateurs
        //on ajoute une ligne
        ui->userGroups1->addItem(group[1]);
}

void MainWindow::addUserToUi(QStringList user, QStringList groups)
{
    //ajout d'une ligne dans le tableau
    ui->tableUser->setRowCount(ui->tableUser->rowCount()+1);

    //remplissage de la ligne avec les données du formulaire
    ui->tableUser->setVerticalHeaderItem(ui->tableUser->rowCount()-1, new QTableWidgetItem(user[0]));
    ui->tableUser->setItem(ui->tableUser->rowCount()-1, 0, new QTableWidgetItem(user[1]));
    ui->tableUser->setItem(ui->tableUser->rowCount()-1, 1, new QTableWidgetItem(user[2]));
    ui->tableUser->setItem(ui->tableUser->rowCount()-1, 2, new QTableWidgetItem(user[3]));
    ui->tableUser->setItem(ui->tableUser->rowCount()-1, 3, new QTableWidgetItem(groups[0]));
    //ui->tableUser->setItem(ui->tableUser->rowCount()-1, 4, new QTableWidgetItem(""));

    /*for(int i = 1; i < groups.size(); i++)
    {
        ui->tableUser->item(ui->tableUser->rowCount()-1, 4)->text().append(groups[i]);
    }*/
    //ui->tableUser->setItem(ui->tableUser->rowCount()-1, 4, new QTableWidgetItem(groups[1]));
    resetFormUser();

    //ajustement de la largeur des collones du tableau
    ui->tableUser->resizeColumnsToContents();
}

void MainWindow::deleteUser()
{

}

void MainWindow::modifyUser()
{

}

void MainWindow::loadUsers()
{
    ui->tableUser->clearContents();
    ui->tableUser->setRowCount(0);
    QFile file(userFileName);
    if(!file.open(QFile::ReadOnly))
    {
        statusBar()->showMessage("Impossible d'ouvrir le fichier des utilisateurs");
    }
    else
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QStringList user = in.readLine().split(";");
            //ajout d'une ligne dans le tableau
            ui->tableUser->setRowCount(ui->tableUser->rowCount()+1);

            //remplissage de la ligne
            ui->tableUser->setVerticalHeaderItem(ui->tableUser->rowCount()-1, new QTableWidgetItem(user[0]));
            ui->tableUser->setItem(ui->tableUser->rowCount()-1, 0, new QTableWidgetItem(user[1]));
            ui->tableUser->setItem(ui->tableUser->rowCount()-1, 1, new QTableWidgetItem(user[2]));
            ui->tableUser->setItem(ui->tableUser->rowCount()-1, 2, new QTableWidgetItem(user[3]));
        }
    }
}

void MainWindow::saveUsers()
{
    QFile file(userFileName);
    if(!file.open(QFile::WriteOnly))
    {
        statusBar()->showMessage("Impossible d'ouvrir le fichier des utilisateurs");
    }
    else
    {
        QTextStream out(&file);
        for(uint row = 0; row < ui->tableUser->rowCount(); row++)
        {
            out<<ui->tableUser->verticalHeaderItem(row)->text()<<";";
            for(uint column = 0; column < ui->tableUser->columnCount()-2; column++)
            {
                out<<ui->tableUser->item(row, column)->text()<<";";
            }
            out<<endl;
        }
    }
}

void MainWindow::on_pushButtonSetToGroupePrincipal_clicked()
{
    //on vérifie qu'un groupe est sélectionnée
    if(ui->userGroups2->selectedItems().length()>0)
    {
        //on met les background de tout les items blancs
        for(int i = 0; i < ui->userGroups2->count(); i++)
            ui->userGroups2->item(i)->setBackgroundColor(QColor("white"));
        ui->userGroups2->insertItem(0, ui->userGroups2->takeItem(ui->userGroups2->row(ui->userGroups2->selectedItems()[0])));

        //on met la couleur du premier item en jaune pour indiquer que c'est l'utilisateur principal
        ui->userGroups2->item(0)->setBackgroundColor(QColor("yellow"));
    }
}

void MainWindow::on_action_Sauvegarde_triggered()
{
    saveUsers();
}

void MainWindow::on_action_Ouvrir_triggered()
{
    loadUsers();
}

