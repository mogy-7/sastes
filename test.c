// #ifndef MAIN_H
// #define MAIN_H

// les bibliotique etuliser .
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>
#include <time.h>
#include <ctype.h>

//  time_t tt ;
// struct tm* dt;
// int jour ;
// int mois ;
// int  anne ;

#define MAX_TACHES 100

typedef struct s_date
{
	int anne;
	int mois;
	int jour;
} date;
typedef struct s_status
{
	char statusname[20];
	int tag;
} status;

typedef struct s_tache
{
	int id;
	char titre[50];
	char descr[100];
	date deadline;
	status statuses;
	int joures;
	date criation;
} Tache;

Tache troi[MAX_TACHES];
int nbrtroi = 0;

Tache tache[MAX_TACHES];
int nbrTaches = 0;

void affichage(Tache T[], int a)
{
	for (int i = 0; i < a; i++)
	{
		printf("\nID : %d\n", T[i].id);
		printf("Titre : %s\n", T[i].titre);
		printf("descr : %s\n", T[i].descr);
		printf("Deadline : %d", T[i].deadline.anne);
		printf("/%d", T[i].deadline.mois);
		printf("/%d\n", T[i].deadline.jour);
		printf("Statut : %s\n", T[i].statuses.statusname);
		printf("Date de creation : %d", T[i].criation.jour);
		printf("/%d", T[i].criation.mois);
		printf("/%d\n", T[i].criation.anne);
		printf("\n");
	}
}

int timecalc(int a, int b, int c)
{
	time_t tt = time(NULL);
	struct tm *dt = localtime(&tt);
	int jour = dt->tm_mday;
	int mois = dt->tm_mon + 1;
	int anne = dt->tm_year + 1900;
	;
	;
	// int jour ;
	// int mois ;
	// int  anne ;

	int y = anne - a;
	int m;
	if (mois - b <= 0 && y >= 1)
	{
		y--;
		b += 12;
	}
	m = mois - b;
	int d;
	if (jour - c < 0 && m >= 1)
	{
		m--;
		c += 30;
	}
	d = jour - c;
	int days = -(d + m * 30 + y * 365);
	return days;
}

void ajtTache(int a)
{
	time_t tt = time(NULL);
	struct tm *dt = localtime(&tt);
	int D = dt->tm_mday;
	int M = dt->tm_mon + 1;
	int Y = dt->tm_year + 1900;
	int N = 0;
	int d;

	if (nbrTaches >= MAX_TACHES)
	{
		printf("La liste de taches est pleine. Impossible d'ajouter plus de taches.\n");
		return;
	}

	Tache buffer;
	while (N < a)
	{
		buffer.criation.anne = Y;
		buffer.criation.mois = M;
		buffer.criation.jour = D;
		buffer.id = nbrTaches + 1;
		printf("Titre de la %d tache : ", N + 1);
		scanf(" %[^\n]", buffer.titre);

		printf("Description de la %d tache   : ", N + 1);
		scanf(" %[^\n]", buffer.descr);
		printf("==================== on 'est on %d/%d/%d =====================\n", D, M, Y);
		printf("entre le deadline  : \n");
anne:
		printf("\n\tentrer l'annee :  ");
		scanf(" %d", &d);
		if (d < 2023 || d > 2100)
		{
			printf("\n\t\tinvalid anne !!!\n");
			goto anne;
		}
		buffer.deadline.anne = d;
		int y = d;
moi:
		printf("\n\t entrer le moi  :  ");
		scanf(" %d", &d);
		if ((d < 1 || d > 12) || (d < M && y - Y < 1))
		{
			printf("\n\t\tinvalid moi !!!\n");
			goto moi;
		}
		buffer.deadline.mois = d;
		int m = d;
jour:
		printf("\n\t entrer le jour  :  ");
		scanf(" %d", &d);
		if ((d < 1 || d > 30) || (d < D && m - M < 1 && y - M < 1))
		{
			printf("\n\t\tinvalid jour !!!\n");
			goto jour;
		}
		buffer.deadline.jour = d;
		buffer.joures = timecalc(buffer.deadline.anne, buffer.deadline.mois, buffer.deadline.jour);
status:
		int s;
		printf("\nStatut de de la %d tache :\n\tpour a realiser entrer (1) .\n\tpour en cours (2) .\n\tpour finalisee (3) .\n", N + 1);
		printf("=======================================> ");
		scanf(" %d", &s);
		if (s == 1)
		{
			strcpy(buffer.statuses.statusname, "a realiser");
			buffer.statuses.tag = 1;
		}
		else if (s == 2)
		{
			strcpy(buffer.statuses.statusname, "en cours");
			buffer.statuses.tag = 2;
		}
		else if (s == 3)
		{
			strcpy(buffer.statuses.statusname, "finalisee");
			buffer.statuses.tag = 3;
		}
		else
		{
			puts("\n\t\tinvalide choix !!!");
			goto status;
		}
		tache[nbrTaches++] = buffer;
		N++;
	}
	printf("\n\t~Tache ajoutee avec succes!~\n");
}

