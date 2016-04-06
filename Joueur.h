#pragma once
#include "Personnage.h"
#include "systeme.h"
#include "Class_Liste.h"
#include "Class_Joueur.h"
#include <ctime>
class Joueur :
	public Personnage
{
public:
	Joueur();
    Joueur(OldJoueur& old, OldListe *liste);
	~Joueur();
    string getTel();
    string getNom();
	bool getPresent();
	int getAge();
    int getDateNaissance();

    void setTelephone(string telephone);
    void setNom(string nom);
	void setPresent(const bool& present);
	void setDateNaissance(int jour, int mois, int annee);
    void setDateNaissance(int date);
    void setLastModified(int timeStamp);
    void setId(int id) {id_  = id;}
    int getId() {return id_;}
    int getLastModified();
    string getNotes();

	bool operator< (Joueur& joueur);



    //TODO fct retournant un string resumant le joueur et ses notes
    string toString();
    void setNotes(string notes);
    void modified();
private:

    //TODO rajouter un ID?????? pour permettre aux joueurs d'entrer le hashcode de leur id dans le site web
    //On pourrait aussi utiliser une combinaison de leur nom et de leur date de naissance (mais alors faudrait empecher que le nom du joueur change...)
    //Faudrait alors faire un hashcode et un de-hash
    int dateNaissance_ = 0, id_ = 0;
    string telephone_ = "";
    string nom_ = "";
    string notes_ = "";
	int lastModified_ = 0;
	bool present_ = false;

};

