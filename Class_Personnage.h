/****************************************************************************
* Fichier: Class_OldPersonnage.h
* Auteur: Gabriel Cote-Carrier
* Date: juin 2015
* Description: 	Définition de la classe OldPersonnage qui gère les données
*				associées au OldPersonnage d'un individu
****************************************************************************/

#ifndef OldPersonnage_H_
#define OldPersonnage_H_
#include <cstring>
class OldPersonnage{

public:

    OldPersonnage();
    ~OldPersonnage();

	char* getPerso();
	bool getGroupe();
	unsigned char getClasse();
	unsigned char getNiveau();
	unsigned char getExp();
	unsigned char getRace();
	unsigned short getRichesse();

	void setPerso(char* perso);
	void setClasse(const unsigned char& classe);
	void setExp(const unsigned char& experience);
	void setRace(const unsigned char& race);
	void setRichesse(const unsigned short& richesse);
	void setGroupe(const bool& groupe);
	void rajouterExperience();
	void calculerNiveau();


private:

    char OldPersonnage_[30];
	unsigned char classe_, niveau_, experience_, race_;
	unsigned short richesse_;
	bool groupe_;
};

#endif // !OldPersonnage_H_
