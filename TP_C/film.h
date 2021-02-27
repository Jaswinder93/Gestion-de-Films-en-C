#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef enum {
	ACTION,
	HORREUR,
	COMEDIE,
	DOCUMENTAIRE,
	POLICIER,
	DRAME,
	ANIMATION,
	SCIENCE_FICTION
}Genre;


typedef struct realisateur_st Realisateur;
typedef struct film_st Film;
typedef struct acteur_st Acteur;
typedef struct date_st Date;
typedef struct artiste_st Artiste;


struct date_st
{
	int jour;
	int mois;
	int annee;

};


struct realisateur_st
{
	char* nom;
	char* prenom;
	Date dateDeNaissance;
	char* nationalite;
};

struct acteur_st
{
	char* nom;
	char* prenom;
	Date dateDeNaissance;
	char* nationalite;
};

struct artiste_st
{
	char* nom;
	char* prenom;
	Date dateDeNaissance;
	char* nationalite;
};

struct film_st
{
	char* titre;
	int annee;
	int duree;
	Genre genre;
	Acteur* acteur;
	int nbActeur;
	Realisateur realisateur;

};


Film* lireFichier(char*, Film*, int*);
Date retourneDate(char*);
char** tableauActeurs(char*, int);
Acteur retourneActeur(char*, Acteur);
void AfficherFilms(Film*, int);
Genre StringToGenre(char*);
char* GenreToString(Genre);
char* ConvertiMinute(int);
Realisateur* remplirRealisateurs(Realisateur*, int*, Film*, int);
void AfficherRealisateurs(Realisateur*, int);
Acteur* remplirActeurs(Acteur*, int*, int, Film*);
void AfficherActeurs(Acteur*, int);
void AfficherUnRealisateur(Realisateur*, int);
void AfficherUnActeur(Acteur*, int);
