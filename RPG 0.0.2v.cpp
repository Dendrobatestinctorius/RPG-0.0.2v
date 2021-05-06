// RPG Terminal 0.0.1v. x64
// © Adam Machowski
// GitHub Dendrobatestinctorius
//


#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <windows.h>
#include <iostream>

using namespace std;


//Postac i jej wartoœci
class Postac {
public:
	bool aktywnaP = false;
	int str = 0, con = 0, dex = 0, wis = 0;
	string name;
	int weaponstr = 5;
	string equipmentweapon = "Piêœæ";
	string equipmentarmor = "Nic";
	int randattr()
	{
		int attr = (rand() % 12) + 8;
		return attr;
	}
	void charcr()
	{
		aktywnaP = true;
		str = randattr();
		dex = randattr();
		con = randattr();
		wis = randattr();
		cout << "\nPodaj imie postaci: ";
		cin >> name;
		cout << "\nWitaj " << name << ". Twoja si³a: " << str << ". Twoja zrêcznoœæ: " << dex << ". Twoja wytrzyma³oœæ: " << con << ". Twoja m¹droœæ: " << wis << endl;
		cout << "Mo¿esz rozpocz¹æ przygodê!" << endl;

	}
	void Postac_stat()
	{
		cout << "\nAktywna postaæ:\nImiê: " << name << "\nStatystyki:\nSi³a: " << str << " Zrêcznoœæ: " << dex << " Wytrzyma³oœæ: " << con << " M¹droœæ: " << wis << endl;
		cout << "Wyposa¿enie:\nBroñ: " << equipmentweapon << " +" << weaponstr << " Pancerz: " << equipmentarmor;
	}
};

class Enemy {
public:
	int str =0 , dex = 0, con = 0 , wis = 0;
	string name, weapon, armor;
	int weapon_str = 0, armor_con = 0;
	void Goblin()
	{
		str = 8;
		dex = 12;
		con = 11;
		wis = 6;
		name = "Goblin";
		weapon_str = 10;
		armor_con = 5;
		weapon = "Maczuga";
		armor = "Skórzany p³aszcz";
	}
	void Enemy_info()
	{
		cout << "\nNapotkane stworzenie:\n" << name << "\nStatystyki:\nSi³a: " << str << " Zrêcznoœæ: " << dex << " Wytrzyma³oœæ: " << con << " M¹droœæ: " << wis << endl;
		cout << "Wyposa¿enie:\nBroñ: " << weapon << " +" << weapon_str << " Pancerz: " << armor << " +" << armor_con;
	}
};

//deklaracje funkcji
void okno_rozmiar();
void kolor_txt(int color);
void ClearScreen();
bool Dane_postaci(Postac& player);
void Title();
void menu();
int inpt();
bool zla_opcja();
bool Scena1(Postac& player);
bool las_wej(Postac& player);
bool Scena3(Postac& player);
bool Scena4(Postac& player);
bool Scena5(Postac& player);




int main()
{
	okno_rozmiar();
	setlocale(LC_ALL, "pl_PL");
	srand(time(NULL));
	Title();
	menu();
	return 0;
}

//Definicje funkcji

//wielkoœæ okna konsolo  !!Windows!!
void okno_rozmiar()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 1280, 720, TRUE);
}

//ustawienie koloru tekstu !!Windows!!
void kolor_txt(int color)
{
	HANDLE  Console;
	Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, color);
}

//Czyszczenie ekranu !!Windows!!
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) 
		return;

	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) 
		return;

	SetConsoleCursorPosition(hStdOut, homeCoords);
}

// wywo³anie danych postaci
bool Dane_postaci(Postac& player)
{
	kolor_txt(9);
	player.Postac_stat();
	kolor_txt(15);
	return false;
}

//Powitanie
void Title()
{
	kolor_txt(2);
	cout << "Witaj w moim perwszym RPG tekstowym" << endl;
	cout << "wersja 0.0.1 Terminal!" << endl;
	cout << "TM DendrobatesTinctorius Studio\n" << endl;
	kolor_txt(15);
	cout << "Sterowanie jest proste, poprzez podanie cyfry odpowiadaj¹cej wyborowi" << endl;
}

