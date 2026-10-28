#include "PlanNoExpro.hpp"

void NoExpropiativo::mostrarEstadoCola(dqueue* cola) {
    dqueue::node* aux = cola->getStart();
    bool hay = false;
    while (aux != nullptr) {
        if (aux->tiempo_restante > 0) {
            cout << "[" << aux->ID << "]";
            hay = true;
        }
        aux = aux->nxt;
    }
    if (!hay) cout << "[Vacia]";
}

void NoExpropiativo::mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios) {  // Muestra los resultados de la planificación de procesos
    float suma_tr = 0;
    int n = cola_simulada->size(); 

    cout << "\n--- Resultados de la Planificacion ---" << endl; // Muestra los resultados de la planificación de procesos

    dqueue::node* aux = cola_simulada->getStart();
    
    while (aux != nullptr) { 
        
        cout << "ID: " << aux->ID << " | Tiempo: " << aux->tiempo << " | Prioridad: " << aux->prioridad << " | Tiempo de Retorno: " << aux->tiempo_retorno << endl;
             
        suma_tr += aux->tiempo_retorno;
        aux = aux->nxt;
    }
    
    cout << "-------------------------------------------------------" << endl;
    
    cout << "Tiempo de Retorno Promedio: " << fixed << setprecision(2) << (suma_tr / n) << endl; // Muestra el tiempo de retorno promedio

    cout << "\nSimulacion:" << endl;
    cout << tiempos[0];
    for (int i = 0; i < num_cambios; ++i) {
        cout << " [" << orden[i] << "] " << tiempos[i+1];
    }
    cout << "\n\n";

}

void FIFO::ejecutar(dqueue* cola_original) { 
    dqueue* copia = cola_original->clonar();
    int n = copia->size();
    
    char* orden = new char[n]; 
    int* tiempos = new int[n + 1];
    int tiempo_actual = 0;
    tiempos[0] = 0;
    int idx = 0;

    cout << "\n=== Simulacion FIFO ===\n";
    cout << "Evolucion de la cola:\n";
    mostrarEstadoCola(copia); 

    dqueue::node* aux = copia->getStart();
    while (aux != nullptr) {
        orden[idx] = aux->ID;
        tiempo_actual += aux->tiempo;
        aux->tiempo_restante = 0; 
        aux->tiempo_retorno = tiempo_actual;
        tiempos[idx + 1] = tiempo_actual;
        idx++;
        
        cout << " -> ";
        mostrarEstadoCola(copia); 

        aux = aux->nxt;
    }
    cout << "\n";

    mostrarResultados(copia, orden, tiempos, n);
    delete[] orden; delete[] tiempos; delete copia;
}

void SJF::ejecutar(dqueue* cola_original) { 
    dqueue* copia = cola_original->clonar();
    copia->ordenarPorTiempo(); 

    int n = copia->size();
    char* orden = new char[n]; 
    int* tiempos = new int[n + 1];
    int tiempo_actual = 0;
    tiempos[0] = 0;
    int idx = 0;

    cout << "\n=== Simulacion SJF ===\n";
    cout << "Evolucion de la cola:\n";
    mostrarEstadoCola(copia);

    dqueue::node* aux = copia->getStart();
    while (aux != nullptr) {
        orden[idx] = aux->ID;
        tiempo_actual += aux->tiempo;
        aux->tiempo_restante = 0; 
        aux->tiempo_retorno = tiempo_actual;
        tiempos[idx + 1] = tiempo_actual;
        idx++;
        
        cout << " -> ";
        mostrarEstadoCola(copia);
        
        aux = aux->nxt;
    }
    cout << "\n";

    mostrarResultados(copia, orden, tiempos, n);
    delete[] orden; delete[] tiempos; delete copia;
}