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
    void chargerListe();    //changer pour XML
    static Liste *chargerListe(string fichier);
    void sauvegarderListe(); //appelle sauvegarderListe avec fichier_ en parametre
    //TODO void sauvegarderListe(string fichier); UTILISE XML
    //TODO mergeWithList(string fichier); MERGE les deux et garde les joueurs modifies le plus recemment en cas de conflit
	void trier();
    string getRecherche();
    void recherche(string prefixe);
    //static void setHighestId(int id) {highestId = id; }
    //static int getHighestId() {return highestId;}
    //les fonctions ci-dessous devraient disparaitre dans le futur
    void transfererNotesJoueur(string autreFichier, string nomJoueur);
    string fileName(string fichier, string nomJoueur);
    void setFichier(string fichier);
    void setPresenceTous(bool presence);
    static int highestId;



    void sauvegarderListe(string fichier);
private:
    std::vector<Joueur*> joueurs_, searchJoueurs_;
    string fichier_ = "", vieuFichier_ ="", researchPrefix ="", research;
    int* researchIndex = NULL;

	static Liste* instance;
};

