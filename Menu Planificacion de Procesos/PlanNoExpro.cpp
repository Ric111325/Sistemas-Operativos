#include "PlanNoExpro.hpp"

// Método para mostrar el estado actual de la cola de procesos (solo los que tienen tiempo pendiente)
void NoExpropiativo::mostrarEstadoCola(dqueue* cola) {
    dqueue::node* aux = cola->getStart();
    bool hay = false;
    while (aux != nullptr) {
        // Imprime el ID del proceso si aún tiene tiempo restante de ejecución
        if (aux->tiempo_restante > 0) {
            cout << "[" << aux->ID << "]";
            hay = true;
        }
        aux = aux->nxt;
    }
    // Si ningún proceso tiene tiempo pendiente, indica que la cola está vacía
    if (!hay) cout << "[Vacia]";
}

// Método para mostrar la tabla final de resultados, estadísticas y diagrama de Gantt simplificado
void NoExpropiativo::mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios) {  // Muestra los resultados de la planificación de procesos
    float suma_tr = 0;
    int n = cola_simulada->size(); 

    cout << "\n--- Resultados de la Planificacion ---" << endl; // Muestra los resultados de la planificación de procesos

    dqueue::node* aux = cola_simulada->getStart();

    // Recorre la cola para imprimir las métricas finales de cada proceso
    while (aux != nullptr) { 
        
        cout << "ID: " << aux->ID << " | Tiempo: " << aux->tiempo << " | Prioridad: " << aux->prioridad << " | Tiempo de Retorno: " << aux->tiempo_retorno << endl;
             
        suma_tr += aux->tiempo_retorno; // Acumula el tiempo de retorno para el promedio
        aux = aux->nxt;
    }
    
    cout << "-------------------------------------------------------" << endl;
    
    cout << "Tiempo de Retorno Promedio: " << fixed << setprecision(2) << (suma_tr / n) << endl; // Muestra el tiempo de retorno promedio

    // Imprime la línea de tiempo (Diagrama de Gantt simplificado)
    cout << "\nSimulacion:" << endl;
    cout << tiempos[0];
    for (int i = 0; i < num_cambios; ++i) {
        cout << " [" << orden[i] << "] " << tiempos[i+1];
    }
    cout << "\n\n";

}

// Implementación del algoritmo FIFO
void FIFO::ejecutar(dqueue* cola_original) { 
    dqueue* copia = cola_original->clonar();
    int n = copia->size();
    
    char* orden = new char[n]; // Almacena el orden de ejecución de los procesos
    int* tiempos = new int[n + 1]; // Almacena los puntos temporales del diagrama de tiempos
    int tiempo_actual = 0;
    tiempos[0] = 0;
    int idx = 0;

    cout << "\n=== Simulacion FIFO ===\n";
    cout << "Evolucion de la cola:\n";
    mostrarEstadoCola(copia); 

    dqueue::node* aux = copia->getStart();
    // Ejecuta los procesos en el orden estricto en el que llegaron
    while (aux != nullptr) {
        orden[idx] = aux->ID;
        tiempo_actual += aux->tiempo; // Al ser no expropiativo, el proceso se ejecuta por completo
        aux->tiempo_restante = 0; // Se marca como finalizado
        aux->tiempo_retorno = tiempo_actual; // Registra su tiempo de retorno
        tiempos[idx + 1] = tiempo_actual;
        idx++;
        
        cout << " -> ";
        mostrarEstadoCola(copia); // Actualiza visualmente la cola

        aux = aux->nxt;
    }
    cout << "\n";

    mostrarResultados(copia, orden, tiempos, n); // Muestra los resultados finales
    delete[] orden; delete[] tiempos; delete copia; // Libera la memoria dinámica reservada
}

// Implementación del algoritmo SJF (Shortest Job First)
void SJF::ejecutar(dqueue* cola_original) { 
    dqueue* copia = cola_original->clonar(); // Clona la cola original
    copia->ordenarPorTiempo(); // Ordena los procesos de menor a mayor duración

    int n = copia->size();
    char* orden = new char[n]; // Arreglo para guardar el orden de ejecución
    int* tiempos = new int[n + 1]; // Arreglo para los tiempos de la simulación
    int tiempo_actual = 0;
    tiempos[0] = 0;
    int idx = 0;

    cout << "\n=== Simulacion SJF ===\n";
    cout << "Evolucion de la cola:\n";
    mostrarEstadoCola(copia);

    dqueue::node* aux = copia->getStart();
    // Ejecuta los procesos ya ordenados por duración (el más corto primero)
    while (aux != nullptr) {
        orden[idx] = aux->ID;
        tiempo_actual += aux->tiempo; // Acumula el tiempo total de ejecución del proceso
        aux->tiempo_restante = 0; // Marca el proceso como completado
        aux->tiempo_retorno = tiempo_actual; // Registra el tiempo de retorno
        tiempos[idx + 1] = tiempo_actual;
        idx++;
        
        cout << " -> ";
        mostrarEstadoCola(copia);
        
        aux = aux->nxt;
    }
    cout << "\n";

    mostrarResultados(copia, orden, tiempos, n); // Muestra los resultados y estadísticas
    delete[] orden; delete[] tiempos; delete copia; // Libera la memoria
}
