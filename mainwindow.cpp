#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Rajouter le menu
    fileMenu = menuBar()->addMenu(tr("File"));
    fileGroup = new QActionGroup(fileMenu);
    newFile = new QAction(tr("Nouvelle liste"),fileGroup);
    openFile = new QAction(tr("Ouvrir une liste"),fileGroup);
    saveFile = new QAction(tr("Sauvegarder"),fileGroup);
    saveFileAs = new QAction(tr("Sauvegarder sous"),fileGroup);
    mergeWith = new QAction(tr("Fusionner une autre liste dans cette liste"),fileGroup);
    loadOldVersion = new QAction(tr("Charger une version antérieure d'une liste"),fileGroup);
    //actions du menu
    fileMenu->addActions(fileGroup->actions());
    connect(saveFile,SIGNAL(triggered(bool)),
            this,SLOT(sauvegarder()));
    connect(openFile,SIGNAL(triggered(bool)),
            this,SLOT(chargerListe()));
    connect(newFile,SIGNAL(triggered(bool)),
            this,SLOT(nouvelleListe()));
    connect(saveFileAs,SIGNAL(triggered(bool)),
            this,SLOT(sauvegarderSous()));
    connect(mergeWith, SIGNAL(triggered(bool)),
            this,SLOT(fusionnerAutreListe()));
    connect(loadOldVersion, SIGNAL(triggered(bool)),
            this,SLOT(chargerAnterieur()));


    listMenu = menuBar()->addMenu(tr("Liste"));
    listGroup = new QActionGroup(listMenu);
    setAllPresent = new QAction(tr("Mettre tous les joueurs présents"),listGroup);
    setAllAbsent = new QAction(tr("Mettre tous les joueurs absents"),listGroup);
    listMenu->addActions(listGroup->actions());
    connect(setAllPresent,SIGNAL(triggered(bool)),
            this,SLOT(tousPresents()));
    connect(setAllAbsent,SIGNAL(triggered(bool)),
            this,SLOT(tousAbsents()));


    //Bouton ajout de joueur
    connect(ui->btnAjouter,SIGNAL(pressed()),
            this, SLOT(createPlayer()));
    //Sur changement de joueur selectionne
    connect(ui->listWidget, SIGNAL(currentRowChanged(int)),
            this,SLOT(chargerJoueur(int)));
    connect(ui->btnModifier, SIGNAL(pressed()),
            this, SLOT(debuterModification()));
    connect(ui->btnCompleterModif, SIGNAL(pressed()),
            this,SLOT(finirModification()));
    connect(ui->btnAnnulerModif, SIGNAL(pressed()),
            this,SLOT(annulerModification()));
    connect(ui->btnEffacer, SIGNAL(pressed()),
            this,SLOT(effacerJoueur()));
    connect(ui->boxRecherche, SIGNAL(textChanged(QString)),
            this, SLOT(recherche(QString)));
    connect(ui->btnPresence,SIGNAL(pressed()),
            this, SLOT(ajouterPresence()));
    this->enableModifications(false);


    this->addClasses(this->ui->boxClasse);
    this->addRaces(this->ui->boxRace);
    this->addGroupes(this->ui->boxGroupe);

    //TODO demander a la liste de se charger
    Liste::getInstance();
    Liste::highestId =0;

    //TODO Imprimer les notes pour chaque joueur present??
    //TODO Connecter tous les signaux

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::tousPresents(){
    Liste::getInstance()->setPresenceTous(true);
    updateList();
}
void MainWindow::tousAbsents(){
    Liste::getInstance()->setPresenceTous(false);
    updateList();
}

void MainWindow::chargerAnterieur(){
    QString fichier = QFileDialog::getOpenFileName(this,tr("Choississez une liste"), "", tr("Bin files (*.bin)"));
    OldListe* tmp = new OldListe;
    tmp->setFichier(fichier.toStdString());
    tmp->lectureChargerOldListe();
    Liste* instance = Liste::getInstance();
    instance->viderListe();

    for(int i = 0 ; i < tmp->getNbOldJoueurs(); i ++){
        instance->ajouterJoueur(new Joueur(tmp->getOldJoueur(i),tmp));
    }
    updateList();
}

