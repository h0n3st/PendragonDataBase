#include "xml.h"

xml::xml()
{

}

void xml::writeList(Liste *liste, string fichier)
{
    QFile file(QString::fromStdString(fichier));
    file.open(QIODevice::WriteOnly);
    QXmlStreamWriter write(&file);
    write.setAutoFormatting(true);

    write.writeStartDocument();

    liste->recherche("");
    write.writeStartElement(QString::fromStdString("bd"),QString::fromStdString("Joueurs"));
    for(int i = 0 ; i < liste->getNbJoueurs();i++){
        Joueur* tmp = liste->getJoueur(i);
        write.writeStartElement(QString::fromStdString("bd"),QString::fromStdString("Joueur"));
        write.writeAttribute("Id",QString::number(tmp->getId()).toStdString().c_str());
        write.writeAttribute("Nom", tmp->getNom().c_str());
        write.writeAttribute("DateNaissance",QString::number(tmp->getDateNaissance()).toStdString().c_str());
        write.writeAttribute("Personnage",tmp->getPerso().c_str());
        write.writeAttribute("Classe",QString::number(tmp->getClasse()).toStdString().c_str());
        write.writeAttribute("Race",QString::number(tmp->getRace()).toStdString().c_str());
        write.writeAttribute("Groupe",QString::number(tmp->getGroupe()).toStdString().c_str());
        write.writeAttribute("Experience",QString::number(tmp->getExp()).toStdString().c_str());
        write.writeAttribute("Present",QString::number(tmp->getPresent()).toStdString().c_str());
        write.writeAttribute("LastModified",QString::number(tmp->getLastModified()).toStdString().c_str());
        write.writeAttribute("Notes", tmp->getNotes().c_str());
        write.writeCharacters(QString::fromStdString("tabarnak fourrez"));
        write.writeEndElement();
    }
    write.writeEndElement();
    write.writeEndDocument();
    file.close();

}

Liste *xml::readList(string fichier)
{
    QFile file(QString::fromStdString(fichier));
    file.open(QIODevice::ReadOnly);
    QXmlStreamReader read(&file);

    Liste* liste = new Liste();
    while(!read.atEnd()){
        QXmlStreamReader::TokenType tmp  = read.readNext();
        QMessageBox box;
        if(tmp == QXmlStreamReader::StartDocument)
           continue;
        if (tmp==QXmlStreamReader::StartElement){
            QXmlStreamAttributes att = read.attributes();
            readPlayer(att,liste);
        }


    //SOMEHOW, THIS SUDDENLY WORKS, IF ITS NOT BROKEN DONT FIX IT

    }
    read.clear();
    file.close();
    return liste;
}
void xml::readPlayer(QXmlStreamAttributes att, Liste* liste){
    if(att.size()>0){

        int id = att.value("Id").toString().toInt();

        string nom = att.value("Nom").toString().toStdString();

        int dateNaissance = att.value("DateNaissance").toInt();

        string personnage = att.value("Personnage").toString().toStdString();

        int classe = att.value("Classe").toInt();

        int race = att.value("Race").toInt();

        int groupe = att.value("Groupe").toInt();

        int exp = att.value("Experience").toInt();

        bool present = (bool)att.value("Present").toInt();

        int lastModified = att.value("LastModified").toInt();

        string notes = att.value("Notes").toString().toStdString();


        Joueur* tmp = new Joueur;
        tmp->setId(id);
        tmp->setNom(nom);
        tmp->setDateNaissance(dateNaissance);
        tmp->setPerso(personnage);
        tmp->setClasse(classe);
        tmp->setRace(race);
        tmp->setGroupe(groupe);
        tmp->setExp(exp);
        tmp->setPresent(present);
        tmp->setLastModified(lastModified);
        tmp->setNotes(notes);
        liste->ajouterJoueur(tmp);
        }
}




