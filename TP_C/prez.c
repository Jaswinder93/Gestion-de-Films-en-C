#include "prez.h"


/*
 Affichage dynamique menu
 Affichage menu

*/
const char cine[] =
"   |===========================================================|\n\
   |                                                           |\n\
   |                     _                    ____             |\n\
   |           ______   |_|   ___      _     /___/             |\n\
   |         /  _____|   _   |   \\    | |   ______             |\n\
   |        |  /        | |  | |\\ \\   | |  |  ____|            |\n\
   |        | |         | |  | | \\ \\  | |  | |____             |\n\
   |        | |         | |  | |  \\ \\ | |  |  ____|            |\n\
   |        |  \\_____   | |  | |   \\ \\| |  | |____             |\n\
   |         \\_______|  |_|  |_|    \\___|  |______|            |\n\
   |                                                           |\n\
   |                                                           |\n\
   |           Appuyer sur une touche pour commencer           |\n\
   |                                                           |\n\
   |===========================================================|\n\
";

const char menu[] =
"   |===========================================================|\n\
   |                                                           |\n\
   |                          MENU :                           |\n\
   |                                                           |\n\
   |         1. Afficher tous les films                        |\n\
   |         2. Afficher tous les acteurs                      |\n\
   |         3. Afficher tous les realisateurs                 |\n\
   |         4. Rechercher un film par nom                     |\n\
   |         5. Rechercher un realisateur par nom              |\n\
   |         6. Recherche un acteur par nom                    |\n\
   |         7. Quitter                                        |\n\
   |                                                           |\n\
   |         Appuyez sur le chiffre correspondant a            |\n\
   |         la fonctionnalite souhaitee puis entrez           |\n\
   |                                                           |\n\
   |===========================================================|\n\
";

void afficher_intro() {
    fflush(stdout);
    system("cls");
    system("COLOR 02");
    printf("\n%s", cine);
    int i;
    for (i = 0; i < 14; i++) {
        printf("\n");
    }
}

void afficher_menu() {
    fflush(stdout);
    system("cls");
    system("COLOR 09");
    printf("\n%s", menu);
}

void affichage_dyna_menu() {
    fflush(stdout);
    system("cls");
    system("COLOR 09");
    int i;
    for (i = 0; i < 50; i++) {
        printf("\n");
    }
    printf("\n%s", menu);
    affichage_dynamique(13);
    afficher_menu();
}

void delai(unsigned int value)
{
    unsigned int compt1 = 0;
    unsigned int compt2 = 0;

    for (compt1 = 0; compt1 < value; compt1++)
    {
        for (compt2 = 0; compt2 < compt1; compt2++)
        {
        }
    }
}

void affichage_dynamique(int nbSauts)
{
    const int valDelai = 8000;
    int shifControl = 0;

    for (shifControl = 0; shifControl < nbSauts; ++shifControl)
    {
        delai(valDelai);
        printf("\n");
    }
}
