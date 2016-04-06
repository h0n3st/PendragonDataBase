#include "Ajouter.h"
#include "ui_Ajouter.h"

Ajouter::Ajouter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ajouter)
{
    ui->setupUi(this);
    connect(ui->buttonBox, ui->buttonBox->accepted,this,this->ajouterJoueur);
    MainWindow::addClasses(this->ui->boxClasse);
    MainWindow::addRaces(this->ui->boxRace);
    MainWindow::addGroupes(this->ui->boxGroupe);
    setDates(this->ui->boxJour,
             this->ui->boxMois,
             this->ui->boxAnnee);
}

Ajouter::~Ajouter()
{
    delete ui;
}
void Ajouter::ajouterJoueur(){
    //TODO : code pour creer un joueur et l'ajouter a la liste
    std::string nom = this->ui->boxNom->text().toStdString(),
            personnage = this->ui->boxPersonnage->text().toStdString() ;
    int jour = this->ui->boxJour->currentIndex(),
            mois = this->ui->boxMois->currentIndex(),
            annee = this->ui->boxAnnee->currentIndex(),
            classe = this->ui->boxClasse->currentIndex(),
            race = this->ui->boxRace->currentIndex(),
            groupe = this->ui->boxGroupe->currentIndex(),
            experience = this->ui->boxExp->value();

    Joueur* tmp = new Joueur;
    tmp->setNom(nom);
    tmp->setPerso(personnage);
    const int STARTING_YEAR = 1995;
    tmp->setDateNaissance(jour,mois,annee + STARTING_YEAR);
    tmp->setClasse(classe);
    tmp->setRace(race);
    tmp->setGroupe(groupe);
    tmp->setExp(experience);
    tmp->setPresent(this->ui->boxPresent->isChecked());
    Liste::getInstance()->ajouterJoueur(tmp);

}

void Ajouter::setDates(QComboBox* jour, QComboBox* mois, QComboBox* annee){
    jour->clear();
    mois->clear();
    annee->clear();
    for(int i = 1; i <= 31; i ++)
        jour->addItem(QString::number(i));
    for(int i = 1; i <= 12; i++)
        mois->addItem(QString::number(i));
    for(int i = 1995; i <= 2010; i++){
        annee->addItem(QString::number(i));
    }
    jour->setCurrentIndex(-1);
    mois->setCurrentIndex(-1);
    annee->setCurrentIndex(-1);
}
