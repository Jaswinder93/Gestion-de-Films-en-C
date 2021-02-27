#pragma warning(disable : 4996)
#pragma warning(disable : 6308)
#include "film.h"
#define TAILLE_BUFF 1024

/*
Tache : lire le fichier CSV et renvoyer un tableau de film
@param-in : nom du fichier, tableau de film, l'indice en pointeur du film
@param-out : tout les films contenu dans le fichier CSV

*/
Film* lireFichier(char* nomFichier, Film* film, int* indiceFilm) {
	*indiceFilm += 1;

	char line[TAILLE_BUFF];

	FILE* file = fopen(nomFichier, "r");

	if (file == NULL) {
		perror("Erreur de fichier\n");
		exit(0);
	}
	int indiceLine, i;
	char* temp;
	while (fgets(line, sizeof(line), file) != NULL) {

		char* token = strtok(line, ";");
		indiceLine = 0;
		while (token != NULL) {
			switch (indiceLine) {
			case 0:
				film[*indiceFilm - 1].titre = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(film[*indiceFilm - 1].titre, token);
				break;
			case 1:
				film[*indiceFilm - 1].annee = strtol(token, NULL, 10);
				break;
			case 2:
				film[*indiceFilm - 1].duree = strtol(token, NULL, 10);
				break;
			case 3:
				film[*indiceFilm - 1].genre = StringToGenre(token);
				break;
			case 4:
				film[*indiceFilm - 1].realisateur.nom = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(film[*indiceFilm - 1].realisateur.nom, token);
				break;
			case 5:
				film[*indiceFilm - 1].realisateur.prenom = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(film[*indiceFilm - 1].realisateur.prenom, token);
				break;
			case 6:
				film[*indiceFilm - 1].realisateur.dateDeNaissance = retourneDate(token);
				break;
			case 7:
				film[*indiceFilm - 1].realisateur.nationalite = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(film[*indiceFilm - 1].realisateur.nationalite, token);
				break;
			case 8:
				film[*indiceFilm - 1].nbActeur = strtol(token, NULL, 10); film[*indiceFilm - 1].acteur = (Acteur*)malloc(film[*indiceFilm - 1].nbActeur * sizeof(Acteur));
				break;
			case 9:
				temp = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(temp, token);
				char** tableauAct = tableauActeurs(temp, film[*indiceFilm - 1].nbActeur);
				for (i = 0; i < film[*indiceFilm - 1].nbActeur; i++) {
					film[*indiceFilm - 1].acteur[i] = retourneActeur(tableauAct[i], film[*indiceFilm - 1].acteur[i]);
				}
				free(temp);
				break;
			default:
				break;
			}
			indiceLine++;
			token = strtok(NULL, ";");


		}
		*indiceFilm += 1;
		if (film != 0)
			film = (Film*)realloc(film, (*indiceFilm) * sizeof(Film));
	}
	return film;
}

/*
Tache : retourner un text en format Date
@param-in : Char* du texte contenant la date dans le CSV
@param-out : retourne une Date

*/
Date retourneDate(char* tokenFichier) {
	char jour[3] = { 0 }, mois[3] = { 0 }, annee[5] = { 0 };
	Date d;
	d.jour = 0, d.mois = 0, d.annee = 0;
	int indiceJ = 0, indiceM = 0, indiceA = 0, taille = strlen(tokenFichier), i;
	for (i = 0; i < taille; i++) {
		if (i < 2) { jour[indiceJ++] = tokenFichier[i]; }
		if (i > 2 && i < 5) { mois[indiceM++] = tokenFichier[i]; }
		if (i > 5) { annee[indiceA++] = tokenFichier[i]; }
	}
	jour[indiceJ] = mois[indiceM] = annee[indiceA] = '\0';
	d.jour = atoi(jour), d.mois = atoi(mois), d.annee = atoi(annee);
	return d;
}

