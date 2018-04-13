#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QDebug>

/**
  @brief Fenêtre principale
*/
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /**
     * @brief contient la ligne du tableau de l'utilisateur en cours d'édition
     */
    QTableWidget currentUser;

    /**
     * @brief Nom du fichier qui contient les utilisateurs
     */
    QString userFileName;

    /**
     * @brief Remet tout les champs du formulaire à zero
     */
    void resetFormUser();

    /**
     * @brief Remplis la liste des groupes dans le formulaire de création d'utilisateur
     */
    void fillGroupsList();

    void deleteUser();
    void modifyUser();

    /**
     * @brief Remplis la liste des utilisateurs avec les informations contenu dans le fichier dont le nom est userFileName
     */
    void loadUsers();

    /**
     * @brief Sauvegarde dans le fichier des utilisateurs les utilisateurs dans le tableau
     */
    void saveUsers();

    /**
     * @brief Vérifie que le formulaire de groupe soit remplis
     * @return false si tout les champs ne sont pas remplis
     */

    //change l'utilisateur en cours d'édition
    void changeUser(QTableWidgetItem* user);

    /**
    * @return La liste des groupes de l'utilisteur avec en premier dans la liste le groupe principal
    */
    QStringList getGroupesFromForm();

    /**
     * @brief Ajoute un groupe dans les différentes listes qui contiennent les groupes
     * @param group QStringList contenant les informations du groupe
     * 0: id, 1: libelle, 2: déscription
     */
    void addGroupToUI(QStringList group);

    /**
     * @brief Ajoute un utilisateur au tableau des utilisateurs
     * @param user QStringList contenant les informations de l'utilisateurs
     * @param groups QStringList contenant les noms des groupes ou groups[0] est le groupe principal
     */
    void addUserToUi(QStringList user, QStringList groups);

private slots:
    void on_pushButtonSetToGroupePrincipal_clicked();
    void on_action_Sauvegarde_triggered();
    void on_action_Ouvrir_triggered();

    /**
     * @brief Ajoute un groupe à un utilisateur
     */
    void addGroupToUser();

    /**
     * @brief Enlève un groupe à un utilisateur
     */
    void removeGroupFrommUser();

    /**
     * @brief créer un utilisateur à partir du formulaire
     */
    void createUser();

    /**
     * @brief créer un groupe à partir du formulaire
     */
    void createGroup();

    /**
     * @brief Vérifie que le formulaire de groupe est bien remplis
     */
    void checkFormGroup();

    /**
     * @brief Vérifie que le formulaire d'utilisateur est bien remplis
     */
    void checkFormUser();
};

#endif // MAINWINDOW_H
