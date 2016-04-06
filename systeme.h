#ifndef SYSTEME_H
#define SYSTEME_H


class Systeme
{
public:
    Systeme();
    static const int NOMBRE_GROUPES = 5;
    static int fromOldClasses(int old);
    static int fromOldRaces(int old);
    enum Classes : int {FANTASSIN = 1, BRETTEUR = 0, ASSASSIN = 4, ECLAIREUR = 5, PALADIN = 3, DEVOT = 2, MAGE = 6 };
    enum Races : int{HUMAIN = 0,ELFE = 1,ORC = 2};
    enum Groupes : int {ARMADA, FANATIQUES, EREBE,REGIMENT, DRACOSIRE};

};

#endif // SYSTEME_H
