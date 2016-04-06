#include "systeme.h"

Systeme::Systeme()
{

}

int Systeme::fromOldClasses(int old)
{
    Classes tmp;
    switch (old){
    case 0: //assassin
        tmp = ASSASSIN;
        break;

    case 1: //bretteur
        tmp = BRETTEUR;
        break;
    case 2: //Éclaireur
        tmp = ECLAIREUR;
        break;
    case 3: //Fantassin
        tmp =FANTASSIN;
        break;

    case 4: //Magicien
        tmp = MAGE;
        break;

     default:
    return 0;
        break;
    }
    return tmp;
}

int Systeme::fromOldRaces(int old)
{
    Races tmp;
    switch (old){
    case 0://drow ?
        tmp = HUMAIN;
        break;

    case 1://Elfe ?
        tmp = ELFE;
        break;

    case 2://Humain ?
        tmp = HUMAIN;
        break;

    case 3: //Nain ?
        tmp = HUMAIN;
        break;

    case 4: //Orc?
        tmp = ORC;
        break;

     default: //humain
        tmp = HUMAIN;
        break;
    }
    return tmp;
}
