#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

int PrzesunieciePoziome = 0;
int PrzesunieciePionowe = 0;
int ZmianaRozmiaru = 0;
int MinimalnaPozycjaZnaku = -1;


void RysowanieFigury(int szerokosc, double wysokoscPodana, char znak, int PrzesunieciePoziome, int ZmianaRozmiaru) {
	
	int pozycjaZnaku = (szerokosc) + PrzesunieciePoziome;
	double RozmiarFigury = wysokoscPodana + ZmianaRozmiaru;

	for (int j = 1; j <= RozmiarFigury; j++) {

		// petla wiersza jednego
		bool obecnoscZnaku = false;

		for (int i = 1; i <= szerokosc; i++) {
			if (i == pozycjaZnaku && obecnoscZnaku == false) {   // sprawdzam czy robic znak

				if (j < RozmiarFigury / 2) {
					cout << znak;
					obecnoscZnaku = true;
					pozycjaZnaku--;
					::MinimalnaPozycjaZnaku = pozycjaZnaku;
				}
				else if (j == RozmiarFigury / 2 && (int)RozmiarFigury % 2 == 0) {
					cout << znak;
					obecnoscZnaku = true;
				}
				else { // II po³owa
					cout << znak;
					obecnoscZnaku = true;
					pozycjaZnaku++;
				}
			}
			else {
				cout << " "; // dev
			}
		}

		cout << endl;
		//koniec petli jednego
	}
}

void PrzesuwanieFigury(int szerokosc,int wysokosc, double wysokoscPodana, char znak) {

	int wybor = _getch();
	int PozycjaPoPrzesunieciu = wysokoscPodana + ZmianaRozmiaru + PrzesunieciePionowe;

	system("cls");

	switch (wybor) {

	case 75: //lewo
		if (MinimalnaPozycjaZnaku > 1) {
			::PrzesunieciePoziome--;
		}
		RysowanieFigury(szerokosc, wysokoscPodana, znak, ::PrzesunieciePoziome, ::ZmianaRozmiaru);
		break;

	case 77: // prawo
		if (PrzesunieciePoziome < 0) {
			::PrzesunieciePoziome++;
		}
		RysowanieFigury(szerokosc, wysokoscPodana, znak, ::PrzesunieciePoziome, ::ZmianaRozmiaru);
		break;

	case 72: // góra
		if (PrzesunieciePionowe > 0) {
			::PrzesunieciePionowe--;
		}
		for (int i = 1; i <= PrzesunieciePionowe; i++) {
			cout << endl;
		}
		RysowanieFigury(szerokosc, wysokoscPodana, znak, ::PrzesunieciePoziome, ::ZmianaRozmiaru);
		break;

	case 80: // dó³
		if (PozycjaPoPrzesunieciu < wysokosc) {
			::PrzesunieciePionowe++;
		}
		for (int i = 1; i <= PrzesunieciePionowe; i++) {
			cout << endl;
		}
		RysowanieFigury(szerokosc, wysokoscPodana, znak, ::PrzesunieciePoziome, ::ZmianaRozmiaru);
		break;

	case 43: // powiekszenie
		if (MinimalnaPozycjaZnaku > 1 && PozycjaPoPrzesunieciu < wysokosc) {
			::ZmianaRozmiaru++;
		}
		RysowanieFigury(szerokosc, wysokoscPodana, znak, ::PrzesunieciePoziome, ::ZmianaRozmiaru);
		break;

	case 45: // zmniejszenie
		if (wysokoscPodana + ZmianaRozmiaru > 0) {
			::ZmianaRozmiaru--;
		}
		RysowanieFigury(szerokosc, wysokoscPodana, znak, ::PrzesunieciePoziome, ::ZmianaRozmiaru);
		break;

	case 27:
		exit(0);
	}
}

int main(int argc, char *argv[])
{

//wielkosc okna

	CONSOLE_SCREEN_BUFFER_INFO csbi; 
	int szerokosc;
	int wysokosc;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	szerokosc = csbi.srWindow.Right - csbi.srWindow.Left;
	wysokosc = csbi.srWindow.Bottom - csbi.srWindow.Top;

//koniec liczenia wielkosci okna


//wczytywanie znaku ASCII

	int kodASCII=128;
	
	while (kodASCII < 0 || kodASCII>127) {
		cout << "Podaj kod znaku ASCII: ";
		cin >> kodASCII;
	}

	char znak = char(kodASCII);


//wczytanie rozmiaru figury

	double wysokoscPodana;

	do {
		cout << "Podaj wysokosc figury (mniej niz " << wysokosc << " )" << endl;
		cin >> wysokoscPodana;

	} while (wysokoscPodana > wysokosc);


//Pierwsze rysowanie oraz pêtla przesuniecia figury

	system("cls");

	RysowanieFigury(szerokosc, wysokoscPodana, znak, PrzesunieciePoziome, ZmianaRozmiaru);

	while (true) {
		PrzesuwanieFigury(szerokosc, wysokosc, wysokoscPodana, znak);
	}

	_getch();
	return 0;
}