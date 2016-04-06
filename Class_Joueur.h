/****************************************************************************
* Fichier: Class_OldJoueur.h
* Auteur: Gabriel Cote-Carrier
* Date: juin 2015
* Description: 	Definition de la classe OldJoueur qui est l'objet utilisé par le
*				programme pour contenir et afficher des données.
*				La classe OldJoueur gère les données associées à l'individu
*				tandis qu'elle hérite de la classe OldPersonnage pour pouvoir
*				également gérer les données associées au OldPersonnage de cet
*				individu
****************************************************************************/

#include <vector>
#include<ctime>
#include <string>
#include <cstring>
#include "Class_Personnage.h"

#ifndef _OldJoueur_H_
#define _OldJoueur_H_


class OldJoueur : public OldPersonnage {

public:
    OldJoueur();
    ~OldJoueur();
	char* getTel();
	char* getNom();
	bool getPresent();
	bool getInscrit();
	bool getVisible();
	int getAge();

	void setTelephone(char* telephone);
	void setNom(char* nom);
	void setPresent(const bool& present);
	void setInscrit(const bool& inscrit);
	void setVisible(const bool& visible);
	void setDateNaissance(int jour, int mois, int annee);
    int getDateNaissance() {return dateNaissance_;}

    bool operator< (OldJoueur& oldJoueur);

private:
	int dateNaissance_;
	char telephone_[15];
	char nom_[30];
	
	bool present_;
	bool inscrit_;
	bool visible_;

};


#endif
