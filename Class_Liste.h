/****************************************************************************
* Fichier: Class_OldListe.h
* Auteur: Gabriel Cote-Carrier
* Date: juin 2015
* Description: 	Definition de la classe OldListe qui sert à contenir
*				un ensemble de OldJoueurs qui pourra être affiché par le
*				dialogue principal
****************************************************************************/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "Class_Joueur.h"

using namespace std;

#ifndef _OldListe_H_
#define _OldListe_H_
class OldListe 	{

public:
    OldListe();
    ~OldListe();
    int getNbOldJoueurs();
    void ajouterOldJoueur(const OldJoueur& oldJoueur);
    void retirerOldJoueur(const int& position);
    OldJoueur& getOldJoueur(int& position);
    string getfichier();
    void setFichier(const string& fichier);
    void viderOldListe();
	int lectureGetNbElements();
    void lectureChargerOldListe();
	bool lectureFichierExiste();
    void sauvegarderOldListe();
    void transfererNotesOldJoueur(string autreFichier, char* nomOldJoueur);
	void trier();
	
private:
    std::vector<OldJoueur> OldJoueurs_;
    string fichier_, vieuFichier_;
};
#endif

