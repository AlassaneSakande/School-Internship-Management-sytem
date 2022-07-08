## INTERNSHIP MANAGEMENT SYSTEM

<p align="center">
<img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white"/>
<img src="https://img.shields.io/badge/Emacs-%237F5AB6.svg?&style=for-the-badge&logo=gnu-emacs&logoColor=white"/>
</p>

![intern](https://user-images.githubusercontent.com/84173235/177986010-4f08e43d-cafc-4314-b2aa-6e54423a7511.jpeg)


Simple C program to manage interns of a given University


# Note that the comments are in english while we've kept our variables in french

The school professionals can add , delete, modify and view the elements
according to differents needs.

# Functions

choix() : Menu

void Ajout(stagiaires **tmp1_liste, stagiaires *liste) : Add an intern

void Affichage(stagiaires *tmp1_liste) : View recently added infos

void Enregistrer(stagiaires **tmp1_liste): Save recently added

void view(): Print the whole list

void supprimer(): Delete an intern's infos

int find_student(char firstname[TAILLE], char lastname[TAILLE], char company[TAILLE], char teacher[TAILLE]) : Finding a student

void liste_stagiaire_entreprise(): Print company's interns

void modifier(): Modify infos

void liste_stagiaire_professeur() : Print teacher's interns

void date_visite(): Add a date of teacher visiting date

void aff_date_visite(): print the dates

void resultat(): Add presentation's results

void aff_resultat(): Print the presentations' results

# Additional modules

modebuffer.c

	- Void the buffer
	
	- Converting all strings to lowercase