/*
Tache : retourner un tableau d'acteur d'un film à partir de ses informations
@param-in : char* des informations d'un acteur, l'acteur concerné
@param-out : l'acteur avec ses informations renseigné grâce au char*

*/
Acteur retourneActeur(char* token, Acteur act) {
	char nom[30] = { 0 }, prenom[50] = { 0 }, date[11] = { 0 }, nationalite[30] = { 0 };
	int taille = strlen(token), i, indiceA = 0, j = 0;
	for (i = 0; i < taille; i++) {
		if (token[i] != '-') {
			if (indiceA == 0) { nom[j++] = token[i]; }
			if (indiceA == 1) { prenom[j++] = token[i]; }
			if (indiceA == 2) { date[j++] = token[i]; }
			if (indiceA == 3) { nationalite[j++] = token[i]; }
		}
		if (token[i] == '-') {
			if (indiceA == 0) { nom[j] = '\0'; }
			if (indiceA == 1) { prenom[j] = '\0'; }
			if (indiceA == 2) { date[j] = '\0'; }
			if (indiceA == 3) { nationalite[j] = '\0'; }
			indiceA++; j = 0;
		}
	}
	act.nom = (char*)malloc((strlen(nom) + 1) * sizeof(char)), act.prenom = (char*)malloc((strlen(prenom) + 1) * sizeof(char)), act.nationalite = (char*)malloc((strlen(nationalite) + 1) * sizeof(char));
	if (act.nom != 0)
		strcpy(act.nom, nom);
	if (act.prenom != 0)
		strcpy(act.prenom, prenom);
	if (act.nationalite != 0)
		strcpy(act.nationalite, nationalite);
	act.dateDeNaissance = retourneDate(date);
	return act;
}

/*
Tache : renvoyer un tableau de char contenant les infos de chaque acteurs
@param-in : char* de tout les acteurs d'un film, et le nombre d'acteurs
@param-out : tableau de char des infos des acteurs d'un film

*/
char** tableauActeurs(char* token, int nbActeur) {
	char** tempActeurs = (char**)malloc(nbActeur * sizeof(char*));
	int i, indiceA = 0, j = 0;
	for (i = 0; i < nbActeur; i++) { tempActeurs[i] = (char*)malloc(sizeof(char)); }
	int taille = strlen(token);
	for (i = 0; i < taille; i++) {
		if (token[i] != ',') {
			tempActeurs[indiceA][j++] = token[i];
			tempActeurs[indiceA] = (char*)realloc(tempActeurs[indiceA], (j + 1) * sizeof(char));

		}
		if (token[i] == ',') {
			tempActeurs[indiceA] = (char*)realloc(tempActeurs[indiceA], (strlen(tempActeurs[indiceA]) + 1) * sizeof(char));
			tempActeurs[indiceA][j] = '\0';
			indiceA++;
			j = 0;
		}
	}
	return tempActeurs;
}

/*
Tache : afficher tout les films du tableau
@param-in : tableau de film, et le nombre de films

*/
void AfficherFilms(Film* f, int indice) {
	int i, j;
	for (i = 0; i < indice - 1; i++) {
		printf("\t__________________________");
		printf("\n\t|Fiche film %d\n", i + 1);
		printf("\t|%s (%d)\n", f[i].titre, f[i].annee);
		printf("\t|Realisateur : %s %s\n", f[i].realisateur.nom, f[i].realisateur.prenom);
		printf("\t|Acteurs : ");
		for (j = 0; j < f[i].nbActeur; j++) {
			printf(" %s %s", f[i].acteur[j].nom, f[i].acteur[j].prenom);
			(j < f[i].nbActeur - 1) ? printf(",") : printf("\n");
		}
		char* genre = GenreToString(f[i].genre), * duree = ConvertiMinute(f[i].duree);
		printf("\t|duree : %s\n", duree);
		printf("\t|genre : %s\n", genre);
		printf("\t|__________________________\n\n");
	}
}


/*
Tache : convertir string en genre
@param-in : char* du genre

*/
Genre StringToGenre(char* string) {
	Genre g = 0;
	if (strcmp(string, "Action") == 0) { g = ACTION; }
	if (strcmp(string, "Horreur") == 0) { g = HORREUR; }
	if (strcmp(string, "Comedie") == 0) { g = COMEDIE; }
	if (strcmp(string, "Documentaire") == 0) { g = DOCUMENTAIRE; }
	if (strcmp(string, "Policier") == 0) { g = POLICIER; }
	if (strcmp(string, "Drame") == 0) { g = DRAME; }
	if (strcmp(string, "Animation") == 0) { g = ANIMATION; }
	if (strcmp(string, "Science-Fiction") == 0) { g = SCIENCE_FICTION; }
	return g;
}
/*
Tache : convertir genre en string
@param-in :le Genre

*/
char* GenreToString(Genre g) {
	char* nomGenre = NULL;
	if (g == ACTION) { nomGenre = (char*)malloc(6 * sizeof(char)); nomGenre = "Action"; }
	if (g == HORREUR) { nomGenre = (char*)malloc(7 * sizeof(char)); nomGenre = "Horreur"; }
	if (g == COMEDIE) { nomGenre = (char*)malloc(7 * sizeof(char)); nomGenre = "Comedie"; }
	if (g == DOCUMENTAIRE) { nomGenre = (char*)malloc(12 * sizeof(char)); nomGenre = "Documentaire"; }
	if (g == POLICIER) { nomGenre = (char*)malloc(8 * sizeof(char)); nomGenre = "Policier"; }
	if (g == DRAME) { nomGenre = (char*)malloc(5 * sizeof(char)); nomGenre = "Drame"; }
	if (g == ANIMATION) { nomGenre = (char*)malloc(9 * sizeof(char)); nomGenre = "Animation"; }
	if (g == SCIENCE_FICTION) { nomGenre = (char*)malloc(15 * sizeof(char)); nomGenre = "Science-Fiction"; }
	return nomGenre;
}
/*
Tache : convertir minutes en heures
@param-in: minutes en int
*/
char* ConvertiMinute(int minutes) {
	char* heure = (char*)malloc(5 * sizeof(char));
	int h = (int)minutes / 60, min = minutes - h * 60;
	sprintf(heure, "%dh%d", h, min);
	return heure;
}
/*
Tache : remplissage du tableau de realisateur
@param-in: tableau de realisateur, indice realisateur au debut, tableau de film, le nombre de film
@param-out : L'ensemble des réalisateurs
*/

