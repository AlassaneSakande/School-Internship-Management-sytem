// Libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modebuffer.c"                 // Library to void the buffer and evoid additional press while using scanf
#include <ctype.h>
#define TAILLE 30                       // Length of all the strings

/* 
Declare and init structs
professeurs, entreprises et stagiaires
*/
struct professeurs
{
    char nom_prof[TAILLE];
    char prenom_prof[TAILLE];
    char date_prof[TAILLE];
    char titre_prof[TAILLE];
};
typedef struct professeurs professeurs;

struct entreprises
{
    char nom_en[TAILLE];
    char adresse_en[TAILLE];
    char specialite_en[TAILLE];
};
typedef struct entreprises entreprises;

//struct stagiaires containing all the infos related to the internship
struct stagiaires
{
    char nom_stag[TAILLE];
    char prenom_stag[TAILLE];
    char classe_stag[TAILLE];
    float salaire_stag;
    int annee_stag;
    char mention[TAILLE];
    float moy_soutenance;

    professeurs professeur;
    entreprises entreprise;

    // Next and last element of the list
    struct stagiaires *suivant;
    struct stagiaires *precedent;

};
typedef struct stagiaires stagiaires;

//***************************************************************
// Fonctions prototypes
void choix();
void Ajout(stagiaires **tmp1_liste, stagiaires *liste);
void Affichage(stagiaires *tmp1_liste);
void Enregistrer(stagiaires **tmp1_liste);
void view();
void supprimer();
int find_student(char firstname[TAILLE], char lastname[TAILLE], char company[TAILLE], char teacher[TAILLE]);
void liste_stagiaire_entreprise();
void modifier();
void liste_stagiaire_professeur();
void date_visite();
void aff_date_visite();
void resultat();
void aff_resultat();
//***************************************************************

// Main program
int main()
{
    printf("\n ********************************************************************************************************************\n");
    printf("\n ********************************************************************************************************************\n");
    printf("\n**                                                                                                                   **");
    printf("\n**     ***       ***        ***  **********  ***        *********   ************    ****   ****     **********       **\n");
    printf("\n**      ***     *****      ***   ***         ***        **          **        **    ***** *****     ***              **\n");
    printf("\n**       ***   ***  ***   ***    **********  ***        **          **        **    *** *** ***     **********       **\n");
    printf("\n**        *** ***    *** ***     ***         ***        **          **        **    ***  *  ***     ***              **\n");
    printf("\n**         *****      *****      *********** ********** *********   ************    ***     ***     **********       **\n");
    printf("\n**                                                                                                                   **");
    printf("\n *********************************************************************************************************************\n");
    printf("\n *********************************************************************************************************************\n");

    printf("\n\n");

    choix();
    return 0;
}

// The menu
void choix() {

// declre and init the list and the last element of the list
  static stagiaires *liste =NULL;
  static stagiaires *tmp1_liste=NULL;
    int choice,
    n;

// Verify the presence of elements in the list, if empty allocate some spaces
    if(liste==NULL)
      liste=calloc(1,sizeof(stagiaires));
    
    printf("\n");
    printf("------------------------\n");
    printf("Choissisez une option \n");
    printf("------------------------\n");
    printf("1. Add\n");
    printf("\t2. View\n");
    printf("\t\t3. Save\n");
    printf("\t\t\t4. View the list\n");
    printf("5. Company's students\n");
    printf("\t6. Teacher's students\n");
    printf("\t\t7. Delete an intern\n");
    printf("\t\t\t8. Modify an intern\n");
    printf("9. Add visiting date\n");
    printf("\t10. Add results of final presentation\n");
    printf("\t\t11. View visiting dates\n");
    printf("\t\t\t12. View presentation results\n");
    printf("\n");
    printf("0. Quit\n");
    printf("\n");
    printf("---------> ");
    scanf("%d", &choice);
    buffer();
    printf("\n");

    switch(choice) {
        case 1:
        Ajout(&tmp1_liste, liste);
        choix();
        break;

        case 2:
        Affichage(tmp1_liste);
        choix();
        break;

        case 3:
        Enregistrer(&tmp1_liste);
        choix();
        break;

        case 4:
        view();
        choix();
        break;

        case 5:
        liste_stagiaire_entreprise();
        choix();
        break;

        case 6:
        liste_stagiaire_professeur();
        choix();
        break;

        case 7:
        supprimer();
        choix();
        break;

        case 8:
        modifier();
        choix();
        break;

        case 9:
        date_visite();
        choix();
        break;

        case 10:
        resultat();
        choix();
        break;

        case 11:
        aff_date_visite();
        choix();
        break;

        case 12:
        aff_resultat();
        choix();
        break;

        case 0:
        printf("Quit ?\n");
        printf("1. yes\n");
        printf("2. no\n");
        printf("--------> ");
        scanf("%d", &n);
        printf("\n");
        
        if(n == 2) {
            choix();
            break;
        }
        // Liberer la liste avant de quitter le programme
        else if(n == 1) {
            printf("\n Goodbye \n");
            while(liste != NULL) {
                free(liste);
                liste = liste->suivant;
            }
            exit(EXIT_FAILURE);
        }
        default:
        printf("*********** Please choose between 0-10 ************\n");
        choix();
    }
}


