
#include "Liste.h"


Liste* Liste::instance = NULL;
int Liste::highestId;
Liste::Liste()
{
}


Liste::~Liste()
{
    while(joueurs_.size() != 0)
        delete joueurs_.front();
}

int Liste::getNbJoueurs() {
    if (researchPrefix.length()>0)
        return searchJoueurs_.size();
	return joueurs_.size();
}
void Liste::ajouterJoueur(Joueur* joueur) {

    //Si c'est un nouveau joueur, lui attribuer un Id et l'ajouter
    if(joueur->getId() == 0 ){
        highestId+=1;
        joueur->setId(highestId);
        joueurs_.push_back(joueur);
    }
    else{

        if(joueur->getId()>highestId)
            highestId = joueur->getId();
        bool found = false;
        //Chercher si un jouer avec le même id existe déjà
        for(int i = 0 ; i < joueurs_.size();i++){

            //Si c'est le cas
            if(!found&&joueurs_[i]->getId() == joueur->getId()){

                //Ajouter le nouveau joueur s'il est plus récent
                if(joueurs_[i]->getLastModified() < joueur->getLastModified()){
                    retirerJoueur(i);
                    joueurs_.push_back(joueur);
                }
                //Ne rien faire sinon
                found = true;

            }
        }
        //S'il n'existe pas déjà, l'ajouter à la liste
        if(!found){
            joueurs_.push_back(joueur);
        }
    }
    recherche(researchPrefix);
}
void Liste::retirerJoueur(int position) { //À TESTER!!!!!!!!!!!!!!!
    if(researchPrefix.length() > 0){

        Joueur* toDelete = searchJoueurs_[position];
        for(int i = 0 ; i < joueurs_.size();i++){
            if(joueurs_[i]->getId() == toDelete->getId()){
                string tmp = researchPrefix;
                recherche("");
                this->retirerJoueur(i);
                recherche(tmp);
                return;
            }
        }
    }
    delete joueurs_[position];
	joueurs_[position] = joueurs_.back();
	joueurs_.pop_back();
    if(researchPrefix.length()>0){
        recherche(researchPrefix);
   }
}
Joueur *Liste::getJoueur(int position) {

        if (researchPrefix.length()>0)
            return searchJoueurs_[position];

        else
            return joueurs_[position];
}
string Liste::getfichier() {
    return fichier_;
}

void Liste::setInstance(Liste *liste)
{
 instance = liste;
}
void Liste::setFichier(string fichier) {

	vieuFichier_ = fichier_;

	fichier_ = fichier;

}

void Liste::setPresenceTous(bool presence)
{
 for(int i = 0; i < joueurs_.size(); i ++)
     joueurs_[i]->setPresent(presence);
}
void Liste::viderListe() {
	joueurs_.clear();
    this->searchJoueurs_.clear();
    this->highestId = 0;
}
Liste* Liste::chargerListe(string fichier)
{
    Liste* tmp =  xml::readList(fichier);
    tmp->setFichier(fichier);
    return  tmp;
}
void Liste::sauvegarderListe() {
    if(fichier_!= "")
        this->sauvegarderListe(fichier_);
}
void Liste::sauvegarderListe(string fichier) {
    xml::writeList(this,fichier);
    this->fichier_ = fichier;
}
string Liste::fileName(string fichier, string nomJoueur) {
	int extensionLength = 4;

	//trouve le nom de l'ancien fichier de note selon les conventions
    string file = fichier.erase(fichier.length() - extensionLength);
    fichier += "_notes_" + nomJoueur + ".txt";
	return file;
}
void Liste::transfererNotesJoueur(string autreFichier, string nomJoueur) {
	
	/*
	wstring oldFile = fileName(autreFichier, nomJoueur);

	wstring notes, temporaire;

	ifstream lecture(autreFichier, ios::beg);
	if (!lecture.fail()) {
		//lecture du contenu de l'ancien fichier de note
		while (!lecture.eof()) {
			getline(lecture, temporaire);
			notes += temporaire;
			notes += "\n";
		}
		lecture.close();

		//trouve le nouveau nom de fichier de note selon les conventions
		string newFile = fileName(fichier_, nomJoueur);

		//transfert du contenu dans un nouveau fichier de note
		ofstream ecrire(newFile, ios::trunc);
		ecrire << notes << endl;
		ecrire.close();
	}
	else {
		lecture.close();
	}
	*/
}
struct JoueurCompare{
    bool operator()(Joueur* left, Joueur* right){
        return left->getNom() < right->getNom();
    }
};

void Liste::trier() {
    sort(joueurs_.begin(), joueurs_.end(),JoueurCompare());
    sort(searchJoueurs_.begin(),searchJoueurs_.end(),JoueurCompare());
}

string Liste::getRecherche()
{
    return researchPrefix;
}
void Liste::recherche(string prefixe) {
    this->searchJoueurs_.clear();
    if(prefixe.length() > 0){

        for(int i = 0 ; i < prefixe.length(); i++)
            prefixe[i] = std::tolower(prefixe[i]);


        for (int i = 0; i < joueurs_.size(); i++) {
            string nom = joueurs_[i]->getNom();
            for(int j = 0 ; j < nom.length(); j++)
                nom[j] = std::tolower(nom[j]);

            if (nom.find(prefixe) != string::npos)
                this->searchJoueurs_.push_back(joueurs_[i]);
        }
    }
    this->researchPrefix = prefixe;
}