Realisateur* remplirRealisateurs(Realisateur* r, int* indiceReal, Film* f, int indiceFilm) {
	*indiceReal += 1;
	int isIn = 0, i, k;
	for (i = 0; i < indiceFilm - 1; i++) {
		for (int k = 0; k < *indiceReal - 1; k++) {
			if (strcmp(r[k].nom, f[i].realisateur.nom) == 0 && strcmp(r[k].prenom, f[i].realisateur.prenom) == 0) {
				isIn = 1;
			}
		}
		if (isIn == 0) {
			r[*indiceReal - 1] = f[i].realisateur;
			*indiceReal += 1;
			r = (Realisateur*)realloc(r, (*indiceReal) * sizeof(Realisateur));
		}
		isIn = 0;
	}
	return r;
}
/*
Tache : remplissage du tableau d'acteurs
@param-in: tableau de acteurs, indice acteurs au debut, le nombre de film, le tableau de films
@param-out : L'ensemble des acteurs
*/
Acteur* remplirActeurs(Acteur* a, int* indiceAct, int indexFilms, Film* f) {
	*indiceAct += 1;
	int isIn = 0,i,j,k;
	for (i = 0; i < indexFilms - 1; i++) {
		for ( j = 0; j < f[i].nbActeur; j++) {
			for ( k = 0; k < *indiceAct - 1; k++) {
				if (strcmp(a[k].nom, f[i].acteur[j].nom) == 0 && strcmp(a[k].prenom, f[i].acteur[j].prenom) == 0) {
					isIn = 1;
				}
			}
			if (isIn == 0) {
				a[*indiceAct - 1] = f[i].acteur[j];
				*indiceAct += 1;
				a = (Acteur*)realloc(a, (*indiceAct) * sizeof(Acteur));
			}
			isIn = 0;
		}
	}
	return a;
}

