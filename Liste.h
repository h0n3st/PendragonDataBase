#pragma once
#include "Joueur.h"
#include "xml.h"
#include "systeme.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Liste
{
public:
	Liste();
	~Liste();
	static Liste* getInstance() {
		
        if (instance == NULL)
			instance = new Liste();
		return instance;

	}
	int getNbJoueurs();
    void ajouterJoueur(Joueur* joueur);
    void retirerJoueur(int position);
    Joueur* getJoueur(int position);
    string getfichier();
    void setInstance(Liste* liste);
	void viderListe();
    static Liste *chargerListe(string fichier);
    void sauvegarderListe(); //appelle sauvegarderListe avec fichier_ en parametre
    void trier();
    string getRecherche();
    void recherche(string prefixe);
    void setFichier(string fichier);
    void setPresenceTous(bool presence);
    void sauvegarderListe(string fichier);
    static int highestId;
    //les fonctions ci-dessous devraient disparaitre dans le futur
    void transfererNotesJoueur(string autreFichier, string nomJoueur);
    string fileName(string fichier, string nomJoueur);





private:
    std::vector<Joueur*> joueurs_, searchJoueurs_;
    string fichier_ = "", vieuFichier_ ="", researchPrefix ="", research;
    int* researchIndex = NULL;

	static Liste* instance;
};

