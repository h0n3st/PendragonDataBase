#ifndef AJOUTER_H
#define AJOUTER_H
#include "Liste.h"
#include "mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QComboBox>

namespace Ui {
class Ajouter;
}

class Ajouter : public QDialog
{
    Q_OBJECT

public:
    explicit Ajouter(QWidget *parent = 0);
    ~Ajouter();

    void setDates(QComboBox *jour, QComboBox *mois, QComboBox *annee);

public slots:
    void ajouterJoueur();
private:
    Ui::Ajouter *ui;
};

#endif // AJOUTER_H