// Add an intern infos taking as params
// the last element of the list (tmp1_liste) the list (liste)
void Ajout(stagiaires **tmp1_liste, stagiaires *liste) {
    
// declare and init the element which next element looking towards to the last element
    static stagiaires *tmp0_liste = NULL;
    int nbr = 0,
    i,
    bool = 1;
start:
    printf("\nCombien de stagiaire(s) voulez-vous ajouter ? : ");
    scanf("%d", &nbr);
    buffer();

    if(nbr <= 0) {
        printf("\nEntrer un nombre > 0");
        goto start;
    }

    for(i = 1; i <= nbr; i++) {
      if(bool == 1) {
// First element of the list
	printf("\n\n");
    printf("\n -----------------\n");
    printf("\n|  LE STAGIAIRE   |\n");
    printf("\n -----------------\n");

	printf("Nom : ");
	modebuffer(liste->nom_stag, TAILLE);
	strcpy(liste->nom_stag, miniscule(liste->nom_stag));

	printf("Prenom : ");
	modebuffer(liste->prenom_stag, TAILLE);
	strcpy(liste->prenom_stag, miniscule(liste->prenom_stag));

	printf("Classe: ");
	modebuffer(liste->classe_stag, TAILLE);
	strcpy(liste->classe_stag, miniscule(liste->classe_stag));

	printf("Salaire: ");
	scanf("%f", &liste->salaire_stag);
	buffer();

	printf("Annee: ");
	scanf("%d", &liste->annee_stag);
	buffer();

    printf("\n  ------------------\n");
	printf("\n |   ENTREPRISE :   |\n");
    printf("\n  ------------------\n");

	printf("Nom : ");
	modebuffer(liste->entreprise.nom_en, TAILLE);
	strcpy(liste->entreprise.nom_en, miniscule(liste->entreprise.nom_en));

	printf("Adresse ");
	modebuffer(liste->entreprise.adresse_en, TAILLE);
	strcpy(liste->entreprise.adresse_en, miniscule(liste->entreprise.adresse_en));

	printf("Specialite : ");
	modebuffer(liste->entreprise.specialite_en, TAILLE);
	strcpy(liste->entreprise.specialite_en, miniscule(liste->entreprise.specialite_en));

    printf("\n  ----------------------\n");
	printf("\n| LE PROFESSEUR DE SUIVI |\n");
    printf("\n  ----------------------\n");

	printf("Nom : ");
	modebuffer(liste->professeur.nom_prof, TAILLE);
	strcpy(liste->professeur.nom_prof, miniscule(liste->professeur.nom_prof));

	printf("Prenom : ");
	modebuffer(liste->professeur.prenom_prof, TAILLE);
	strcpy(liste->professeur.prenom_prof, miniscule(liste->professeur.prenom_prof));

	printf("Titre: ");
	modebuffer(liste->professeur.titre_prof, TAILLE);
	strcpy(liste->professeur.titre_prof, miniscule(liste->professeur.titre_prof));

	if(liste==NULL)
	  printf("Erreur 1...\n");
	
    // The last one is the first if we only have one element
	*tmp1_liste = liste;

	if(*tmp1_liste==NULL)
	  printf("Erreur 2...\n");
	
    // Init the last element of the first element as NULL 'cause it doesn't exist
	liste->precedent = NULL;
	bool = 0;
      }

      else
        {
	  // Allocate space for the next element
      (*tmp1_liste)->suivant = calloc(1,sizeof(stagiaires));
	  // Save the adress of the last element before moving to the next one
      tmp0_liste = *tmp1_liste;
      // The last element goes to the next one
	  *tmp1_liste = (*tmp1_liste)->suivant;

// Add infos for all the remaining interns
	 printf("\n -----------------\n");
     printf("\n|  LE STAGIAIRE   |\n");
     printf("\n -----------------\n");
	  printf("Nom : ");
	  modebuffer((*tmp1_liste)->nom_stag, TAILLE);
	  strcpy((*tmp1_liste)->nom_stag, miniscule((*tmp1_liste)->nom_stag));

	  printf("Prenom : ");
	  modebuffer((*tmp1_liste)->prenom_stag, TAILLE);
	  strcpy((*tmp1_liste)->prenom_stag, miniscule((*tmp1_liste)->prenom_stag));

	  printf("Classe: ");
	  modebuffer((*tmp1_liste)->classe_stag, TAILLE);
	  strcpy((*tmp1_liste)->classe_stag, miniscule((*tmp1_liste)->classe_stag));

	  printf("Salaire: ");
	  scanf("%f", &(*tmp1_liste)->salaire_stag);
	  buffer();

	  printf("Annee: ");
	  scanf("%d", &(*tmp1_liste)->annee_stag);
	  buffer();

	   printf("\n  ------------------\n");
       printf("\n |   ENTREPRISE :   |\n");
       printf("\n  ------------------\n");
	  printf("Nom : ");
	  modebuffer((*tmp1_liste)->entreprise.nom_en, TAILLE);
	  strcpy((*tmp1_liste)->entreprise.nom_en, miniscule((*tmp1_liste)->entreprise.nom_en));

	  printf("Adresse ");
	  modebuffer((*tmp1_liste)->entreprise.adresse_en, TAILLE);
	  strcpy((*tmp1_liste)->entreprise.adresse_en, miniscule((*tmp1_liste)->entreprise.adresse_en));

	  printf("Specialite : ");
	  modebuffer((*tmp1_liste)->entreprise.specialite_en, TAILLE);
	  strcpy((*tmp1_liste)->entreprise.specialite_en, miniscule((*tmp1_liste)->entreprise.specialite_en));

	  printf("\n  ----------------------\n");
      printf("\n| LE PROFESSEUR DE SUIVI |\n");
      printf("\n  ----------------------\n");
	  printf("Nom : ");
	  modebuffer((*tmp1_liste)->professeur.nom_prof, TAILLE);
	  strcpy((*tmp1_liste)->professeur.nom_prof, miniscule((*tmp1_liste)->professeur.nom_prof));

	  printf("Prenom : ");
	  modebuffer((*tmp1_liste)->professeur.prenom_prof, TAILLE);
	  strcpy((*tmp1_liste)->professeur.prenom_prof, miniscule((*tmp1_liste)->professeur.prenom_prof));

	  printf("Titre: ");
	  modebuffer((*tmp1_liste)->professeur.titre_prof, TAILLE);
	  strcpy((*tmp1_liste)->professeur.titre_prof, miniscule((*tmp1_liste)->professeur.titre_prof));

// Save last address of the last element
	  (*tmp1_liste)->precedent=tmp0_liste;
        }
    }
    // element following the last one is NULL
    (*tmp1_liste)->suivant = NULL;
}


