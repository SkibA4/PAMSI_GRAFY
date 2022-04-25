#include "dijkstra.h"

int Graf::minimum(Dijkstra* arr) {

	int min = -1;
	int minimalnyDystans = INT_MAX;

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		if (!arr[i].czyPowtorzony && arr[i].dlugoscSciezki < minimalnyDystans) {
			min = i;
			minimalnyDystans = arr[i].dlugoscSciezki;
		}
	}
	return min;
}

// ALGORYTM DIJKSTRY DLA MACIERZY SĄSIEDZTWA
Dijkstra* Graf::dijkstraMacierz() {

	Dijkstra* arr = new Dijkstra[liczbaWierzcholkow];
	droga = new int[liczbaWierzcholkow];

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		if (i == wierzcholekStartowy) {
			arr[i].dlugoscSciezki = 0;
		} else {
			arr[i].dlugoscSciezki = INT_MAX;
		}
		arr[i].czyPowtorzony= false;
		droga[i] = -1;
	}

	int min = minimum(arr);

	while (min != -1) {
		arr[min].czyPowtorzony = true;
		for (int i = 0; i < liczbaWierzcholkow; i++) {
			if (macierzSasiedztwa[min][i] > 0 && arr[min].dlugoscSciezki + macierzSasiedztwa[min][i] < arr[i].dlugoscSciezki) {
				arr[i].dlugoscSciezki = arr[min].dlugoscSciezki + macierzSasiedztwa[min][i];
				droga[i] = min;
			}
		}
		min = minimum(arr);
	}
	return arr;
}

// ALGORYTM DIJKSTRY DLA LISTY SĄSIEDZTWA
Dijkstra* Graf::dijkstraLista() {

	Dijkstra* arr = new Dijkstra[liczbaWierzcholkow];
	droga = new int[liczbaWierzcholkow];
    Element* temp;

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		if (i == wierzcholekStartowy) {
			arr[i].dlugoscSciezki = 0;
		} else {
			arr[i].dlugoscSciezki = INT_MAX;
		}
		arr[i].czyPowtorzony= false;
		droga[i] = -1;
	}

	int min = minimum(arr);

	while (min != -1) {
		arr[min].czyPowtorzony = true;
		temp = listaSasiedztwa[min];
		
		for (temp = listaSasiedztwa[min]; temp; temp = temp->Nastepny) {
			if (arr[min].dlugoscSciezki + temp->waga < arr[temp->wezel].dlugoscSciezki) {
				arr[temp->wezel].dlugoscSciezki = arr[min].dlugoscSciezki + temp->waga;
				droga[temp->wezel] = min;
			}			
		}
		min = minimum(arr);
	}
	return arr;
}