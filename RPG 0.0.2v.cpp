// RPG Terminal 0.0.1v. x64
// � Adam Machowski
// GitHub Dendrobatestinctorius
//


#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <windows.h>
#include <iostream>

using namespace std;


//Postac i jej warto�ci
class Postac {
public:
	bool aktywnaP = false;
	int str = 0, con = 0, dex = 0, wis = 0;
	string name;
	int weaponstr = 5;
	string equipmentweapon = "Pi��";
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
		cout << "\nWitaj " << name << ". Twoja si�a: " << str << ". Twoja zr�czno��: " << dex << ". Twoja wytrzyma�o��: " << con << ". Twoja m�dro��: " << wis << endl;
		cout << "Mo�esz rozpocz�� przygod�!" << endl;

	}
	void Postac_stat()
	{
		cout << "\nAktywna posta�:\nImi�: " << name << "\nStatystyki:\nSi�a: " << str << " Zr�czno��: " << dex << " Wytrzyma�o��: " << con << " M�dro��: " << wis << endl;
		cout << "Wyposa�enie:\nBro�: " << equipmentweapon << " +" << weaponstr << " Pancerz: " << equipmentarmor;
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
		armor = "Sk�rzany p�aszcz";
	}
	void Enemy_info()
	{
		cout << "\nNapotkane stworzenie:\n" << name << "\nStatystyki:\nSi�a: " << str << " Zr�czno��: " << dex << " Wytrzyma�o��: " << con << " M�dro��: " << wis << endl;
		cout << "Wyposa�enie:\nBro�: " << weapon << " +" << weapon_str << " Pancerz: " << armor << " +" << armor_con;
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

//wielko�� okna konsolo  !!Windows!!
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

// wywo�anie danych postaci
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
	cout << "Sterowanie jest proste, poprzez podanie cyfry odpowiadaj�cej wyborowi" << endl;
}

//Menu, g��wna p�tla programu
void menu()
{
	int menuchoice = 0;
	bool ctrl = true;
	do {
		Postac player;
		kolor_txt(15);
		cout << "\n===================================================" << endl;
		cout << "Stworz Posta�[1], Zacznij przygod� [2], Zako�cz Gre [9]";
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
					cout << "Najperw stw�rz posta�.";
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
			cout << "Niez�a pr�ba, ale to nie liczba, jeszcz raz\n:";
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
	cout << "nie ma takiego wyboru, spr�buj jeszcze raz";
	cin.clear();
	cin.ignore(1000, '\n');
	return false;
}

//Scena pocz�tkowa
bool Scena1(Postac& player)
{
	int scena1 = 0;
	bool ctrl = true;
	ClearScreen();
	if (player.weaponstr >= 6) {
		cout << "\nStoisz na polu. Za toba rozpo�ciera sie las" << endl;
		cout << "Id� w stron� lasu[2], Kontynuuj przez pole[4], Dane Postaci[8], Zako�cz przygod�[9]";
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
		cout << "\nStoisz na polu, przed tob� le�� grabie. Za toba rozpo�ciera sie las" << endl;
		cout << "Podnie� grabie[1], Id� w stron� lasu[2], Skocz na grabie[3], Kontynuuj przez pole[4], Dane Postaci[8], Zako�cz przygod�[9]";
		do {
			cout << "\n:";
			scena1 = inpt();
			switch (scena1) {
			case 1:
				if (player.str >= 10) {
					player.weaponstr = 14;
					player.equipmentweapon = "Grabie";
					cout << "\nMasz pot�n� bro�! Tylko co teraz?" << endl;
					cout << "Id� w stron� lasu[2], konntynuuj przez pole[4], Dane Postaci[8], Zako�cz przygod�[9]";
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
					cout << " zosta�o ci tylko:" << endl;
					cout << "Id� w stron� lasu[2], konntynuuj przez pole[4], Dane Postaci[8], Zako�cz przygod�[9]";
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
				cout << "\nmoje gratulacje, strzeli�es samob�ja...\nKoniec gry wracasz na start.\n\n\n";
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

//Scena wej�cie do lasu
bool las_wej(Postac& player)
{
	int scena2 = 0;
	bool ctrl = true;
	cout << "\nDotar�e� na skraj lasu. przed tob� pradawna knieja." << endl;
	cout << "Wejdz w g��b lasu[1], Zawr�� g�upcze[2], Dane Postaci[8], Zako�cz przygod�[9]";
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
	cout << "\nW�druj�c �cie�k� przez pole trafiasz na goblina. \nMa�a pod�a kreatura nie zwraca na ciebie uwagi, poniewa� zjada zw�oki kr�lika" << endl;
	cout << "Zaatakuj goblina[1], Przywitaj si�[2], Zawr�� p�ki jest zaj�ty[3],Sprawdz przeciwnika[7] Dane Postaci[8], Zako�cz przygod�[9]";
	do {
		cout << "\n:";
		scena3 = inpt();
		switch (scena3) {
		case 1:
			if ((player.str + player.weaponstr) >= (gobo.con + gobo.armor_con)) {
				cout << "\nZa pomoc� " << player.equipmentweapon << " jednym ciosem zabi�e� goblina!!.\nNie mia� przy sobie nic cennego wi�c ruszasz dalej.\n";
				ctrl = Scena5(player);
				break;
			}
			else {
				cout << "\nPoniewa� twoja si�a i bro� to tylko: " << player.weaponstr + player.str << ". nie zrobi�es na goblinie wra�enia. Z warkotem rzuci� si� na ciebie!\n";
				if (player.dex >= gobo.dex) {
					cout << "Jednak jeste� do�� szybki uda�o ci sie unikn�� stworzenia i biegniesz co si� w nogach dalej.\n";
					ctrl = Scena5(player);
					break;
				}
				kolor_txt(12);
				cout << "Ciosem pazur�w rozerwa� ci udo, nie masz szans na przetrwanie\n\n";
				break;
			}
		case 2:
			cout << "\nGoblin rzuci� si� na ciebie z warkotem zanim wyci�gn��e� bro�!";
			if (player.con >= gobo.str) {
				cout << "\nuda�o ci si� odepchn�� stworzenie!";
				if (player.str >= gobo.con) {
					cout << "\nPowali�e� go i udusi�e�. Jednak nie mia� przy sobie nic cennego\n";
					ctrl = Scena5(player);
					break;
				}
				cout << "\nJednak nie masz do�� si�y �eby go pokona�";
				kolor_txt(12);
				cout << "\nCiosem pazur�w rozerwa� ci udo, nie masz szans na przetrwanie\n\n";
				break;

			}
			else if (player.dex >= gobo.dex) {
				cout << "\nJednak jeste� do�� szybki uda�o ci sie unikn�� stworzenia i biegniesz co si� w nogach dalej.\n";
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

//Scena wn�trze lasu
bool Scena4(Postac& player)
{
	int scena4 = 0;
	bool ctrl = true;
	cout << "\nciemny jak dupa las. P�ki co to koniec.\nWprowadz dowoln� liczbe �eby wr�cic do menu\n:";
	do {
		scena4 = inpt();
	} while (ctrl == false);
	return ctrl;
}

// Scena nad rzek�
bool Scena5(Postac& player)
{
	int scena5 = 0;
	bool ctrl = true;
	cout << "\nDotar�e� nad rzek�. P�ki co to koniec.\nWprowadz dowoln� liczbe �eby wr�cic do menu\n:";
	do {
		scena5 = inpt();
	} while (ctrl == false);
	return ctrl;
}