void MainWindow::fusionnerAutreListe(){
    QString fichier = QFileDialog::getSaveFileName(this, tr("Choississez une liste"), "", tr("Xml Files (*.xml)"));
    Liste* autreListe = xml::readList(fichier.toStdString());
    Liste* instance = Liste::getInstance();
    for(int i = 0 ; i < autreListe->getNbJoueurs(); i++){
        instance->ajouterJoueur(autreListe->getJoueur(i));
    }
    updateList();
}

void MainWindow::resizeEvent(QResizeEvent* event){
   /*
    int totalWidth = event->size().width(),
            totalHeight = event->size().height();
    int oldWidth = event->oldSize().width(),
            oldHeight = event->oldSize().height();

    int deltaWidth = totalWidth - oldWidth,
            deltaHeight = totalHeight - oldHeight;
    int specificWidth = deltaWidth / 3;
    int specificHeight = deltaHeight;
    int midHeight = deltaHeight/3;

    this->ui->listWidget->resize(this->ui->listWidget->size().width() + specificWidth,
                                 this->ui->listWidget->size().height() + specificHeight);
    this->ui->layoutMid1->setGeometry(QRect(this->ui->layoutMid1->geometry().left() + specificWidth,
                                            this->ui->layoutMid1->geometry().top(),
                                            this->ui->layoutMid1->geometry().width() + specificWidth,
                                            this->ui->layoutMid1->geometry().height() + midHeight));
    this->ui->layoutMid2->setGeometry(QRect(this->ui->layoutMid2->geometry().left() + specificWidth,
                                            this->ui->layoutMid2->geometry().top() + midHeight,
                                            this->ui->layoutMid2->geometry().width() + specificWidth,
                                            this->ui->layoutMid2->geometry().height() + midHeight));
    this->ui->layoutMid3->setGeometry(QRect(this->ui->layoutMid3->geometry().left() + specificWidth,
                                            this->ui->layoutMid3->geometry().top() + 2*midHeight,
                                            this->ui->layoutMid3->geometry().width() + specificWidth,
                                            this->ui->layoutMid3->geometry().height() + midHeight));
    this->ui->layoutRight1->setGeometry(QRect(this->ui->layoutRight1->geometry().left() + 2*specificWidth,
                                            this->ui->layoutRight1->geometry().top(),
                                            this->ui->layoutRight1->geometry().width() + specificWidth,
                                            this->ui->layoutRight1->geometry().height() + specificHeight));
*/

}

void MainWindow::sauvegarder(){
    Liste::getInstance()->sauvegarderListe();
}
void MainWindow::sauvegarderSous(){
    QString fichier = QFileDialog::getSaveFileName(this, tr("Choississez une liste"), "", tr("Xml Files (*.xml)"));

    Liste::getInstance()->sauvegarderListe(fichier.toStdString());
}

void MainWindow::nouvelleListe(){
    Liste::getInstance()->viderListe();
    updateList();
}
void MainWindow::chargerListe(){
    QString fichier = QFileDialog::getOpenFileName(this, tr("Choississez une liste"), "", tr("Xml Files (*.xml)"));
    Liste::getInstance()->setInstance(Liste::chargerListe(fichier.toStdString()));
    updateList();
}

void MainWindow::ajouterPresence(){
    if(this->ui->listWidget->currentRow() != -1){
        Joueur* tmp = Liste::getInstance()->getJoueur(this->ui->listWidget->currentRow());
        unsigned char niveau = tmp->getNiveau();
        tmp->rajouterExperience(1);
        tmp->setPresent(true);

        chargerJoueur(this->ui->listWidget->currentRow());
        if(tmp->getNiveau() != niveau){
            QMessageBox box;
            box.setText(tr("Le joueur est maintenant de niveau : ") + QString::number(tmp->getNiveau()));
            box.exec();
        }
    }
}