void troifun()
{
	int count = 1;
	for (int i = 0; i < nbrTaches; i++)
	{
		// printf(" les jour sont %d ", tache[i].joures);
		if (tache[i].joures <= 3)
		{
			printf("ID : %d\n", tache[i].id);
			printf("Titre : %s\n", tache[i].titre);
			printf("descr : %s\n", tache[i].descr);
			printf("Deadline : %d", tache[i].deadline.anne);
			printf("/%d", tache[i].deadline.mois);
			printf("/%d\n", tache[i].deadline.jour);
			printf("Statut : %s\n", tache[i].statuses.statusname);
			printf("\n");
			count = 0;
		}
	}
	if (count)
	{
		printf("\n\t~n'exist pas~\n");
	}
}

void triParTitre(Tache tab[], int nbr)
{

	for (int i = 0; i < nbr - 1; i++)
	{
		for (int j = 0; j < nbr - i - 1; j++)
		{
			if (strcmp(tab[j].titre, tab[j + 1].titre) > 0)
			{
				Tache tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
	affichage(tab, nbr);
}
void triPard()
{

	for (int i = 0; i < nbrTaches - 1; i++)
	{
		for (int j = 0; j < nbrTaches - i - 1; j++)
		{
			if (tache[j].joures > tache[j + 1].joures)
			{
				Tache tmp = tache[j];
				tache[j] = tache[j + 1];
				tache[j + 1] = tmp;
			}
		}
	}
	affichage(tache, nbrTaches);
}

void AfficherTaches()
{
	if (nbrTaches == 0)
	{
		printf("Aucune tache trouvee.\n");
		return;
	}
	while (1)
	{
		int a;
tri:
		printf("pour affichier  les taches trier :\n\tpar ordre alphabetique entrer (1).\n\tpar deadline (2).\n\tdeadline est dans 3 jours ou moins (3).\n");
		printf("=======================>   ");
		scanf("%d", &a);
		if (a == 1)
		{
			triParTitre(tache, nbrTaches);
		}
		else if (a == 2)
		{
			triPard();
		}
		else if (a == 3)
		{
			troifun();
		}
		else
		{
			printf("nombre de choix invalid");
			goto tri;
		}
		int z;
		printf("voulez-vous afficher la list des taches autres fois ? [Y/N] : ");
ask:
		z = getchar();
		if (z == 'Y' || z == 'y')
		{
			continue;
		}
		else if (z == 'N' || z == 'n')
		{
			break;
		}
		else
		{
			goto ask;
		}
	}
}
int chrParid(int a)
{
	int B = 0;
	int F = nbrTaches;
	while (B <= F)
	{
		int M = (B + F) / 2;
		if (tache[M].id == a)
			return M;
		else if (tache[M].id < a)
			B = M + 1;
		else
			F = M - 1;
	}
	return -1;
}

// int chrPart(char tab[]){
//     triParTitre(tache,nbrTaches);
//     int B = 0;
//     int F = nbrTaches;
//     while(B <= F ){
//         int M = (B + F)/2;
//         if (strcmp(tache[M].titre,tab) == 0)
//             return M;
//         else if (strcmp(tache[M].titre,tab) < 0)
//             B = M + 1;
//         else
//             F = M - 1;
//     }
//     return -1;
// }
int chrPart(char tab[])
{
	int M = -1;
	for (int i = 0; i < nbrTaches; i++)
	{
		if (strcmp(tache[i].titre, tab) == 0)
		{
			return i;
		}
	}
	return M;
}

int midifyer(int d, int i)
{
	time_t tt = time(NULL);
	struct tm *dt = localtime(&tt);
	int jour = dt->tm_mday;
	int mois = dt->tm_mon + 1;
	int anne = dt->tm_year + 1900;
	int N = 0;

	char buffer[100];
	int n, s;
	if (d == 1)
	{
		printf("entre la modification de la description ici :  ");
		scanf(" %[^\n]", buffer);
		strcpy(tache[i].descr, buffer);
	}
	else if (d == 2)
	{
		printf("entre la modification de le statut ici :  \n");
status:
		printf("Statut de la tache :\n  pour a realiser entrer (1) :\n  pour en cours (2) :\n  pour finalisee (3) : ");
		scanf(" %d", &s);
		if (s == 1)
		{
			strcpy(tache[i].statuses.statusname, "a realiser");
			tache[i].statuses.tag = 1;
		}
		else if (s == 2)
		{
			strcpy(tache[i].statuses.statusname, "en cours");
			tache[i].statuses.tag = 2;
		}
		else if (s == 3)
		{
			strcpy(tache[i].statuses.statusname, "finalisee");
			tache[i].statuses.tag = 3;
		}
		else
		{
			puts("\tinvalide input \n");
			goto status;
		}
	}
	else if (d == 3)
	{
		printf("entre la modification de le deadline ici :  ");
did:
		printf("\n\tentre l'anne : ");
		scanf("%d", &n);
		if (n < 2023 || n > 2100)
		{
			printf("\n\t invalid annee !!\n");
			goto did;
		}
		tache[i].deadline.anne = n;
		int y = n;
mo:
		printf("\n\tentre le moi : ");
		scanf("%d", &n);
		if ((n < 1 || n > 12) || (n < mois && n - y < 1))
		{
			printf("\n\t invalid moi !!\n");
			goto mo;
		}
		tache[i].deadline.mois = n;
		int m = n;
jo:
		printf("\n\tentre le jour : ");
		scanf("%d", &n);
		if ((n < 1 || n > 30) || (n < jour && (m - mois < 1 && y - anne < 1)))
		{
			printf("\n\t invalid jour !!\n");
			goto jo;
		}
		tache[i].deadline.jour = n;
	}
	else
	{
		return -1;
	}
}

void modify()
{
	while (1)
	{
		if (nbrTaches <= 0)
		{
			printf("\n\t~n'est pas de tache pour modifier~\n");
			return;
		}
		int n;
		int i, d;
start:
		printf("entre le id de la tache : ");
		scanf("%d", &n);
		i = chrParid(n);
		if (i == -1)
		{
			printf("\tid invalid \n");
			goto start;
		}
modi:
		printf("\tpour  Modifier la description entrer (1) .\n ");
		printf("\tpour Modifier le statut d'une tache (2) .\n");
		printf("\tModifier le deadline d'une tache entrer (3) .\n");
		printf("==================================================> ");
		scanf("%d", &d);
		if (midifyer(d, i) == -1)
		{
			printf("\tinvalid choix ! \n");
			goto modi;
		}

		char c;
		printf("\tvoulez-vous le modifier des autres tache ? [Y/N] : ");
ask:
		c = getchar();
		if (c == 'Y' || c == 'y')
		{
			continue;
		}
		else if (c == 'N' || c == 'n')
		{
			break;
		}
		else
		{
			goto ask;
		}
	}
}

void suprimer()
{   
    if (nbrTaches <= 0)
		{
			printf("n'est pas de tache pour suprimer \n");
			return;
		}
    int s;
    printf("si vous voulez tout supprimer entrer (0) :  ");
    scanf("%d",&s);
    if (s == 0)
    {
        nbrTaches = 0;
        printf("\n\t~Tout est suprimer~");
        return;
    }
    
	while (1)
	{
		if (nbrTaches <= 0)
		{
			printf("n'est pas de tache pour suprimer \n");
			break;
		}
		int n;
		int i, d;

start:
		printf("entre le id de la tache : ");
		scanf("%d", &n);
		i = chrParid(n);
		if (i == -1)
		{
			printf("\tid invalid \n");
			goto start;
		}
		Tache tmp = tache[i];
		tache[nbrTaches - 1] = tache[i];
		tache[i] = tache[nbrTaches - 1];
		nbrTaches--;
		if (nbrTaches <= 0)
		{
			printf("\tsuprimer avec succer !!\n\tnombre de tahce est vide !!! \n");
			return;
		}
		char q;
au:
		printf("un aute tache ? [Y/N] :  ");
		q = getchar();
		if (q == 'Y' || q == 'y')
		{
			continue;
		}
		else if (q == 'N' || q == 'n')
		{
			break;
		}
		else
		{
			goto au;
		}
	}
}

void affichtache(int a)
{
	int i = a - 1;
	printf("ID : %d\n", tache[i].id);
	printf("Titre : %s\n", tache[i].titre);
	printf("descr : %s\n", tache[i].descr);
	printf("Deadline : %d", tache[i].deadline.anne);
	printf("/%d", tache[i].deadline.mois);
	printf("/%d\n", tache[i].deadline.jour);
	printf("Statut : %s\n", tache[i].statuses.statusname);
	printf("\n");
}

void rechercher()
{
	while (1)
	{
		if (nbrTaches <= 0)
		{
			printf("\tNombre des taches est vide !!\n");
			return;
		}
		int n;
		int i, d, r;

		printf("pour recherchrer par id entrer (1) :\npour rechercher par titre entrer (2) : ");
chr:
		scanf("%d", &r);
		if (r < 1 || r > 2)
		{
			printf("\tinvalid choix !!");
			goto chr;
		}
		if (r == 1)
		{
start:
			printf("entre le id de la tache : ");
			scanf("%d", &n);
			i = chrParid(n);
			if (i == -1)
			{
				printf("\tid invalid \n");
				goto start;
			}
			affichtache(i + 1);
		}
		else if (r == 2)
		{
bf:
			char buffer[50];
			printf("entre le titre de la tache : ");
			scanf(" %s", buffer);
			i = chrPart(buffer);
			if (i == -1)
			{
				printf("\ttitre invalid \n");
				goto bf;
			}
			affichtache(i + 1);
		}
		char c;
		printf("voulez-vous rechercher autres tache ? [Y/N] : ");
ask:
		c = getchar();
		if (c == 'Y' || c == 'y')
		{
			continue;
		}
		else if (c == 'N' || c == 'n')
		{
			break;
		}
		else
		{
			goto ask;
		}
	}
}

void statis()
{

	if (nbrTaches <= 0)
	{
		printf("n'est pas de tache !! \n");
		return;
	}
	while (1)
	{
		int n;
f:
		printf("pour afficher le nombre total des taches entrer (1) : \n");
		printf("pour afficher le nombre de taches completes et incompletes entrer (2) : \n");
		printf("pour afficher le nombre de jours restants jusqu'au delai de chaque tache (3) : \n");
		printf("======================================================================================> ");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("le nombre total des taches est :  %d \n", nbrTaches);
		}
		else if (n == 2)
		{
			int C = 0, I = 0;
			for (size_t i = 0; i < nbrTaches; i++)
			{
				if (tache[i].statuses.tag == 3)
				{
					C++;
				}
				else
				{
					I++;
				}
			}
			printf("\n\tle nombre de taches completes est : %d", C);
			printf("\n\tle nombre de taches incompletes est : %d\n\n", I);
		}
		else if (n == 3)
		{
			for (size_t i = 0; i < nbrTaches; i++)
			{
				printf("\nID : %d\n", tache[i].id);
				printf("Titre : %s\n", tache[i].titre);
				printf("le nombre de jours restants : %d j\n", tache[i].joures);
			}
		}
		else
		{
			printf("\tchoix invalid !!");
			goto f;
		}
strt:
		char v;
		printf("voulez-vous  des autres static [Y/N] ? ");
		v = getchar();
		if (v == 'Y' || v == 'y')
			continue;
		else if (v == 'N' || v == 'n')
			break;
		else
		{
			goto strt;
		}
	}
}

int main()
{
	int choix, f;
	int n;
	while (1)
	{
		printf("\n\nMenu principal:\n");
		printf("====================================\n");
		printf("1. Ajouter nouvelles taches .\n");
		printf("2. Afficher la liste des toutes les taches (triees).\n");
		printf("3. Modifier un tache .\n");
		printf("4. Suprimer un tache .\n");
		printf("5. Rechercher les Taches  .\n");
		printf("6. Statistiques .\n");
		printf("7.  Quitere  .\n");
		printf("=========>Entrez votre choix : ");
		scanf("%d", &choix);
		switch (choix)
		{
			case 1:
nmbr:
				printf("\nentre le nombre de taches : ");
				scanf("%d", &n);
				if (n <= 0)
				{
					printf("nombre de tache invalid !\n");
					goto nmbr;
				}
				else if (n > 100)
				{
					printf("\n\t~tu passes les limit des taches~\n");
					goto nmbr;
				}
				else if (n > 10)
				{
					printf("\n\t~c'est traux mai pas problem~\n");
				}

				ajtTache(n);
				break;
			case 2:
				AfficherTaches();
				break;
			case 3:
				modify();
				break;
			case 4:
				suprimer();
				break;
			case 5:
				rechercher();
				break;
			case 6:
				statis();
				break;
			case 7:
				printf("Au revoir!\n");
				exit(0);
			default:
				printf("Choix invalide !!!\n\t Veuillez reessayer.\n");
		}
	}
}