// View recently added infos by LIFO
void Affichage(stagiaires *tmp1_liste) {
    int i = 1;
    // Proceed to the saving while we are not at the end of the list
    while(tmp1_liste != NULL) {
        printf("stagiaire %d: %s\t%s\n\tclasse: %s\n\tsalaire: %f\n\tannee: %d\n\tNom de l'entreprise: %s\n\tAdresse de l'entreprise: %s\n\t Specialite de l'entreprise: %s\n\tNom du prof: %s\n\tPrenom du prof: %s\n\tTitre du prof: %s\n\n", i,
            (tmp1_liste)->nom_stag, (tmp1_liste)->prenom_stag, (tmp1_liste)->classe_stag,
            (tmp1_liste)->salaire_stag, (tmp1_liste)->annee_stag, (tmp1_liste)->entreprise.nom_en,
            (tmp1_liste)->entreprise.adresse_en, (tmp1_liste)->entreprise.specialite_en,
            (tmp1_liste)->professeur.nom_prof, (tmp1_liste)->professeur.prenom_prof,
            (tmp1_liste)->professeur.titre_prof);
// The last element becomes the precedent until it is the first
// When it will be the last one its preceding one becomes NULL
        (tmp1_liste) = (tmp1_liste)->precedent;
        i++;
    }
    printf("\n");
}


