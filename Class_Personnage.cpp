/****************************************************************************
* Fichier: Class_OldPersonnage.cpp
* Auteur: Gabriel Cote-Carrier
* Date: juin 2015
* Description: 	Implémentation de la classe OldPersonnage qui gère les données
*				associées au OldPersonnage d'un individu
****************************************************************************/

#include "Class_Personnage.h"

//Constructeur de base
//donne par défaut une valeur nulle à richesse_
OldPersonnage::OldPersonnage(){

	richesse_ = 0;
}
//Destructeur par défaut
OldPersonnage::~OldPersonnage(){

}
/*
    OldPersonnage::getPerso
	Paramètres : aucun
    Retour : 	char* l'attribut OldPersonnage_
*/
char* OldPersonnage::getPerso(){

    return OldPersonnage_;
}
/*
    OldPersonnage::getGroupe
	Paramètres : aucun
	Retour : 	bool l'attribut groupe_
*/
bool OldPersonnage::getGroupe(){

	return groupe_;
}
/*
    OldPersonnage::getClasse
	Paramètres : aucun
	Retour : 	unsigned char l'attribut classe_
*/
unsigned char OldPersonnage::getClasse(){

	return classe_;
}
/*
    OldPersonnage::getNiveau
	Paramètres : aucun
	Retour : 	unsigned char l'attribut niveau_
*/
unsigned char OldPersonnage::getNiveau(){

	return niveau_;
}
/*
    OldPersonnage::getExp
	Paramètres : aucun
	Retour : 	unsigned char l'attribut experience_
*/
unsigned char OldPersonnage::getExp(){

	return experience_;
}
/*
    OldPersonnage::getRace
	Paramètres : aucun
	Retour : 	unsigned char l'attribut race_
*/
unsigned char OldPersonnage::getRace(){

	return race_;
}
/*
    OldPersonnage::getRichesse
	Paramètres : aucun
	Retour : 	unsigned char l'attribut richesse_
*/
unsigned short OldPersonnage::getRichesse(){

	return richesse_;
}
/*
    OldPersonnage::setPerso
    Paramètres : char* la nouvelle valeur de OldPersonnage_
	Retour : 	aucun
*/
void OldPersonnage::setPerso(char* perso){

    strcpy(OldPersonnage_, perso);
}
/*
    OldPersonnage::setClasse
	Paramètres : unsigned char la nouvelle valeur de classe_
	Retour : 	aucun
*/
void OldPersonnage::setClasse(const unsigned char& classe){

	this->classe_ = classe;
}
/*
    OldPersonnage::setExp
	Paramètres : unsigned char la nouvelle valeur de experience_
	Retour : 	aucun
	La méthode calcule également la nouvelle valeur de niveau_
	associée à la nouvelle valeur de experience_
*/
void OldPersonnage::setExp(const unsigned char& experience){

	this->experience_ = experience;
	calculerNiveau();
}
/*
    OldPersonnage::setRace
	Paramètres : unsigned char la nouvelle valeur de race_
	Retour : 	aucun
*/
void OldPersonnage::setRace(const unsigned char& race){

	this->race_ = race;
}
/*
    OldPersonnage::setRichesse
	Paramètres : unsigned short la nouvelle valeur de richesse_
	Retour : 	aucun
*/
void OldPersonnage::setRichesse(const unsigned short& richesse){

	this->richesse_ = richesse;
}
/*
    OldPersonnage::calculerNiveau
	Paramètres : aucun
	Retour : 	aucun
	La méthode calcule la valeur de niveau_ selon la valeur
	de l'attribut experience_
*/
void OldPersonnage::calculerNiveau(){

	if (experience_ >= 13){
		niveau_ = 5;
	}
	else if (experience_ >= 9){
		niveau_ = 4;
	}
	else if (experience_ >= 6){
		niveau_ = 3;
	}
	else if (experience_ >= 3){
		niveau_ = 2;
	}
	else{
		niveau_ = 1;
	}
}
/*
    OldPersonnage::setGroupe
	Paramètres : booléen la nouvelle valeur de groupe_
	Retour : 	aucun
*/
void OldPersonnage::setGroupe(const bool& groupe){
	this->groupe_ = groupe;
}
/*
    OldPersonnage::rajouterExpérience
	Paramètres : aucun
	Retour : 	aucun
	La méthode incrémente la valeur de l'attribut experience_
	jusqu'à concurrence de 20, puis calcule la valeur de niveau_ 
	associé à cette nouvelle valeur
*/
void OldPersonnage::rajouterExperience() {

	if (experience_<20)
	{
		this->experience_++;
	}
	calculerNiveau();
}
