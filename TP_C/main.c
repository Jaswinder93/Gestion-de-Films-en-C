#include "film.h"
#include "prez.h"

/*
Exerice : Structure & Tableaux
author : Jaswinder Singh & Antoine Cathaud
Classe : L3 Réseau et sécurité

*/
int main()
{
	Film* films = (Film*)malloc(1 * sizeof(Film));
	int indiceFilm = 0, indiceReal = 0, indiceAct = 0, c;
	Realisateur* realisateurs = (Realisateur*)malloc(1 * sizeof(Realisateur));
	Acteur* acteurs = (Acteur*)malloc(1 * sizeof(Acteur));
	films = lireFichier("fichier.csv", films, &indiceFilm);
	realisateurs = remplirRealisateurs(realisateurs, &indiceReal, films, indiceFilm);
	acteurs = remplirActeurs(acteurs, &indiceAct, indiceFilm, films);

	afficher_intro();
	while (!kbhit()) {}
	affichage_dynamique(20);
	affichage_dyna_menu();

	char choiceRecommence[10]; int choixReco =1;
	char choixM[10]; int choixMenu;
	while ((c = getchar()) != '\n' && c != EOF);
	while (choixReco==1) {
		printf("$choix-menu>");
		fgets(choixM, 10, stdin);
		choixMenu = atoi(choixM);
		switch (choixMenu) {
		case 1:
			system("cls");
			system("COLOR 04");
			printf("\t _______________________________\n");
			printf("\t|   Afficher les films          |\n");
			printf("\t|_______________________________|\n");
			AfficherFilms(films, indiceFilm);
			break;
		case 2:
			system("cls");
			system("COLOR 06");
			printf("\t _______________________________\n");
			printf("\t|   Afficher les acteurs        |\n");
			printf("\t|_______________________________|\n");
			AfficherActeurs(acteurs, indiceAct);
			break;
		case 3:
			system("cls");
			system("COLOR 05");
			printf("\t  _______________________________ \n");
			printf("\t     Afficher les realisateurs  ! \n");
			printf("\t  _______________________________\n");
			AfficherRealisateurs(realisateurs, indiceReal);
			break;
		case 4:
			system("cls");
			system("COLOR 04");
			printf("\t _______________________________\n");
			printf("\t      Chercher un film !|\n");
			printf("\t _______________________________ \n");
			AfficherUnFilm(films, indiceFilm);
			break;
		case 5:
			system("cls");
			system("COLOR 06");
			printf("\t _______________________________\n");
			printf("\t    Chercher un realisateur!	  \n");
			printf("\t _______________________________\n");
			AfficherUnRealisateur(realisateurs, indiceReal);
			break;
		case 6:
			system("cls");
			system("COLOR 06");
			printf("\t _______________________________\n");
			printf("\t   Chercher un acteur		 !    \n");
			printf("\t _______________________________\n");
			AfficherUnActeur(acteurs, indiceAct);
			break;
		case 7:
			printf("\t _______________________________\n");
			printf("\t|            A BIENTOT !        |\n");
			printf("\t|_______________________________|\n");
			exit(0);
			break;
		default:
			printf("\t _______________________________\n");
			printf("\t|Vous avez mal taper la touche !|\n");
			printf("\t|_______________________________|\n");

		}

		printf("\t ________________________________\n");
		printf("\t|1-Continuer   Autres- Arreter !|\n");
		printf("\t|_______________________________|\n\n$choix-continuer>");
		fgets(choiceRecommence, 10, stdin);
		choixReco = atoi(choiceRecommence);
		if (choixReco==1)
			afficher_menu();
	}
	printf("\t _______________________________\n");
	printf("\t|            A BIENTOT !        |\n");
	printf("\t|_______________________________|\n");
	free(acteurs); free(realisateurs); free(films);
	return 0;
}
