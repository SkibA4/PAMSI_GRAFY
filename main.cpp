#include "graf.h"
#include "dijkstra.h"
#include <chrono>

void menu() {
    cout << endl << "//////////////// PROJEKT 2 ///////////////////" << endl;
    cout << "1 - wygeneruj graf" << endl;
	cout << "2 - wczytaj graf" << endl;
	cout << "3 - wyświetl graf" << endl;
	cout << "4 - algorytm Dijkstra na macierzy sąsiedztwa" << endl;
	cout << "5 - algorytm Dijkstra na liście sąsiedztwa" << endl;
	cout << "0 - koniec działania programu" << endl;
	cout << "Twój wybór: ";
}

int main() {

    int wybor;
	bool flaga = true;
	Graf* graf;
	Dijkstra* arr;

	using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

	while (flaga) {
		menu();
		cin >> wybor;
		switch (wybor) {
			case 1: {
				generujGraf();
				break;
			}
			case 2: {
				wczytajGraf(graf);
				break;
			}
			case 3: {
				graf->wyswietlMacierz();
				graf->wyswietlListe();
				break;
			}
			case 4: {
				auto t1 = high_resolution_clock::now();
				for (int i = 0; i < 100; i++) {
					arr = graf->dijkstraMacierz();
				}
				auto t2 = high_resolution_clock::now();
				duration<double, std::milli> ms_double = t2 - t1;
				cout << endl << "Czas działania algorytmu: " << ms_double.count() << " ms." << endl;
				graf->zapisz(arr);
				break;
			}
			case 5: {
				auto t1 = high_resolution_clock::now();
				for (int i = 0; i < 100; i++) {
					arr = graf->dijkstraLista();
				}
				auto t2 = high_resolution_clock::now();
				duration<double, std::milli> ms_double = t2 - t1;
				cout << endl << "Czas działania algorytmu: " << ms_double.count() << " ms." << endl;
				graf->zapisz(arr);
				break;
			}
			case 0: {
				flaga = false;
				break;
			}
			default: {
				cout << "Błędny wybór. Spróbuj jeszcze raz" << endl;
				break;
			}
		}
	}
	return 0;
}