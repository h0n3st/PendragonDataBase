
#include "Joueur.h"


Joueur::Joueur()
{
    lastModified_ = time(NULL);
}

Joueur::Joueur(OldJoueur &old, OldListe* liste)
{
    lastModified_ = 0;
    nom_ = string(old.getNom());
    dateNaissance_ = old.getDateNaissance();
    id_ = 0;
    this->setPerso((string)old.getPerso());
    this->setClasse(Systeme::fromOldClasses(old.getClasse()));
    this->setRace(Systeme::fromOldRaces(old.getRace()));
    this->setExp(old.getExp());
    this->setGroupe(-1);
    int extensionLength = 4;
    string fichier = liste->getfichier();
    fichier = fichier.erase(fichier.length() - extensionLength);
    fichier += "_notes_"+string(old.getNom()) + ".txt";
    ifstream lecture(fichier.c_str());

        if (!lecture.fail())
        {

            std::string temporaire, complet;

            while (!lecture.eof())
            {

                string enter = "\n";
                getline(lecture, temporaire);
                complet += temporaire;
                complet += enter;


            }
            this->notes_ = complet;
        }
}


Joueur::~Joueur()
{
}
string Joueur::getTel() { return telephone_; }
string Joueur::getNom() { return nom_; }
bool Joueur::getPresent() { return present_; }
int Joueur::getAge() {
	const double SECONDES_PAR_JOUR = 86400;
	const double JOUR_PAR_AN = 365.25;
	int secondesParAn = SECONDES_PAR_JOUR*JOUR_PAR_AN;

    time_t temps = time(NULL);

	//Le calcul est imprecis de quelques jours
	int ageEnSecondes = temps - dateNaissance_;
	int ageEnAn = ageEnSecondes / secondesParAn;

    return ageEnAn;
}

int Joueur::getDateNaissance()
{
 return dateNaissance_;
}

void Joueur::setTelephone(string telephone) { telephone_ = telephone; }
void Joueur::setNom(string nom) { this->nom_ = nom; }
void Joueur::setPresent(const bool& present) { present_ = present; }
void Joueur::setDateNaissance(int jour, int mois, int annee) {
	const double SECONDES_PAR_JOUR = 86400;
	const double JOUR_PAR_AN = 365.25;
	const double JOUR_PAR_MOIS[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

	//calcul imprecis a quelques jours
    dateNaissance_ = int(((double(annee - 1970))*JOUR_PAR_AN + JOUR_PAR_MOIS[mois] + double(jour))*SECONDES_PAR_JOUR);
}

void Joueur::setDateNaissance(int date)
{
    dateNaissance_ = date;
}

void Joueur::setLastModified(int timeStamp)
{
    lastModified_ = timeStamp;
}
void Joueur::modified(){
    lastModified_ = time(NULL);
}

int Joueur::getLastModified()
{
    return lastModified_;
}

string Joueur::getNotes()
{
    return notes_;
}

void Joueur::setNotes(string notes)
{
    notes_ = notes;
}

bool Joueur::operator< (Joueur& joueur) {
	return nom_ < joueur.nom_;
}

string Joueur::toString()
{
    return (nom_ + " | " + getPerso());
}
