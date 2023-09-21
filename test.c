// #ifndef MAIN_H
// #define MAIN_H

// les bibliotique etuliser .
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
#include <time.h>
#include <ctype.h>

     time_t tt ;
    struct tm* dt;
    int jour ;
    int mois ;
    int  anne ;
    

#define MAX_TACHES 100


typedef struct s_date{
    int anne;
    int mois;
    int jour;
}date;
typedef struct s_status{
    char statusname[20];
    int tag;
}status;

typedef struct s_tache{
    int id;
    char titre[50];
    char descr[100];
    date deadline; 
    status statuses;   
    int joures;
}Tache;

Tache troi[MAX_TACHES];
int nbrtroi = 0;

Tache tache[MAX_TACHES];
int nbrTaches = 0;

   void affichage(Tache T[], int a){
    int b = a;
    for (int i = 0; i < b; i++) {
        printf("ID : %d\n", T[i].id);
        printf("Titre : %s\n", T[i].titre);
        printf("descr : %s\n", T[i].descr);
        printf("Deadline : %d", T[i].deadline.anne);
        printf("/%d",T[i].deadline.mois);
        printf("/%d\n", T[i].deadline.jour);
        printf("Statut : %s\n", T[i].statuses.statusname);
        printf("\n");
    }
 }

int timecalc(int a, int b, int c ){
    tt = time(NULL);
     dt = localtime(&tt);
    jour  = dt->tm_mday;
    mois = dt->tm_mon+1;
    anne = dt->tm_year+1900;

    int y = anne - a;
    int m;
    if (mois - b <= 0 && y >= 1)
    {
        y--;
       b += 12;
    }
    m =  mois - b;
    int d;
    if (jour - c < 0 && m >= 1)
    { m--;
     c += 30; }
    d = jour - c;
     int days = -(d + m*30 + y*365);
       return days;
    
}



void ajtTache(int a){
       time_t tt = time(NULL);
    struct tm* dt = localtime(&tt);
    int jour  = dt->tm_mday;
    int mois = dt->tm_mon+1;
    int  anne = dt->tm_year+1900;
    int N = 0;
    int d;
    
    if (nbrTaches >= MAX_TACHES) {
        printf("La liste de taches est pleine. Impossible d'ajouter plus de taches.\n");
        return;
    }
    
    Tache buffer;
    while(N < a){
    buffer.id = nbrTaches + 1;
    printf("Titre de la %d tache : ",N+1);
    scanf(" %[^\n]", buffer.titre);

    printf("Description de la %d tache : ",N+1);
    scanf(" %[^\n]", buffer.descr);
    printf(" on 'est on %d/%d/%d\n",jour,mois,anne);
    printf("Date limite  : \n");
    anne:
    printf("\tentrer l'annee :  ");
    scanf(" %d", &d);
    if (d < 2023)
    {
        printf("\t\tinvalid anne!\n");
        goto anne;
    }
    buffer.deadline.anne = d;
    int y = d;
    moi:
    printf("\t entrer le moi  :  ");
   scanf(" %d", &d);
    if ((d < 1 || d > 12 ) || (d < mois && y - anne < 1 ))
    {
        printf("\t\tinvalid moi!\n");
        goto moi;
    }
    buffer.deadline.mois = d;
    int m = d;
    jour:
    printf("\t entrer le jour  :  ");
    scanf(" %d", &d);
     if ((d < 1 || d > 30) || (d < jour && m - mois < 1 && y - anne < 1 ))
    {
        printf(" invalid jour !\n");
        goto jour;
    }
    buffer.deadline.jour = d;
    buffer.joures = timecalc(buffer.deadline.anne,buffer.deadline.mois,buffer.deadline.jour );

    status:
    int s;
    printf("Statut de la %d tache\n  pour a realiser entrer (1) :\n  pour en cours (2) :\n  pour finalisee (3) : ",N+1);
    scanf(" %d",&s);
    if(s == 1){
        strcpy(buffer.statuses.statusname,"a realiser");
            buffer.statuses.tag = 1;
    }
    else if(s == 2){
        strcpy(buffer.statuses.statusname,"en cours");
        buffer.statuses.tag = 2;
    }
    else if(s == 3){
       strcpy(buffer.statuses.statusname,"finalisee");
       buffer.statuses.tag = 3;
    }
    else{
        puts("invalide input ");
         goto status;
    }
    tache[nbrTaches++] = buffer;
    N++;
    }
    printf("Tache ajoutee avec succes!\n");
    }

