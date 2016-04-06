#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Ajouter.h"
#include "Liste.h"
#include "xml.h"
#include "Class_Liste.h"
#include <QMainWindow>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QResizeEvent>
#include <QFileDialog>
namespace Ui {
class MainWindow;

}
class ControllerMainWindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Menu d'action avec clic droit

    //Il pourrait etre interessant de mettre les

    void updateList();
    static void addRaces(QComboBox *box);
    static void addClasses(QComboBox *box);
    static void addGroupes(QComboBox *box);
    void enableModifications(bool enable);
    void getStatistics();
public slots:
    void createPlayer();
    void chargerJoueur(int pos);
    void debuterModification();
    void finirModification();
    void annulerModification();
    void effacerJoueur();
    void recherche(QString search);
    void ajouterPresence();
    void sauvegarder();
    void nouvelleListe();
    void chargerListe();
    void sauvegarderSous();
    void fusionnerAutreListe();
    void chargerAnterieur();
    void tousPresents();
    void tousAbsents();
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
    QMenu* fileMenu, *listMenu;
    QAction *saveFile, *saveFileAs,*openFile,*newFile,*mergeWith, *loadOldVersion,
                *setAllPresent, *setAllAbsent;
    QActionGroup* fileGroup, *listGroup;
};

#endif // MAINWINDOW_H
