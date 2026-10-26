#include "menu.hpp"

void menu::mostrarOpciones() {
    cout << "\n===== Menu de planificacion de procesos =====\n";
    cout << "1. Captura de procesos\n";
    cout << "2. FIFO\n";
    cout << "3. SJF\n";
    cout << "4. Prioridad\n";
    cout << "5. Round Robin\n";
    cout << "6. Salir\n";
}

int menu::leerOpcion() {
    int opcion;
    cout << "Selecciona una opcion: ";
    while (!(cin >> opcion) || opcion < 1 || opcion > 6) {
        cout << "Opcion invalida, selecciona un numero del 1 al 6: ";
        cin.clear();
        char caracter;
        while (cin.get(caracter) && caracter != '\n') {}
    }
    return opcion;
}

void menu::capturarProcesos() {
    int num;
    cout << "Cuantos procesos son? ";
    cin >> num;
    
    cola_procesos.limpiar(); 

    for (int i = 0; i < num; i++) {
        char id;
        int t, p;
        cout << "\nProceso " << (i + 1) << ":\n";
        cout << "ID: "; cin >> id;
        cout << "Tiempo: "; cin >> t;
        cout << "Prioridad: "; cin >> p;
        
        cola_procesos.enqueue(id, t, p);
    }
    cout << "Procesos capturados exitosamente.\n";
}

void menu::ejecutar() {
    int opcion;
    do {
        mostrarOpciones();
        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                capturarProcesos();
                break;
            case 2:
                if(cola_procesos.Empty()) cout << "\nNo hay procesos. ve a la opcion 1.\n";
                else obj_fifo.ejecutar(&cola_procesos);
                break;
            case 3:
                if(cola_procesos.Empty()) cout << "\nNo hay procesos, ve a la opcion 1.\n";
                else obj_sjf.ejecutar(&cola_procesos);
                break;
            case 4:
                if(cola_procesos.Empty()) cout << "\nNo hay procesos, ve a la opcion 1.\n";
                else obj_prioridad.ejecutar(&cola_procesos);
                break;
            case 5:
                if(cola_procesos.Empty()) cout << "\nNo hay procesos, ve a la opcion 1.\n";
                else obj_rr.ejecutar(&cola_procesos);
                break;
            case 6:
                cola_procesos.limpiar(); 
                cout << "\nFin del programa. Memoria liberada.\n";
                break;
        }
    } while (opcion != 6);
}