
#include "Personnage.h"


Personnage::Personnage()
{
}


Personnage::~Personnage()
{
}

string Personnage::getPerso() {return personnage_;}
int Personnage::getGroupe() { return groupe_; }
int Personnage::getClasse() { return classe_; }
int Personnage::getNiveau() { return niveau_; }
int Personnage::getExp() { return experience_; }
int Personnage::getRace() { return race_; }


void Personnage::setPerso(const string& perso) { personnage_ = perso; }
void Personnage::setClasse(const int& classe) { classe_ = classe; }
void Personnage::setRace(const int& race) { race_ = race; }
void Personnage::setExp(const int& exp) { experience_ = exp; calculerNiveau(); }
void Personnage::setGroupe(const int &groupe) { groupe_ = groupe; }
void Personnage::rajouterExperience(unsigned int qte) { 
	experience_ += qte; 
    if (experience_ > MAX_EXP)
		experience_ = MAX_EXP;
    calculerNiveau();
}
int Personnage::calculerNiveau(){
	if (experience_ >= LEVEL_FIVE) {
		niveau_ = 5;
	}
	else if (experience_ >= LEVEL_FOUR) {
		niveau_ = 4;
	}
	else if (experience_ >= LEVEL_THREE) {
		niveau_ = 3;
	}
	else if (experience_ >= LEVEL_TWO) {
		niveau_ = 2;
	}
	else {
		niveau_ = 1;
	}
	return niveau_;
}