// Fonction to save in the file
void Enregistrer(stagiaires **tmp1_liste) {
    // Declare of liste.txt file in adding mode
    int i = 1;
    FILE *l = fopen("liste.txt", "a");

    // Print this message if there is any error
    if(l == NULL) {
        printf("Probleme a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    while((*tmp1_liste) != NULL) {
        fprintf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
            (*tmp1_liste)->nom_stag, (*tmp1_liste)->prenom_stag, (*tmp1_liste)->classe_stag,
            (*tmp1_liste)->salaire_stag, (*tmp1_liste)->annee_stag, (*tmp1_liste)->entreprise.nom_en,
            (*tmp1_liste)->entreprise.adresse_en, (*tmp1_liste)->entreprise.specialite_en,
            (*tmp1_liste)->professeur.nom_prof, (*tmp1_liste)->professeur.prenom_prof,
            (*tmp1_liste)->professeur.titre_prof);

        printf("**** stagiaire no %d ENREGISTRE AVEC SUCCES****\n", i);
        i++;

        (*tmp1_liste) = (*tmp1_liste)->precedent;
    }

    printf("\n");
    fclose(l);
    printf("\n");
}


// Viewing liste.txt file
void view() {
    int check = 0;
    // Declare the liste.txt file in read-only mode
    FILE *l = fopen("liste.txt", "r");

    // While we are not at the end of the file, view each caract
    while(check != EOF) {
        check = fgetc(l);
        if (check != EOF)
        printf("%c", check);
    }
    // Closing the liste.txt file
    fclose(l);
}

// Fonction to delete a student's informations
void supprimer() {
    char name1[TAILLE],
    name2[TAILLE],
    society[TAILLE],
    sir[TAILLE];
    int x,
    y,
    w,
    z,
    state,
    choice,
    test = 0;

    // Open two files : the original liste.txt and the temp copy.txt
    // The idea is to copy the infos in the tmp file excepting those of the student concerned
    // Delete and copy the infos in the original ones after being completely deleted before
    FILE *l,
    *p;
    p = fopen("copy.txt", "w");
    l = fopen("liste.txt", "r");
    // Declare a variable of stagiaires type
    stagiaires tmp1_liste;

    if(l == NULL || p == NULL) {
        printf("ERROR for accessing the file\n");
        exit(EXIT_FAILURE);
    }
    start:
    printf("Entrer les infos du stage\n");
    printf("Nom du stagiaire: ");
    modebuffer(name1, TAILLE);
    strcpy(name1, miniscule(name1));

    printf("Prenom du stagiaire: ");
    modebuffer(name2, TAILLE);
    strcpy(name2, miniscule(name2));

    printf("Nom de l'entreprise: ");
    modebuffer(society, TAILLE);
    strcpy(society, miniscule(society));

    printf("Nom de famille du professeur: ");
    modebuffer(sir, TAILLE);
    strcpy(sir, miniscule(sir));

    state = find_student(name1, name2, society, sir);

    if(state == -1) {
        // Student found in the file

        do
        {
            // Go along the original file
            fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                tmp1_liste.professeur.titre_prof);

// Compare the entered infos and those in the file
            x = strcmp(name1, tmp1_liste.nom_stag);
            y = strcmp(name2, tmp1_liste.prenom_stag);
            w = strcmp(society, tmp1_liste.entreprise.nom_en);
            z = strcmp(sir, tmp1_liste.professeur.nom_prof);

// while infos are different from those of the student copy them in the temp file
            if((x!=0 && y!=0 && w!=0 && z!=0)) {
                fprintf(p, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                    tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                    tmp1_liste.salaire_stag, tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                    tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                    tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                    tmp1_liste.professeur.titre_prof);
            }

            test = 1;
        }
        while(!feof(l));
// Closing files
        fclose(l);
        fclose(p);
// Delete the original file
        remove("liste.txt");
// Rename the temp file as the original
        rename("copy.txt", "liste.txt");

        if(test == 1)
        printf("informations supprimees avec succes\n");

// temp file for a possible future use
        p = fopen("copy.txt", "a");
        fclose(p);
    }
    else
    {
        // If not found restart or quit
        printf("stagiaire non present dans la liste\n");
        printf("Selectionner une option\n");
        printf("1. Recommencer\n");
        printf("2. Arreter\n");
        printf("---------> ");
        scanf("%d", &choice);
        buffer();
        printf("\n");

        if(choice == 1)
// Go to the beginning
        goto start;
        else
        {
            printf("\nAurevoir\n");
            exit(EXIT_FAILURE);
        }
    }
}


