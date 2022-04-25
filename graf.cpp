#include "graf.h"

// KONSTRUKTOR GRAFU
Graf::Graf(int liczbaWierzcholkow, int liczbaKrawedzi, int wierzcholekStartowy) {

    // Przypisanie obiektowi wartości
    this->liczbaWierzcholkow = liczbaWierzcholkow;
    this->liczbaKrawedzi = liczbaKrawedzi;
    this->wierzcholekStartowy = wierzcholekStartowy;

    // Zainicjowanie tablicy dwuwymiarowej reprezentującej macierz sąsiedztwa i wypełnienie jej zerami 
    macierzSasiedztwa = new int*[liczbaWierzcholkow];

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		macierzSasiedztwa[i] = new int[liczbaWierzcholkow];
    }
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++)
			macierzSasiedztwa[i][j] = 0;
    }

    // Zainicjowanie tablicy jednowymiarowej reprezentującej listę sąsiedztwa
    listaSasiedztwa = new Element*[liczbaWierzcholkow];

    for (int i = 0; i < liczbaWierzcholkow; i++) {
        listaSasiedztwa[i] = NULL;
    }
}

// DODAWANIE KRAWĘDZI GRAFU
void Graf::dodajKrawedz(int poczatek, int koniec, int waga) {

    // Utworzenie nowego elementu i wypełnienie go wartościami
    element = new Element;
    element->wezel = koniec;
    element->waga = waga;
    element->Nastepny = listaSasiedztwa[poczatek];

    // Przypisanie wartości do listy i macierzy sąsiedztwa
    listaSasiedztwa[poczatek] = element;
    macierzSasiedztwa[poczatek][koniec] = waga;
}

// GENEROWANIE GRAFU
void generujGraf() {

    int liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, waga, count = 0;
    float gestoscGrafu;
    string nazwaPliku;
    ofstream plik;

    cout << "Podaj nazwę pliku: ";
    cin >> nazwaPliku;

    // Utworzenie pliku, w którym będą znajdywały się dane grafu
    plik.open(nazwaPliku.c_str());
    cout << "Podaj kolejno ilość wierzchołków, gęstość z przedziału (0; 1), wierzchołek startowy: ";
    cin >> liczbaWierzcholkow >> gestoscGrafu >> wierzcholekStartowy;

    // Określenie liczby krawędzi na podstawie podanej gęstości
    liczbaKrawedzi = ((liczbaWierzcholkow * (liczbaWierzcholkow - 1)) / 2) * gestoscGrafu;

    // Wpisanie do pliku danych grafu
    plik << liczbaKrawedzi << " " << liczbaWierzcholkow << " " << wierzcholekStartowy << endl;

    for (int i = 0; i < liczbaWierzcholkow; i++) {
        for (int j = i; j < liczbaWierzcholkow; j++) {
            if (i != j && count < liczbaKrawedzi) {
					waga = rand() % 50 + 1; // Przydzielenie losowej wagi przejścia z przedziału [1; 50]
					plik << i << " " << j << " " << waga << endl;
					plik << j << " " << i << " " << waga << endl;
					count++;
				}
        }
    }
    plik.close(); 
}

// WCZYTYWANIE DANYCH GRAFU Z PLIKU
void wczytajGraf (Graf*& graf) {

    int liczbaKrawedzi, liczbaWierzcholkow, wierzcholekStartowy, wierzcholekPoczatkowy, wierzcholekKoncowy, waga;
    string nazwaPliku;
    ifstream plik;

    cout << "Podaj nazwę pliku: ";
    cin >> nazwaPliku;

    // Otworzenie pliku z grafem i uzupełnienie pól klasy Graf danymi po pomyślnym otwarciu
    plik.open(nazwaPliku.c_str());
    if (plik.good()) {       
        plik >> liczbaKrawedzi; plik >> liczbaWierzcholkow; plik >> wierzcholekStartowy;
        graf = new Graf(liczbaWierzcholkow, liczbaKrawedzi, wierzcholekStartowy);

        while (!plik.eof()) {
            plik >> wierzcholekPoczatkowy; plik >> wierzcholekKoncowy; plik >> waga;
			graf->dodajKrawedz(wierzcholekPoczatkowy, wierzcholekKoncowy, waga);
        }

        cout << endl << "Pomyślnie wczytano graf" << endl;
    } else {
        cout << "Błędna nazwa pliku. Spróbuj jeszcze raz." << endl;
    }
    plik.close();
}

// WYSWIETLANIE MACIERZY SASIEDZTWA
void Graf::wyswietlMacierz() {

    cout << endl << "///////////// MACIERZ SĄSIEDZTWA /////////////" << endl;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			cout << macierzSasiedztwa[i][j] << "\t";
		}
		cout << endl;
	}
}

// WYSWIELTANIE LISTY SĄSIEDZTEWA 
void Graf::wyswietlListe() {

    // Utworzenie elemntu tymczasowego do którego będą zapisywane dane z kolejnych pól list sąsiedztwa
    Element* temp;
    cout << endl << "////////////// LISTA SĄSIEDZTWA //////////////" << endl;

    for (int i = 0; i < liczbaWierzcholkow; i++) {
        temp = listaSasiedztwa[i];
        cout << i << " ->";
		while (temp) {
			cout << " | " << temp->wezel << ", waga :" << temp->waga ;
			temp = temp->Nastepny;
		}
		cout << endl;
    }
}

// ZAPISYWANIE GRAFU DO PLIKU
void Graf::zapisz(Dijkstra* tab) {

	int licznik = 0;
	int* Tab_drogi = new int[liczbaWierzcholkow];       
	ofstream plik;

	plik.open("Graf.txt");
    plik << "Wierzchołek startowy: " << wierzcholekStartowy << endl;

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		plik << "Droga do wierzchołka " << i << ":" ;
		for (int j = i; j > -1; j = droga[j]) {
			Tab_drogi[licznik++] = j;
        }
		while (licznik) {
            plik << " | " << Tab_drogi[--licznik];
        }
        plik << " | koszt przejścia: "<< tab[i].dlugoscSciezki << endl;
	}
	plik.close();
}