void MainWindow::updateList(){
    this->ui->listWidget->clear();
    getStatistics();
    Liste* instance = Liste::getInstance();
    instance->trier();
    for(int i = 0 ; i < instance->getNbJoueurs(); i ++){
        Joueur* tmp = instance->getJoueur(i);

        new QListWidgetItem(QString::fromStdString(tmp->toString()),
                            this->ui->listWidget);
    }

}
void MainWindow::getStatistics(){           //Cette fonction a l'air de fonctionner uniquement lors des ajouts de joueurs... i dont get it

    Liste* instance = Liste::getInstance();
    string recherche = instance->getRecherche();
    instance->recherche("");
    vector<int> niveaux;
    double ageMoyen = 0.0, niveauMoyen = 0.0;
    int* groupes = new int[Systeme::NOMBRE_GROUPES];
    for(int i = 0; i < Systeme::NOMBRE_GROUPES; i++)
        groupes[i] = 0;
    for(int i = 0 ; i < instance->getNbJoueurs(); i++){

        Joueur* tmp = instance->getJoueur(i);
        if(tmp->getPresent()){
            niveaux.push_back(tmp->getNiveau());
            ageMoyen+= (double)tmp->getAge();
            niveauMoyen += (double)tmp->getNiveau();
            if(tmp->getGroupe()!= -1)
                groupes[tmp->getGroupe()]+=1;
        }
    }
    int niveauMedian=0;
    ageMoyen = ageMoyen / (double)niveaux.size();
    sort(niveaux.begin(),niveaux.end());
    if(niveaux.size() > 0)
        niveauMedian = niveaux[niveaux.size()/2];
    niveauMoyen = niveauMoyen/(double)niveaux.size();

    this->ui->lblAgeMoyen->setText(QString::number(ageMoyen));
    this->ui->lblMedian->setText(QString::number(niveauMedian));
    this->ui->lblMoyenne->setText(QString::number(niveauMoyen));
    this->ui->lblJoueurPresent->setText(QString::number(niveaux.size()));
    this->ui->lblArmada->setText(QString::number(groupes[Systeme::ARMADA]));
    this->ui->lblFanatique->setText(QString::number(groupes[Systeme::FANATIQUES]));
    this->ui->lblErebe->setText(QString::number(groupes[Systeme::EREBE]));
    this->ui->lblRegiment->setText(QString::number(groupes[Systeme::REGIMENT]));
    this->ui->lblDracosire->setText(QString::number(groupes[Systeme::DRACOSIRE]));

    niveaux.clear();
    delete groupes;
    instance->recherche(recherche);

}

void MainWindow::debuterModification(){
    if(this->ui->listWidget->currentRow()!= -1)
        enableModifications(true);
}
void MainWindow::finirModification(){
    enableModifications(false);
    Joueur* tmp = Liste::getInstance()->getJoueur(this->ui->listWidget->currentRow());
    tmp->setNom(this->ui->boxJoueur->text().toStdString());
    tmp->setPerso(this->ui->boxPersonnage->text().toStdString());
    tmp->setClasse(this->ui->boxClasse->currentIndex());
    tmp->setRace(this->ui->boxRace->currentIndex());
    tmp->setGroupe(this->ui->boxGroupe->currentIndex());
    tmp->setPresent(this->ui->boxPresent->isChecked());
    tmp->setExp(this->ui->boxExp->value());
    tmp->setNotes(this->ui->boxNotes->toPlainText().toStdString());
    tmp->modified();
    this->ui->listWidget->currentItem()->setText(QString::fromStdString(tmp->toString()));
    getStatistics();
}
void MainWindow::annulerModification(){
    enableModifications(false);
    chargerJoueur(this->ui->listWidget->currentRow());
}
void MainWindow::effacerJoueur(){
    //TODO
}
void MainWindow::recherche(QString search){

    Liste::getInstance()->recherche(search.toStdString());

    updateList();
}