//Menu, g³ówna pêtla programu
void menu()
{
	int menuchoice = 0;
	bool ctrl = true;
	do {
		Postac player;
		kolor_txt(15);
		cout << "\n===================================================" << endl;
		cout << "Stworz Postaæ[1], Zacznij przygodê [2], Zakoñcz Gre [9]";
		do {
			cout << "\n:";
			menuchoice = inpt();
			switch (menuchoice) {
			case 1:
				player.charcr();
				ctrl = false;
				break;
			case 2:
				if (player.aktywnaP == true) {
					ctrl = Scena1(player);
					break;
				}
				else {
					cout << "Najperw stwórz postaæ.";
					ctrl = false;
					break;
				}
			case 9:
				ctrl = true;
				break;
			default:
				ctrl = zla_opcja();
			}
		} while (ctrl == false);
	} while (menuchoice != 9);
}

//Wprowadzanie opcji
int inpt()
{
	int opcja;
	cin >> opcja;
	if (cin.fail()) {
		do {
			cout << "Niez³a próba, ale to nie liczba, jeszcz raz\n:";
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> opcja;
		} while (cin.fail());
	}

	return opcja;
}

//Opcja poza zakresem
bool zla_opcja()
{
	cout << "nie ma takiego wyboru, spróbuj jeszcze raz";
	cin.clear();
	cin.ignore(1000, '\n');
	return false;
}

//Scena pocz¹tkowa
bool Scena1(Postac& player)
{
	int scena1 = 0;
	bool ctrl = true;
	ClearScreen();
	if (player.weaponstr >= 6) {
		cout << "\nStoisz na polu. Za toba rozpoœciera sie las" << endl;
		cout << "Id¿ w stronê lasu[2], Kontynuuj przez pole[4], Dane Postaci[8], Zakoñcz przygodê[9]";
		do {
			cout << "\n:";
			scena1 = inpt();
			switch (scena1) {
			case 2:
				ctrl = las_wej(player);
				break;
			case 4:
				ctrl = Scena3(player);
				break;
			case 8:
				ctrl = Dane_postaci(player);
				break;
			case 9:
				return true;
			default:
				ctrl = zla_opcja();
			}
		} while (ctrl == false);
		return ctrl;
	}
	else {
		cout << "\nStoisz na polu, przed tob¹ le¿¹ grabie. Za toba rozpoœciera sie las" << endl;
		cout << "Podnieœ grabie[1], Id¿ w stronê lasu[2], Skocz na grabie[3], Kontynuuj przez pole[4], Dane Postaci[8], Zakoñcz przygodê[9]";
		do {
			cout << "\n:";
			scena1 = inpt();
			switch (scena1) {
			case 1:
				if (player.str >= 10) {
					player.weaponstr = 14;
					player.equipmentweapon = "Grabie";
					cout << "\nMasz potê¿n¹ broñ! Tylko co teraz?" << endl;
					cout << "IdŸ w stronê lasu[2], konntynuuj przez pole[4], Dane Postaci[8], Zakoñcz przygodê[9]";
					do {
						cout << "\n:";
						scena1 = inpt();
						switch (scena1) {
						case 2:
							ctrl = las_wej(player);
							break;
						case 4:
							ctrl = Scena3(player);
							break;
						case 8:
							ctrl = Dane_postaci(player);
							break;
						case 9:
							return true;
						default:
							ctrl = zla_opcja();
						}
					} while (ctrl == false);
					return ctrl;
				}
				else {
					kolor_txt(4);
					cout << "\nJestes zbyt cherlawy!";
					kolor_txt(15);
					cout << " zosta³o ci tylko:" << endl;
					cout << "IdŸ w stronê lasu[2], konntynuuj przez pole[4], Dane Postaci[8], Zakoñcz przygodê[9]";
					do {
						cout << "\n:";
						scena1 = inpt();
						switch (scena1) {
						case 2:
							ctrl = las_wej(player);
							break;
						case 4:
							ctrl = Scena3(player);
							break;
						case 8:
							ctrl = Dane_postaci(player);
							break;
						case 9:
							return true;
						default:
							ctrl = zla_opcja();
						}
					} while (ctrl == false);
					return ctrl;
				}
			case 2:
				ctrl = las_wej(player);
				break;
			case 3:
				kolor_txt(4);
				cout << "\nmoje gratulacje, strzeli³es samobója...\nKoniec gry wracasz na start.\n\n\n";
				break;
			case 4:
				ctrl = Scena3(player);
				break;
			case 8:
				ctrl = Dane_postaci(player);
				break;
			case 9:
				ctrl = true;
				break;
			default:
				ctrl = zla_opcja();
			}
		} while (ctrl == false);
	}
	return ctrl;
}

