/****************************************************************************
* Fichier: Class_OldListe.cpp
* Auteur: Gabriel Cote-Carrier
* Date: juin 2015
* Description: 	Implémentation de la classe OldListe qui sert à contenir
*				un ensemble de OldJoueurs qui pourra être affiché par le
*				dialogue principal
****************************************************************************/

#include <fstream>
#include <string>
#include "Class_Liste.h"

	//Constructeur
	//donne une valeur par defaut a l'attribut fichier_
    OldListe::OldListe()
	{

		fichier_ = "fichier.bin";
	}

	//Destructeur par defaut
    OldListe::~OldListe()
	{

	}

	/*
        OldListe::getNbOldJoueurs
		Parametres : aucun
        Retour : 	int indiquant le nombre d'objets OldJoueurs contenus dans
                    le vecteur de la OldListe
	*/
    int OldListe::getNbOldJoueurs(){

        return OldJoueurs_.size();
	}
	/*
        OldListe::ajouterOldJoueur
        Parametres : OldJoueur l'objet a ajouter
		Retour : 	aucun
        La methode ajoute l'objet OldJoueur au vecteur OldJoueurs_
        puis appelle la methode servant a trier le vecteur OldJoueurs_
	*/
    void OldListe::ajouterOldJoueur(const OldJoueur& oldJoueur){
        OldJoueurs_.push_back(oldJoueur);
		trier();
	}
	/*
        OldListe::retirerOldJoueur
        Parametres : int indiquant la position du OldJoueur a retirer
		Retour : 	aucun
        La methode transfere le dernier OldJoueur du vecteur a la position
        desiree, ce qui efface effectivement le OldJoueur a la position desiree
        Ensuite, la methode retire le dernier OldJoueur du vecteur pour retirer un
        des doubles de ce OldJoueur
        Enfin, la methode trie le vecteur OldJoueurs_
	*/
    void OldListe::retirerOldJoueur(const int& position){

        OldJoueurs_[position] = OldJoueurs_.back();
        OldJoueurs_.pop_back();
		trier();
	}
	/*
        OldListe::getOldJoueur
        Parametres : 	int la position dans le vecteur du OldJoueur auquel
						on desire acceder
        Retour : 	OldJoueur& le OldJoueur desire
	*/
    OldJoueur& OldListe::getOldJoueur(int& position){

        return OldJoueurs_[position];
	}
	/*
        OldListe::getFichier
		Parametres : aucun
		Retour : 	CString le contenu de l'attribut fichier_
	*/
    string OldListe::getfichier(){

		return fichier_;
	}
	/*
        OldListe::setFichier
		Parametres : 	CString le nouveau contenu desire
		Retour : 	aucun
		La methode transfere fichier_ dans vieuFichier_, 
		puis donne le nouveau contenu desire a fichier_
	*/
    void OldListe::setFichier(const string& fichier){

		this->vieuFichier_ = this->fichier_;
		this->fichier_ = fichier;
	}
	/*
        OldListe::viderOldListe
		Parametres : 	aucun
		Retour : 	aucun
        La methode vide le vecteur OldJoueurs_
	*/
    void OldListe::viderOldListe(){

        OldJoueurs_.clear();
	}
	/*
        OldListe::lectureGetNbElements
		Parametres : 	aucun
        Retour : 	int le nombre de OldJoueurs emmagasines dans le
					fichier binaire de nom fichier_
	*/
    int OldListe::lectureGetNbElements(){

        ifstream lecture(fichier_.c_str(), ios::binary);
        lecture.seekg(0, ios::end);			//Determine le nombre de OldJoueurs dans le fichier binaire
        int nElements = int(lecture.tellg() / sizeof (OldJoueur));
		lecture.close();

		return nElements;
	}
	/*
        OldListe::lectureChargerOldListe
		Parametres : 	aucun
		Retour : 	aucun
        La methode vide le vecteur OldJoueurs_,lit les objets OldJoueurs
        contenus dans le fichier binaire et les ajoute au vecteur OldJoueurs_
	*/
    void OldListe::lectureChargerOldListe(){

		int nElements = lectureGetNbElements();
        ifstream lecture(fichier_.c_str(), ios::binary);

		if (lectureFichierExiste()){

            viderOldListe();
			
			for (int i = 0; i < nElements; i++){

                OldJoueur temporaire;
				lecture.read((char*)&temporaire, sizeof(temporaire));
                this->ajouterOldJoueur(temporaire);
			}
			lecture.close();
		}
	}
	/*
        OldListe::lectureFichierExiste
		Parametres : 	aucun
		Retour : 	booleen
		La methode ve000rifie si le fichier binaire existe et l'indique
		en retournant un booleen
	*/
    bool OldListe::lectureFichierExiste(){

        ifstream lecture(fichier_.c_str(), ios::binary);
		bool reussite = !lecture.fail();
		lecture.close();

		return reussite;
	}
	/*
        OldListe::sauvegarderOldListe
		Parametres : 	aucun
		Retour : 	aucun
        La methode sauvegarde l'ensemble des objets OldJoueur dans le
        vecteur OldJoueurs_ dans le fichier binaire et transfere les notes en fichier
        texte de chaque OldJoueur
	*/
    void OldListe::sauvegarderOldListe(){

        ofstream ecriture(fichier_.c_str(), ios::binary);
        for (int i = 0; i < OldJoueurs_.size(); i++)
		{
            ecriture.write((char*)&OldJoueurs_[i], sizeof(OldJoueurs_[i]));
            transfererNotesOldJoueur(vieuFichier_, OldJoueurs_[i].getNom());

		}
		ecriture.close();
	}
	/*
        OldListe::viderOldListe
		Parametres : 	CString le titre du fichier contenant initialement la note
                        char* le nom du OldJoueur dont on veut transferer la note
		Retour : 	aucun
        La methode lit le fichier texte de note associe au OldJoueur, prends son contenu en note
        puis cree un nouveau fichier texte associe au OldJoueur sous le nouveau nom de fichier binaire
        de la OldListe
	*/
    void OldListe::transfererNotesOldJoueur(string autreFichier, char* nomOldJoueur){
		int extensionLength = 4;
		
		//trouve le nom de l'ancien fichier de note selon les conventions
        autreFichier = autreFichier.erase(autreFichier.length() - extensionLength);
        autreFichier += "_notes_" + string(nomOldJoueur) + ".txt";

		string notes, temporaire;

        ifstream lecture(autreFichier.c_str());
		if (!lecture.fail()){
			//lecture du contenu de l'ancien fichier de note
			while (!lecture.eof()){
				getline(lecture, temporaire);
				notes += temporaire;
				notes += "\n";
			}
			lecture.close();

			//trouve le nouveau nom de fichier de note selon les conventions
            string newFile = fichier_;
            newFile = newFile.erase(newFile.length() - extensionLength);
            newFile += "_notes_" + string(nomOldJoueur) + ".txt";

			//transfert du contenu dans un nouveau fichier de note
            ofstream ecrire(newFile.c_str(), ios::trunc);
			ecrire << notes << endl;
			ecrire.close();
		}
		else{
			lecture.close();
		}
	}
	/*
        OldListe::trier
		Parametres : 	aucun
		Retour : 	aucun
        La methode trie tous les objets OldJoueur contenus dans le vecteur
        OldJoueurs_
	*/
    void OldListe::trier(){
        sort(OldJoueurs_.begin(), OldJoueurs_.end());
	}