void troifun(){
            int count = 1;
    for (int i = 0; i < nbrTaches; i++) {
        // printf(" les jour sont %d ", tache[i].joures);
        if (tache[i].joures <= 3)
        {
        printf("ID : %d\n", tache[i].id);
        printf("Titre : %s\n", tache[i].titre);
        printf("descr : %s\n", tache[i].descr);
        printf("Deadline : %d", tache[i].deadline.anne);
        printf("/%d",tache[i].deadline.mois);
        printf("/%d\n", tache[i].deadline.jour);
        printf("Statut : %s\n", tache[i].statuses.statusname);
        printf("\n");
        count = 0;
        }
    }
    if (count)
    {
        printf("taches dont le deadline est dans 3 jours ou moins n'exist pas\n");
    }
    
}
 

void triParTitre(Tache tab[],int nbr){
         int nbrr = nbr;
         // Trie les tâches par titre
    for (int i = 0; i < nbrr - 1; i++) {
        for (int j = 0; j < nbrr - i - 1; j++){
            if (strcmp(tab[j].titre, tab[j + 1].titre) > 0){
                Tache tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
            }
        }
    affichage(tab,nbrr);
}
void triPard(){
    
     for (int i = 0; i < nbrTaches - 1; i++)
        {
        for (int j = 0; j < nbrTaches - i - 1; j++)
            {
            if (tache[j].joures > tache[j+1].joures)
                {
                 Tache tmp = tache[j];
                tache[j] = tache[j + 1];
                tache[j + 1] = tmp;
                }
            }
        }
        affichage(tache,nbrTaches);


}




int AfficherTaches(){
    if (nbrTaches == 0) {
        printf("Aucune tache trouvee.\n");
        return 1;
    }
    int a;
     tri:  
      printf("pour trier les taches\n par ordre alphabetique entrer (1)\n, par deadline (2)\n,  deadline est dans (3) jours ou moins : \n");
      scanf("%d",&a);
    if(a == 1){
        triParTitre(tache,nbrTaches);
               }
    else if (a == 2)
    {
        triPard();
    }
    else if (a == 3)
    {
        troifun();
    }
    else{
        printf("nombre de choix invalid");
        goto tri;
    }


    return 0;
    
}
int triParid(int a){
    int B = 0;
    int F = nbrTaches;
    while(B <= F ){
        int M = (B + F)/2;
        if (tache[M].id == a)
            return M;
        else if (tache[M].id < a)
            B = M + 1;
        else
            F = M - 1;
    }
    return -1;
}


int  midifyer(int d,int i){
    char buffer[100];
    int n;
    if (d == 1)
    {
        printf("entre la modification de la description ici :  ");
            scanf("%s",buffer);
            strcpy(tache[i].descr,buffer);
    }
    else if (d == 2)
    {
       printf("entre la modification de le statut ici :  ");
            scanf("%s",buffer);
            strcpy(tache[i].statuses.statusname,buffer);
    }
    else if (d == 3)
    {
        printf("entre la modification de le deadline ici :  ");
            printf("\n\tentre l'anne : ");
            scanf("%d",n);
            tache[i].deadline.anne;
            printf("\n\tentre le moi : ");
            scanf("%d",n);
            tache[i].deadline.mois = n;
            printf("\n\tentre le jour : ");
            scanf("%d",n);
            tache[i].deadline.jour;

    }
    else
    {
        return -1;
    }
    
    
}


void modify(){
      if (nbrTaches <= 0)
    {
        printf("n'est pas de tache pour modifier \n");
        return;
    }
    int n;
    int i,d;

    while (1)
    {
        start:
       printf("entre le id de la tache : ");
       scanf("%d",n);
      if (triParid() == -1)
      {
        printf("\tid invalid ");
        goto start;
      }
      modi:
      printf("pour  Modifier la description entrer (1) .\n ");
      printf("pour Modifier le statut d'une tache (2) .\n");
      printf("Modifier le deadline d'une tache entrer (3) .\n");
      scanf("%d",d);
     if (midifyer(d,i) == -1)
     {
        printf("invalid choix ! ");
        goto modi;
     }
     

    
    }
    
  
    
    
}

// int main();
// int AfficherTaches(int a);
// void ajtTache(int a);
// int timecalc(int a, int b, int c );
// int troifun();
// void affichage(Tache T[], int a);
// void trieParDl(Tache B[],int N);
// void triParTitre(Tache tab[],int nbr);

// #endif

int main() {
    int choix, f;
    int n;
    while (1) {
        printf("\nMenu principal:\n");
        printf("1. Ajouter nouvelles taches\n");
        printf("2. Afficher la liste de toutes les taches (triees)\n");
        printf("3. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);
        switch (choix){
            case 1:
            printf("entre le nombre de taches : ");
            scanf("%d",&n);
            ajtTache(n);
                break;
            case 2:
                AfficherTaches();
                break;
            case 3:
                modify();
            case 4:
                printf("Au revoir!\n");
                exit(0);
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}