//Scena wejœcie do lasu
bool las_wej(Postac& player)
{
	int scena2 = 0;
	bool ctrl = true;
	cout << "\nDotar³eœ na skraj lasu. przed tob¹ pradawna knieja." << endl;
	cout << "Wejdz w g³¹b lasu[1], Zawróæ g³upcze[2], Dane Postaci[8], Zakoñcz przygodê[9]";
	do {
		cout << "\n:";
		scena2 = inpt();
		switch (scena2) {
		case 1:
			ctrl = Scena4(player);
			break;
		case 2:
			ctrl = Scena1(player);
			break;
		case 8:
			ctrl = Dane_postaci(player);
			break;
		case 9:
			ctrl = true;
			return true;
		default:
			ctrl = zla_opcja();
		}
	} while (ctrl == false);
	return ctrl;
}

//Scena droga przez pole
bool Scena3(Postac& player)
{
	Enemy gobo;
	gobo.Goblin();
	int scena3 = 0;
	bool ctrl = true;
	cout << "\nWêdruj¹c œcie¿k¹ przez pole trafiasz na goblina. \nMa³a pod³a kreatura nie zwraca na ciebie uwagi, poniewa¿ zjada zw³oki królika" << endl;
	cout << "Zaatakuj goblina[1], Przywitaj siê[2], Zawróæ póki jest zajêty[3],Sprawdz przeciwnika[7] Dane Postaci[8], Zakoñcz przygodê[9]";
	do {
		cout << "\n:";
		scena3 = inpt();
		switch (scena3) {
		case 1:
			if ((player.str + player.weaponstr) >= (gobo.con + gobo.armor_con)) {
				cout << "\nZa pomoc¹ " << player.equipmentweapon << " jednym ciosem zabi³eœ goblina!!.\nNie mia³ przy sobie nic cennego wiêc ruszasz dalej.\n";
				ctrl = Scena5(player);
				break;
			}
			else {
				cout << "\nPoniewa¿ twoja si³a i broñ to tylko: " << player.weaponstr + player.str << ". nie zrobi³es na goblinie wra¿enia. Z warkotem rzuci³ siê na ciebie!\n";
				if (player.dex >= gobo.dex) {
					cout << "Jednak jesteœ doœæ szybki uda³o ci sie unikn¹æ stworzenia i biegniesz co si³ w nogach dalej.\n";
					ctrl = Scena5(player);
					break;
				}
				kolor_txt(12);
				cout << "Ciosem pazurów rozerwa³ ci udo, nie masz szans na przetrwanie\n\n";
				break;
			}
		case 2:
			cout << "\nGoblin rzuci³ siê na ciebie z warkotem zanim wyci¹gn¹³eœ broñ!";
			if (player.con >= gobo.str) {
				cout << "\nuda³o ci siê odepchn¹æ stworzenie!";
				if (player.str >= gobo.con) {
					cout << "\nPowali³eœ go i udusi³eœ. Jednak nie mia³ przy sobie nic cennego\n";
					ctrl = Scena5(player);
					break;
				}
				cout << "\nJednak nie masz doœæ si³y ¿eby go pokonaæ";
				kolor_txt(12);
				cout << "\nCiosem pazurów rozerwa³ ci udo, nie masz szans na przetrwanie\n\n";
				break;

			}
			else if (player.dex >= gobo.dex) {
				cout << "\nJednak jesteœ doœæ szybki uda³o ci sie unikn¹æ stworzenia i biegniesz co si³ w nogach dalej.\n";
				ctrl = Scena5(player);
				break;
			}
		case 3:
			ctrl = Scena1(player);
			break;
		case 7:
			kolor_txt(4);
			gobo.Enemy_info();
			kolor_txt(15);
			ctrl = false;
			break;
		case 8:
			ctrl = Dane_postaci(player);
			break;
		case 9:
			ctrl = true;
			return true;
		default:
			ctrl = zla_opcja();
		}
	} while (ctrl == false);
	return ctrl;
}

//Scena wnêtrze lasu
bool Scena4(Postac& player)
{
	int scena4 = 0;
	bool ctrl = true;
	cout << "\nciemny jak dupa las. Póki co to koniec.\nWprowadz dowoln¹ liczbe ¿eby wrócic do menu\n:";
	do {
		scena4 = inpt();
	} while (ctrl == false);
	return ctrl;
}

// Scena nad rzek¹
bool Scena5(Postac& player)
{
	int scena5 = 0;
	bool ctrl = true;
	cout << "\nDotar³eœ nad rzekê. Póki co to koniec.\nWprowadz dowoln¹ liczbe ¿eby wrócic do menu\n:";
	do {
		scena5 = inpt();
	} while (ctrl == false);
	return ctrl;
}