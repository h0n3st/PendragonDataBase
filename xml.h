#ifndef XML_H
#define XML_H
#include "Liste.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <QXmlStreamAttributes>
#include <QFile>
#include <QMessageBox>
class Liste;
class xml
{
public:
    xml();
    static void writeList(Liste* liste,string fichier);
    static Liste* readList(string fichier);
    static void readPlayer(QXmlStreamAttributes att, Liste* liste);
};

#endif // XML_H