/*
Tache : Affichage des realisateur
@param-in: tableau realisateur, le nombre de realisateur
*/
void AfficherRealisateurs(Realisateur* r, int indiceReal) {
	int i;
	for (i = 0; i < indiceReal - 1; i++) {

		printf("\t__________________________");
		printf("\n\t|Fiche Realisateur %d :\n", i + 1);
		printf("\t|Nom : %s %s \n", r[i].nom, r[i].prenom);
		printf("\t|Date de naissance : %d/%d/%d\n", r[i].dateDeNaissance.jour, r[i].dateDeNaissance.mois, r[i].dateDeNaissance.annee);
		printf("\t|Nationalite : %s \n", r[i].nationalite);
		printf("\t|__________________________\n\n");
	}
}
/*
Tache : Affichage des acteurs
@param-in: tableau acteurs, le nombre de acteurs
*/
void AfficherActeurs(Acteur* a, int indiceAct) {
	int i;
	for (i = 0; i < indiceAct - 1; i++) {

		printf("\t_________________________");
		printf("\n\t|Fiche Acteur %d :\n", i + 1);
		printf("\t|Nom : %s %s \n", a[i].nom, a[i].prenom);
		printf("\t|Date de naissance : %d/%d/%d\n", a[i].dateDeNaissance.jour, a[i].dateDeNaissance.mois, a[i].dateDeNaissance.annee);
		printf("\t|Nationalite : %s \n", a[i].nationalite);
		printf("\t|__________________________\n\n");
	}
}
/*
Tache : Affichage d'un film recherche par titre
@param-in: tableau films, le nombre de films
*/
void AfficherUnFilm(Film* f, int indice) {
	int c = 0;
	printf("\nQuel film recherchez vous ?\n");
	char nomFilm[100];
	fgets(nomFilm, 100, stdin);
	if (nomFilm[(strlen(nomFilm)) - 1] == '\n') nomFilm[(strlen(nomFilm)) - 1] = '\0';
	char* nomF = (char*)malloc((strlen(nomFilm)) * sizeof(char));
	strcpy(nomF, nomFilm);
	int i, j, bool = 0;
	for (i = 0; i < indice - 1; i++) {
		if (strcmp(nomF, f[i].titre) == 0){
			printf("\t_________________________");
			printf("\n\t|Fiche film %d\n", i + 1);
				printf("\t|%s (%d)\n", f[i].titre, f[i].annee);
				printf("\t|Realisateur : %s %s\n", f[i].realisateur.nom, f[i].realisateur.prenom);
				printf("\t|Acteurs : ");
				for (j = 0; j < f[i].nbActeur; j++) {
					printf(" %s %s", f[i].acteur[j].nom, f[i].acteur[j].prenom);
						(j < f[i].nbActeur - 1) ? printf(",") : printf("\n");
				}
			char* genre = GenreToString(f[i].genre), * duree = ConvertiMinute(f[i].duree);
				printf("\t|duree : %s\n", duree);
				printf("\t|genre : %s\n", genre);
				printf("\t|__________________________\n");
				bool = 1;
		}
	}
	if (bool == 0) printf("Le film n'existe pas, ou son nom est mal renseigne\n");
}
/*
Tache : Affichage d'un realisateur recherche par nom
@param-in: tableau realisateur, le nombre de realisateur
*/
void AfficherUnRealisateur(Realisateur* r, int indice) {
	int c = 0;
	printf("\nQuel Realisateur recherchez vous (Nom Prenom ex : Stanley Kubrick)?\n");
	char nomRea[100];
	fgets(nomRea, 100, stdin);
	if (nomRea[(strlen(nomRea)) - 1] == '\n') nomRea[(strlen(nomRea)) - 1] = '\0';
	char* nomR = (char*)malloc((strlen(nomRea)) * sizeof(char));
	char *nomtabR= (char*)malloc((strlen(nomR)) * sizeof(char));
	strcpy(nomR, nomRea);
	int i, j, bool = 0;
	for (i = 0; i < indice - 1; i++) {
		strcat(strcat(strcpy(nomtabR, r[i].nom), " "), r[i].prenom);
		if (strcmp(nomR, nomtabR) == 0) {
			printf("\t____________________________");
			printf("\n\t|Fiche Realisateur %d \n", i + 1);
			printf("\t|Nom : %s %s \n", r[i].nom, r[i].prenom);
			printf("\t|Date de naissance : %d/%d/%d \n", r[i].dateDeNaissance.jour, r[i].dateDeNaissance.mois, r[i].dateDeNaissance.annee);
			printf("\t|Nationalite : %s \n", r[i].nationalite);
			printf("\t|___________________________\n");
			bool = 1;
		}
	}
	if (bool == 0) printf("Le realisateur n'existe pas, ou son nom est mal renseigne\n");

}

/*
Tache : Affichage d'un Acteur recherche par nom
@param-in: tableau Acteur, le nombre de Acteur
*/
void AfficherUnActeur(Acteur* a, int indice) {
	int c = 0;
	printf("\nQuel Acteur recherchez vous (Nom Prenom ex : Leonardo DiCaprio)?\n");
	char nomAct[100];
	fgets(nomAct, 100, stdin);
	if (nomAct[(strlen(nomAct)) - 1] == '\n') nomAct[(strlen(nomAct)) - 1] = '\0';
	char* nomA = (char*)malloc((strlen(nomAct)) * sizeof(char));
	char* nomtabA = (char*)malloc((strlen(nomA)) * sizeof(char));
	strcpy(nomA, nomAct);
	int i, j, bool = 0;
	for (i = 0; i < indice - 1; i++) {
		strcat(strcat(strcpy(nomtabA, a[i].nom), " "), a[i].prenom);
		if (strcmp(nomA, nomtabA) == 0) {
			printf("\t_________________________________");
			printf("\n\t|Fiche Acteur %d \n", i + 1);
			printf("\t|Nom : %s %s \n", a[i].nom, a[i].prenom);
			printf("\t|Date de naissance : %d/%d/%d \n", a[i].dateDeNaissance.jour, a[i].dateDeNaissance.mois, a[i].dateDeNaissance.annee);
			printf("\t|Nationalite : %s \n", a[i].nationalite);
			printf("\t|_______________________________\n");
			bool = 1;
		}
	}
	if (bool == 0) printf("l'acteur n'existe pas, ou son nom est mal renseigne\n");
}
