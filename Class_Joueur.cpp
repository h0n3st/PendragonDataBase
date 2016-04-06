/****************************************************************************
* Fichier: Class_OldJoueur.cpp
* Auteur: Gabriel Cote-Carrier
* Date: juin 2015
* Description: 	Definition de la classe Add qui est un dialogue
*				permettant à l'usager de rajouter un OldJoueur
*				à la Liste en usage dans le programme
****************************************************************************/

#include "Class_Joueur.h"

//Constructeur de base
//Donne par défaut des valeurs aux attributs booléens du OldJoueur
OldJoueur::OldJoueur()
{
	visible_ = true;
	present_ = false;
	inscrit_ = false;
}
//Destructeur par défaut
OldJoueur::~OldJoueur()
{
}
/*
    OldJoueur::getTel
	Paramètres : aucun
	Retour : 	char* l'attribut telephone_
*/
char* OldJoueur::getTel(){

	return telephone_;
}
/*
    OldJoueur::getNom
	Paramètres : aucun
	Retour : 	char* l'attribut nom_
*/
char* OldJoueur::getNom(){

	return nom_;
}
/*
    OldJoueur::getPresent
	Paramètres : aucun
	Retour : 	bool l'attribut present_
*/
bool OldJoueur::getPresent(){

	return present_;
}
/*
    OldJoueur::getInscrit
	Paramètres : aucun
	Retour : 	bool l'attribut inscrit_
*/
bool OldJoueur::getInscrit(){

	return inscrit_;
}
/*
    OldJoueur::getVibisble
	Paramètres : aucun
	Retour : 	bool l'attribut visible_
*/
bool OldJoueur::getVisible(){

	return visible_;
}
/*
    OldJoueur::setTelephone
	Paramètres : char* le nouveau contenu de telephone_
	Retour : 	aucun
*/
void OldJoueur::setTelephone(char* telephone){

    std::strcpy(this->telephone_, telephone);
}
/*
    OldJoueur::setNom
	Paramètres : char* le nouveau contenu de nom_
	Retour : 	aucun
*/
void OldJoueur::setNom(char* nom){

    std::strcpy(this->nom_, nom);
}
/*
    OldJoueur::setPresent
	Paramètres : bool le nouveau contenu de present_
	Retour : 	aucun
*/
void OldJoueur::setPresent(const bool& present){

	this->present_ = present;
}
/*
    OldJoueur::setInscrit
	Paramètres : bool le nouveau contenu de inscrit_
	Retour : 	aucun
*/
void OldJoueur::setInscrit(const bool& inscrit){

	this->inscrit_ = inscrit;
}
/*
    OldJoueur::setVisible
	Paramètres : bool le nouveau contenu de visible_
	Retour : 	aucun
*/
void OldJoueur::setVisible(const bool& visible){

	this->visible_ = visible;
}
/*
    OldJoueur::setDateNaissance
	Paramètres : int, int, int la date de naissance sous format jour, mois, annee
	Retour : 	aucun
	La méthode calcule la date de naissance en tant que nombre de secondes écoulées
	depuis le 1er janvier 1970 et l'emmagasine dans l'attribut dateNaissance_
*/
void OldJoueur::setDateNaissance(int jour, int mois, int annee){

	const double SECONDES_PAR_JOUR = 86400;
	const double JOUR_PAR_AN = 365.25;
	const double JOUR_PAR_MOIS[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	//La précision du calcul n'a pas été vérifié
	dateNaissance_ =int( ((double(annee - 1970))*JOUR_PAR_AN + JOUR_PAR_MOIS[mois] + double(jour))*SECONDES_PAR_JOUR);

}
/*
    OldJoueur::getAge
	Paramètres : aucun
    Retour : 	int l'âge associé à la date de naissance du OldJoueur
*/
int OldJoueur::getAge(){

	const double SECONDES_PAR_JOUR = 86400;
	const double JOUR_PAR_AN = 365.25;
	int secondesParAn = SECONDES_PAR_JOUR*JOUR_PAR_AN;

    time_t temps = std::time(NULL);

	//Le calcul est imprécis de quelques jours
	int ageEnSecondes = temps - dateNaissance_;
	int ageEnAn = ageEnSecondes / secondesParAn;

	return ageEnAn;
}
/*
    OldJoueur::operator<
    Paramètres : OldJoueur l'autre OldJoueur avec lequel comparer le OldJoueur
	Retour : 	booléen indiquant le résultat de la comparaison
    Cette redéfinition de l'opérateur < compare uniquement les noms des OldJoueurs
    pour permettre de classer les objets OldJoueur en ordre alphabétique
*/
bool OldJoueur::operator< (OldJoueur& oldJoueur){

    bool plusPetit = std::string(this->nom_) < std::string(oldJoueur.nom_);
	
	return plusPetit;
}