void MainWindow::chargerJoueur(int pos){
    if(pos != -1){
        Joueur* tmp = Liste::getInstance()->getJoueur(pos);
        this->ui->boxJoueur->setText(QString::fromStdString(tmp->getNom()));
        this->ui->boxPersonnage->setText(QString::fromStdString(tmp->getPerso()));
        this->ui->boxAge->setText(QString::number(tmp->getAge()));
        this->ui->boxPresent->setChecked(tmp->getPresent());
        this->ui->boxClasse->setCurrentIndex(tmp->getClasse());
        this->ui->boxRace->setCurrentIndex(tmp->getRace());
        this->ui->boxGroupe->setCurrentIndex(tmp->getGroupe());
        this->ui->boxNiveau->setValue(tmp->getNiveau());
        this->ui->boxExp->setValue(tmp->getExp());
        this->ui->boxNotes->setPlainText(QString::fromStdString(tmp->getNotes()));
        this->ui->btnPresence->setEnabled(!tmp->getPresent());
    }
    else{
        this->ui->boxJoueur->setText(tr(""));
        this->ui->boxPersonnage->setText(tr(""));
        this->ui->boxAge->setText(tr(""));
        this->ui->boxPresent->setChecked(false);
        this->ui->boxClasse->setCurrentIndex(-1);
        this->ui->boxRace->setCurrentIndex(-1);
        this->ui->boxGroupe->setCurrentIndex(-1);
        this->ui->boxNiveau->setValue(0);
        this->ui->boxNiveau->setValue(0);
        this->ui->boxExp->setValue(0);
        this->ui->boxNotes->clear();
        this->ui->btnPresence->setEnabled(false);
    }
}
void MainWindow::enableModifications(bool enable){
    this->ui->boxJoueur->setEnabled(enable);
    this->ui->boxPersonnage->setEnabled(enable);
    this->ui->boxAge->setEnabled(enable);
    this->ui->boxPersonnage->setEnabled(enable);
    this->ui->boxPresent->setEnabled(enable);
    this->ui->boxClasse->setEnabled(enable);
    this->ui->boxRace->setEnabled(enable);
    this->ui->boxGroupe->setEnabled(enable);
    this->ui->boxNiveau->setEnabled(enable);
    this->ui->boxExp->setEnabled(enable);
    this->ui->boxNotes->setEnabled(enable);

    this->ui->btnAnnulerModif->setVisible(enable);
    this->ui->btnCompleterModif->setVisible(enable);
    this->ui->btnEffacer->setVisible(enable);

    this->ui->btnPresence->setEnabled(!enable);
    this->ui->listWidget->setEnabled(!enable);


}

void MainWindow::addRaces(QComboBox* box){
    box->clear();
    box->addItem(tr("Humain"));
    box->addItem(tr("Elfe"));
    box->addItem(tr("Orc"));
    box->setCurrentIndex(-1);
}
void MainWindow::addClasses(QComboBox* box){
    box->clear();
    box->addItem(tr("Bretteur"));
    box->addItem(tr("Fantassin"));
    box->addItem(tr("Dévot"));
    box->addItem(tr("Paladin"));
    box->addItem(tr("Assassin"));
    box->addItem(tr("Éclaireur"));
    box->addItem(tr("Mage"));
    box->setCurrentIndex(-1);
}
void MainWindow::addGroupes(QComboBox* box){
    box->clear();
    box->addItem(tr("Armada"));
    box->addItem(tr("Fanatiques de sang"));
    box->addItem(tr("Érèbe"));
    box->addItem(tr("Régiment oublié"));
    box->addItem(tr("Ordre du dracosire"));
    box->setCurrentIndex(-1);
}

void MainWindow::createPlayer(){
    Ajouter wnd;
    wnd.setModal(true);
    wnd.exec();

    updateList();


}
