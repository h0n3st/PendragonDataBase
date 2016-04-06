#pragma once
#include <string>

using namespace std;
enum LEVELS {
	LEVEL_ONE = 1,
	LEVEL_TWO = 3,
	LEVEL_THREE = 6,
	LEVEL_FOUR = 9,
	LEVEL_FIVE = 13
};

class Personnage
{
public:
	Personnage();
	~Personnage();
    static const int MAX_EXP = 20;
    string getPerso();
    int getGroupe();
    int getClasse();
    int getNiveau();
    int getExp();
    int getRace();


    void setPerso(const string& perso);
    void setClasse(const int& classe);
    void setRace(const int& race);
    void setExp(const int& exp);
    void setGroupe(const int& groupe);
	void rajouterExperience(unsigned int qte);
    int calculerNiveau();

private:
    string personnage_ = "";
    int classe_ = 0, niveau_ = 1 , experience_ = 0, race_ = 0;
    int groupe_ = 0;
	
};