// Fonction to verify that a student exists in our current list
// Return -1 if found otherwise return 1
int find_student(char firstname[TAILLE], char lastname[TAILLE], char company[TAILLE], char teacher[TAILLE]) {
    stagiaires tmp1_liste;
    int b = 0,
    x,
    y,
    w,
    z;
    FILE *l;
    l = fopen("liste.txt", "r");

    if(l == NULL) {
        printf("ERROR for accessing the file\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
          tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
            &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
            tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
            tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
            tmp1_liste.professeur.titre_prof);

        x = strcmp(firstname, tmp1_liste.nom_stag);
        y = strcmp(lastname, tmp1_liste.prenom_stag);
        w = strcmp(company, tmp1_liste.entreprise.nom_en);
        z = strcmp(teacher, tmp1_liste.professeur.nom_prof);

        if((x==0 && y==0 && w==0 && z==0)) {
            b = 1;
            break;
        }
    }
    while(!feof(l));

    if(b == 1) {
        printf("informations correctes ! \n");
        return -1;
    }
    else
    {
        printf("Etudiant non present dans la liste\n");
    }

    fclose(l);
    return 1;
}

// Modify student's infos
void modifier() {
    char nom1[TAILLE],
    prenom1[TAILLE],
    classe[TAILLE];
    char nom2[TAILLE],
    adresse2[TAILLE],
    specialite2[TAILLE];
    char nom3[TAILLE],
    prenom3[TAILLE],
      /*date3[TAILLE],*/
    titre3[TAILLE];
    char name1[TAILLE],
    name2[TAILLE],
    society[TAILLE],
    sir[TAILLE];
    float salaire;
    int annee,
    choice,
    state,
    a,
    b,
    c;

    FILE *l,
    *p;
    l = fopen("liste.txt", "r");
    p = fopen("copy.txt", "w");
    stagiaires tmp1_liste;

    if(l == NULL || p == NULL) {
        printf("erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    start:
    printf("Entrer les infos du stage\n");
    printf("Nom du stagiaire: ");
    modebuffer(name1, TAILLE);
    strcpy(name1, miniscule(name1));

    printf("Prenom du stagiaire: ");
    modebuffer(name2, TAILLE);
    strcpy(name2, miniscule(name2));

    printf("Nom de l'entreprise: ");
    modebuffer(society, TAILLE);
    strcpy(society, miniscule(society));

    printf("Nom de famille du professeur: ");
    modebuffer(sir, TAILLE);
    strcpy(sir, miniscule(sir));

    state = find_student(name1, name2, society, sir);

    if (state == -1) {
        // Entrer les nouvelles informations
        printf("\nstagiaire trouve, procede a la suppression\n");
        printf("\n  *********************************\n");
        printf("\n** MODIFIER LES INFOS DU STAGIAIRE **\n ");
        printf("\n  *********************************\n");

        printf("Nom : ");
        modebuffer(nom1, TAILLE);
        strcpy(nom1, miniscule(nom1));

        printf("Prenom : ");
        modebuffer(prenom1, TAILLE);
        strcpy(prenom1, miniscule(prenom1));

        printf("Classe: ");
        modebuffer(classe, TAILLE);
        strcpy(classe, miniscule(classe));

        printf("Salaire: ");
        scanf("%f", &salaire);
        buffer();

        printf("Annee: ");
        scanf("%d", &annee);
        buffer();

        printf("\n*******************\n");
        printf("\n***  ENTREPRISE *** \n");
        printf("\n*******************\n");

        printf("Nom : ");
        modebuffer(nom2, TAILLE);
        strcpy(nom2, miniscule(nom2));

        printf("Adresse ");
        modebuffer(adresse2, TAILLE);
        strcpy(adresse2, miniscule(adresse2));

        printf("Specialite : ");
        modebuffer(specialite2, TAILLE);
        strcpy(specialite2, miniscule(specialite2));

        printf("\n******************************\n");
        printf("\n*** LE PROFESSEUR DE SUIVI ***\n");
        printf("\n******************************\n");

        printf("Nom : ");
        modebuffer(nom3, TAILLE);
        strcpy(nom3, miniscule(nom3));

        printf("Prenom : ");
        modebuffer(prenom3, TAILLE);
        strcpy(prenom3, miniscule(prenom3));

        printf("Titre: ");
        modebuffer(titre3, TAILLE);
        strcpy(titre3, miniscule(titre3));
    }
    else
    {
        printf("\nstagiaire non present dans la liste\n");
        printf("Selectionner une option\n");
        printf("1. Recommencer\n");
        printf("2. Arreter\n");
        printf("---------> ");
        scanf("%d", &choice);
        buffer();
                printf("\n");

        if(choice == 1)
        goto start;
        else
        {
            printf("\nAurevoir\n");
            exit(EXIT_FAILURE);
        }

    }

    do
    {
        fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
            tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
            &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
            tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
            tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
            tmp1_liste.professeur.titre_prof);

        a = strcmp(name1, tmp1_liste.nom_stag);
        b = strcmp(name2, tmp1_liste.prenom_stag);
        c = strcmp(society, tmp1_liste.entreprise.nom_en);

// For the given intern replace his informations with the new ones
        if((a==0 && b==0 && c==0)) {
            fprintf(p, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                nom1, prenom1, classe, salaire, annee, nom2, adresse2, specialite2, nom3,
                prenom3, titre3);
        }

// Keep the same infos for the remaining
        else
        {
            fprintf(p, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                tmp1_liste.salaire_stag, tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                tmp1_liste.professeur.titre_prof);
        }

    }while(!feof(l));

    fclose(l);
    fclose(p);
    remove("liste.txt");
    rename("copy.txt", "liste.txt");

    p = fopen("copy.txt", "a");
    fclose(p);
}


// FOnction to list the interns in a given company
void liste_stagiaire_entreprise() {
    int choice,
    test = 0,
    a,
    b,
    c;
    char nom_lse[TAILLE],
    adresse_lse[TAILLE],
    specialite_lse[TAILLE];
    FILE *l = fopen("liste.txt", "r");
    stagiaires tmp1_liste;
    
    if(l == NULL) {
        printf("Erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    start:

    printf("Entrer les infos de l'entreprise: \n");
    printf("Nom: ");
    modebuffer(nom_lse, TAILLE);
    strcpy(nom_lse, miniscule(nom_lse));

    printf("Adresse: ");
    modebuffer(adresse_lse, TAILLE);
    strcpy(adresse_lse, miniscule(adresse_lse));

    printf("Specialite: ");
    modebuffer(specialite_lse, TAILLE);
    strcpy(specialite_lse, miniscule(specialite_lse));

    do
    {
        fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
            tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
            &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
            tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
            tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
            tmp1_liste.professeur.titre_prof);

        a = strcmp(nom_lse, tmp1_liste.entreprise.nom_en);
        b = strcmp(adresse_lse, tmp1_liste.entreprise.adresse_en);
        c = strcmp(specialite_lse, tmp1_liste.entreprise.specialite_en);

        if ((a==0 && b==0 && c==0)) {
            printf("\n Les stagiaires de l'entreprise %s sont\n", nom_lse);
            printf("stagiaire : %s\t%s\n\tclasse: %s\n\tsalaire: %f\n\tannee: %d\n\tNom de l'entreprise: %s\n\tAdresse de l'entreprise: %s\n\t Specialite de l'entreprise: %s\n\tNom du prof: %s\n\tPrenom du prof: %s\n\tTitre du prof: %s\n\n",
                tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                tmp1_liste.salaire_stag, tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                tmp1_liste.professeur.titre_prof);
            test = 1;
        }
    }while(!feof(l));

    if(test != 1) {
        printf("Les informations entrees sont incorrectes\n");
        printf("Voullez-vous recommencer ?\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        scanf("%d", &choice);
        buffer();

        if(choice == 1)
        goto start;
        else
        {
            printf("Aurevoir!!!\n");
            exit(EXIT_FAILURE);
        }

    }
    fclose(l);
}


// Fonction to view the interns of a specific teacher
void liste_stagiaire_professeur() {
    char nom_lsp[TAILLE],
    prenom_lsp[TAILLE],
    titre_lsp[TAILLE];
    int test = 0,
    choice,
    a,
    b,
    c;
    stagiaires tmp1_liste;

    FILE *l = fopen("liste.txt", "r");
    if(l == NULL) {
        printf("Erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    start:

    printf("Entrer les infos de l'entreprise: \n");
    printf("Nom: ");
    modebuffer(nom_lsp, TAILLE);
    strcpy(nom_lsp, miniscule(nom_lsp));

    printf("Prenom: ");
    modebuffer(prenom_lsp, TAILLE);
    strcpy(prenom_lsp, miniscule(prenom_lsp));

    printf("Titre: ");
    modebuffer(titre_lsp, TAILLE);
    strcpy(titre_lsp, miniscule(titre_lsp));

    do
    {
        fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
            tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
            &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
            tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
            tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
            tmp1_liste.professeur.titre_prof);

        a = strcmp(nom_lsp, tmp1_liste.professeur.nom_prof);
        b = strcmp(prenom_lsp, tmp1_liste.professeur.prenom_prof);
        c = strcmp(titre_lsp, tmp1_liste.professeur.titre_prof);

        if ((a==0 && b==0 && c==0)) {
            printf("\n Les stagiaires de Mr %s %s sont\n", nom_lsp, prenom_lsp);
            printf("stagiaire : %s\t%s\n\tclasse: %s\n\tsalaire: %f\n\tannee: %d\n\tNom de l'entreprise: %s\n\tAdresse de l'entreprise: %s\n\t Specialite de l'entreprise: %s\n\tNom du prof: %s\n\tPrenom du prof: %s\n\tTitre du prof: %s\n\n",
                tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                tmp1_liste.salaire_stag, tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                tmp1_liste.professeur.titre_prof);
            test = 1;
        }
    }while(!feof(l));

    if(test != 1) {
        printf("Les informations entrees sont incorrectes\n");
        printf("Voullez-vous recommencer ?\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        scanf("%d", &choice);
        buffer();

        if(choice == 1)
        goto start;
        else
        {
            printf("Aurevoir!!!\n");
            exit(EXIT_FAILURE);
        }

    }
    fclose(l);
}

// Fonction to add a new visiting date of a given student
void date_visite() {
    char student_name1[TAILLE],
    student_name2[TAILLE],
    company_name[TAILLE],
    teacher_name[TAILLE];
    int state,
    a,
    b,
    c,
    choice;
    stagiaires tmp1_liste;
    FILE *p = fopen("date.txt", "a");
    FILE *l = fopen("liste.txt", "r+");
    if(l == NULL || p == NULL) {
        printf("Erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    start:
    printf("Voulez-Vous entrer la date pour quel stagiaire ?\n");
    printf("Nom du stagiaire: ");
    modebuffer(student_name1, TAILLE);
    strcpy(student_name1, miniscule(student_name1));

    printf("Prenom du stagiaire: ");
    modebuffer(student_name2, TAILLE);
    strcpy(student_name2, miniscule(student_name2));

    printf("Nom de l'entreprise: ");
    modebuffer(company_name, TAILLE);
    strcpy(company_name, miniscule(company_name));

    printf("Nom de famille du professeur: ");
    modebuffer(teacher_name, TAILLE);
    strcpy(teacher_name, miniscule(teacher_name));

    state = find_student(student_name1, student_name2, company_name, teacher_name);

    if(state == -1) {

        do
        {
            fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                tmp1_liste.professeur.titre_prof);

            a = strcmp(student_name1, tmp1_liste.nom_stag);
            b = strcmp(student_name2, tmp1_liste.prenom_stag);
            c = strcmp(company_name, tmp1_liste.entreprise.nom_en);

            if((a==0 && b==0 && c==0)) {
                // Pour l'etudiant concerne entree la date de visite
                printf("Entrer la date de visite pour %s %s: ", student_name1, student_name2);
                modebuffer(tmp1_liste.professeur.date_prof, TAILLE);
                strcpy(tmp1_liste.professeur.date_prof, miniscule(tmp1_liste.professeur.date_prof));

                fprintf(p, "%s\t%s\t%s\t%s\t%s\t%s\n\n", tmp1_liste.nom_stag, tmp1_liste.prenom_stag,
                    tmp1_liste.entreprise.nom_en, tmp1_liste.professeur.nom_prof,
                    tmp1_liste.professeur.prenom_prof, tmp1_liste.professeur.date_prof);
            }

        }while(!feof(l));
        fclose(l);
        fclose(p);
    }
    else{
         printf("stagiaire non present dans la liste\n");
        printf("Selectionner une option\n");
        printf("1. Recommencer\n");
        printf("2. Arreter\n");
        printf("---------> ");
        scanf("%d", &choice);
        buffer();
                printf("\n");

        if(choice == 1)
        goto start;
        else
        {
            printf("\nAurevoir\n");
            exit(EXIT_FAILURE);
        }
    }
}

// Fonction to view dates of visit of teachers
void aff_date_visite() {
    FILE *p;
    p = fopen("date.txt", "r");
    stagiaires tmp1_liste;
    if(p == NULL) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        fscanf(p, "%s\t%s\t%s\t%s\t%s\t%s\n\n", tmp1_liste.nom_stag, tmp1_liste.prenom_stag,
            tmp1_liste.entreprise.nom_en, tmp1_liste.professeur.nom_prof,
            tmp1_liste.professeur.prenom_prof, tmp1_liste.professeur.date_prof);

        printf("Nom: %s\tPrenom: %s\tNom entreprise: %s\tNom prof: %s\tPrenom prof: %s\tDATE DE VISITE: %s\n\n", tmp1_liste.nom_stag, tmp1_liste.prenom_stag,
            tmp1_liste.entreprise.nom_en, tmp1_liste.professeur.nom_prof,
            tmp1_liste.professeur.prenom_prof, tmp1_liste.professeur.date_prof);

    }while(!feof(p));
    fclose(p);
}

// Fonction to add results for a given student 
void resultat() {
    char student_name1[TAILLE],
    student_name2[TAILLE],
    company_name[TAILLE],
    teacher_name[TAILLE];
    int state,
    a,
    b,
    c,
    choice;
    FILE *p = fopen("resultat.txt", "a");
    FILE *l = fopen("liste.txt", "r+");
    stagiaires tmp1_liste;

    if(l == NULL || p == NULL) {
        printf("Erreur a l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    start:
    printf("Voulez-Vous entrer la date pour quel stagiaire ?\n");
    printf("Nom du stagiaire: ");
    modebuffer(student_name1, TAILLE);
    strcpy(student_name1, miniscule(student_name1));

    printf("Prenom du stagiaire: ");
    modebuffer(student_name2, TAILLE);
    strcpy(student_name2, miniscule(student_name2));

    printf("Nom de l'entreprise: ");
    modebuffer(company_name, TAILLE);
    strcpy(company_name, miniscule(company_name));

    printf("Nom de famille du professeur: ");
    modebuffer(teacher_name, TAILLE);
    strcpy(teacher_name, miniscule(teacher_name));

    state = find_student(student_name1, student_name2, company_name, teacher_name);

    if(state == -1) {
        do
        {
            fscanf(l, "%s\t%s\t%s\t%f\t%d\t%s\t%s\t%s\t%s\t%s\t%s\n",
                tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.classe_stag,
                &tmp1_liste.salaire_stag, &tmp1_liste.annee_stag, tmp1_liste.entreprise.nom_en,
                tmp1_liste.entreprise.adresse_en, tmp1_liste.entreprise.specialite_en,
                tmp1_liste.professeur.nom_prof, tmp1_liste.professeur.prenom_prof,
                tmp1_liste.professeur.titre_prof);

            a = strcmp(student_name1, tmp1_liste.nom_stag);
            b = strcmp(student_name2, tmp1_liste.prenom_stag);
            c = strcmp(company_name, tmp1_liste.entreprise.nom_en);

            if((a==0 && b==0 && c==0)) {
                printf("Entrer les resultats de %s %s\n", student_name1, student_name2);
                printf("mention(mauvais, passable, bien, excellent): ");
                modebuffer(tmp1_liste.mention, TAILLE);
                strcpy(tmp1_liste.mention, miniscule(tmp1_liste.mention));

                printf("moyenne: ");
                scanf("%f", &tmp1_liste.moy_soutenance);
                buffer();

                fprintf(p, "%s\t%s\t%s\t%s\t%s\t%s\t%f\n\n", tmp1_liste.nom_stag, tmp1_liste.prenom_stag,
                    tmp1_liste.entreprise.nom_en, tmp1_liste.professeur.nom_prof,
                    tmp1_liste.professeur.prenom_prof, tmp1_liste.mention, tmp1_liste.moy_soutenance);
            }
        }while(!feof(l));
    }
    else
    {
         printf("stagiaire non present dans la liste\n");
        printf("Selectionner une option\n");
        printf("1. Recommencer\n");
        printf("2. Arreter\n");
        printf("---------> ");
        scanf("%d", &choice);
        buffer();
                printf("\n");

        if(choice == 1)
        goto start;
        else
        {
            printf("\nAurevoir\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(l);
    fclose(p);
}

// Fonction to view the results
void aff_resultat() {
    FILE *p;
    p = fopen("resultat.txt", "r");
    stagiaires tmp1_liste;

    if(p == NULL) {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        fscanf(p, "%s\t%s\t%s\t%s\t%s\t%s\t%f\n\n",
            tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.entreprise.nom_en, tmp1_liste.professeur.nom_prof,
            tmp1_liste.professeur.prenom_prof, tmp1_liste.mention, &tmp1_liste.moy_soutenance);

        printf("Nom: %s\tPrenom: %s\tNom entreprise: %s\tNom prof: %s\tPrenom prof: %s\tMENTION: %s\tMOYENNE: %f\n\n",
            tmp1_liste.nom_stag, tmp1_liste.prenom_stag, tmp1_liste.entreprise.nom_en, tmp1_liste.professeur.nom_prof,
            tmp1_liste.professeur.prenom_prof, tmp1_liste.mention, tmp1_liste.moy_soutenance);

    }while(!feof(p));
    fclose(p);
}
