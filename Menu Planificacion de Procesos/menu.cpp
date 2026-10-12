#include "menu.hpp"

void menu::mostrarOpciones(){
		cout << "\n===== Menu de planificacion de procesos =====\n";
		cout << "1. Captura de procesos\n";
		cout << "2. FIFO\n";
		cout << "3. SJF\n";
		cout << "4. Round Robin\n";
		cout << "5. Prioridad\n";
		cout << "6. Salir\n";
	}

    int menu::leerOpcion() {
		
		int opcion;

		cout << "Seleccione una opcion: ";

		while (!(cin >> opcion) || opcion < 1 || opcion > 6) {

			cout << "Opcion invalida. Seleccione un numero del 1 al 6: ";

			cin.clear();

			char caracter;

			while (cin.get(caracter) && caracter != '\n') {

			}

		}

		return opcion;

	}

    		


void menu::ejecutar() {
	
    int opcion;

    do {

		mostrarOpciones();
			opcion = leerOpcion();


		switch (opcion) {

				case 1:

					cout << "Opcion de captura de procesos seleccionada.\n";

					break;

				case 2:

					cout << "Opcion FIFO seleccionada.\n";

					break;

				case 3:

					cout << "Opcion SJF seleccionada.\n";

					break;

				case 4:

					cout << "Opcion Round Robin seleccionada.\n";

					break;

				case 5:

					cout << "Opcion Prioridad seleccionada.\n";

					break;

				case 6:

					cout << "Saliendo...\n";

					break;

			}

		} while (opcion != 6);

	}



