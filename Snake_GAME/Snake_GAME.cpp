// Snake_GAME.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Versiune 1.0
// Detalii: JOC SNAKE PRE SETAT LA 20x20 definit cu careu , fara ziduri externe - adica poate trece dintr-o parte in alta, limitat la 100 de puncte -- jocul se finalizeaza daca se mananca pe sine insusi
// corpul sarpelui memorat intr-o structura, capul este separat
// generarea automata a fructului si aleatorie  (relativ)

// Imbunatatiri : mai multe nivele si dezvolatarea lor. Reducerea nr. de operatii pe secunda si fluidizarea jocului
//			-> implementarea nivelului memorand matricea (aducerea obstacolelor, eventual a zidurilor si portilor de trecere)
//			-> optiunea de pauza
//			-> meniu

// Data 25/10/2019

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int sfarsitjoc = 1;
int n, m;
int directie_inaintare=1;
int cap_x, cap_y;
int harta[40][40];
int scor;
int fruct_x, fruct_y;

typedef struct
{
	int x;
	int y;
}corp;

corp sarpe[100];

void initializare_joc()
{
	n = 20;		// dimensiune mapa
	m = 20;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			harta[i][j] = 0;
	
	cap_x = 2;		// pozitie cap initiala
	cap_y = 2;
	scor = 0;
	fruct_x = 9;	// pozitie fruct initiala
	fruct_y = 11;

	for (int i = 0; i < 100; i++) // initializare corp sarpe
	{
		sarpe[i].x = -1;
		sarpe[i].y = -1;
	}
}

void desenare_harta_careu_nivel() 
{
	cout << "       Scor: " << scor << "\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (i == 0 || j == 0 || i == n - 1 || j == m - 1)	// margine zona
				cout << "&";
			else
			{
				if (i == cap_x && j == cap_y)	// cap sarpe
					cout << "A";
				else
				{
					int puscorp = 0;
					for (int iscor = 0; iscor < scor; iscor++)			/// desenare corp
						if (sarpe[iscor].x == i && sarpe[iscor].y == j)
						{
							cout << "a";
							puscorp = 1;
							break;
						}
					if (puscorp == 0)
					{
						if (i == fruct_x && j == fruct_y)		// punere fruct
							cout << "@";
						else
							cout << " ";			// spatiul gol
					}
				}

			}
		}
		cout << "\n";
	}
}

void deplasare_stanga()
{
	//harta[cap_x][cap_y] = 0;
	for (int i = scor; i > 0; i--)
		sarpe[i] = sarpe[i - 1];
	sarpe[0].x = cap_x;
	sarpe[0].y = cap_y;
	cap_y--;
	if (cap_y <= 0)
		cap_y = m - 2;
	//harta[cap_x][cap_y] = 2;
}

void deplasare_dreapta()
{
	harta[cap_x][cap_y] = 0;
	for (int i = scor; i > 0; i--)
		sarpe[i] = sarpe[i - 1];
	sarpe[0].x = cap_x;
	sarpe[0].y = cap_y;
	cap_y++;
	if (cap_y >= m-1)
		cap_y = 1;
	harta[cap_x][cap_y] = 2;
}

void deplasare_sus()
{
	harta[cap_x][cap_y] = 0;
	for (int i = scor; i > 0; i--)
		sarpe[i] = sarpe[i - 1];
	sarpe[0].x = cap_x;
	sarpe[0].y = cap_y;
	cap_x--;
	if (cap_x <= 0)
		cap_x = n - 2;
	harta[cap_x][cap_y] = 2;
}

void deplasare_jos()
{
	harta[cap_x][cap_y] = 0;
	for (int i = scor; i > 0; i--)
		sarpe[i] = sarpe[i - 1];
	sarpe[0].x = cap_x;
	sarpe[0].y = cap_y;
	cap_x++;
	if (cap_x >= n-1)
		cap_x = 1;
	harta[cap_x][cap_y] = 2;
}

void logica_joc()
{
	if (directie_inaintare == 0)
		deplasare_stanga();
	if (directie_inaintare == 1)
		deplasare_dreapta();
	if (directie_inaintare == 2)
		deplasare_jos();
	if (directie_inaintare == 3)
		deplasare_sus();
	for (int iscor = 0; iscor < scor; iscor++)
		if (sarpe[iscor].x == cap_x && sarpe[iscor].y == cap_y)
			sfarsitjoc = 0;
}

void logica_fruct()
{
	if (fruct_x == cap_x && fruct_y == cap_y)
	{
		scor++;
	
		int fruct_nou = rand() % (m * n);;
		fruct_x = fruct_nou / n;
		fruct_y = fruct_nou % n;
		if (fruct_x == 0)
			fruct_x++;
		if (fruct_x == n - 1)
			fruct_x--;
		if (fruct_y == 0)
			fruct_y++;
		if (fruct_y == m - 1)
			fruct_y--;
	}
}
void logica_tasta(char c)
{
	switch (c)
	{
	case 'A': 
		if (directie_inaintare != 1)
			directie_inaintare = 0;
		break;
	case 'D': 
		if(directie_inaintare != 0)
			directie_inaintare =1;
		break;
	case 'S': 
		if (directie_inaintare != 3)
			directie_inaintare = 2;
		break;
	case 'W': 
		if (directie_inaintare != 2)
			directie_inaintare = 3;
		break;
	case 'a':
		if (directie_inaintare != 1)
			directie_inaintare = 0;
		break;
	case 'd': 
		if (directie_inaintare != 0)
			directie_inaintare = 1;
		break;
	case 's':
		if (directie_inaintare != 3)
			directie_inaintare = 2;
		break;
	case 'w':
		if (directie_inaintare != 2)
			directie_inaintare = 3;
		break;
	}
}
int main()
{
	char c;

	initializare_joc();
	desenare_harta_careu_nivel();
	
	while (sfarsitjoc != 0)
	{
		system("cls");		//// curatam ecranul si 
		if (_kbhit())		//// verificam ce comanda am primit
		{
			c = _getch();
			logica_tasta(c);
		}

		logica_joc();
		logica_fruct();
		desenare_harta_careu_nivel();
	}
	cout << "\n  SFARSITUL JOCULUI";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
