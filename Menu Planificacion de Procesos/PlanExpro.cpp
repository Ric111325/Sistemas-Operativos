#include "PlanExpro.hpp"

// Método para mostrar el estado actual de la cola de procesos (solo los que tienen tiempo pendiente)
void Expropiativo::mostrarEstadoCola(dqueue* cola) {
    dqueue::node* aux = cola->getStart();
    bool hay = false;
    while (aux != nullptr) {
        // Imprime el ID del proceso si aún le queda tiempo por ejecutar
        if (aux->tiempo_restante > 0) {
            cout << "[" << aux->ID << "]";
            hay = true;
        }
        aux = aux->nxt;
    }
    if (!hay) cout << "[Vacia]"; // Si ningún proceso tiene tiempo restante, indica que la cola está vacía
}

// Método para mostrar la tabla final de resultados, estadísticas y diagrama de Gantt simplificado
void Expropiativo::mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios) {
    float suma_tr = 0;
    int n = cola_simulada->size();

    cout << "\n--- Resultados de la Planificacion ---" << endl;
    // Recorre la cola simulada para imprimir los datos finales de cada proceso
    dqueue::node* aux = cola_simulada->getStart();
    while (aux != nullptr) {
        cout << "ID: " << aux->ID 
             << " | Tiempo: " << aux->tiempo 
            
             << " | Prioridad Final: " << aux->prioridad 
             << " | Tiempo de Retorno: " << aux->tiempo_retorno << endl;
             
        suma_tr += aux->tiempo_retorno; // Acumula el tiempo de retorno para calcular el promedio
        aux = aux->nxt;
    }
    
    cout << "-------------------------------------------------------" << endl;
    cout << "Tiempo de Retorno Promedio: " << fixed << setprecision(2) << (suma_tr / n) << endl; // Imprime el promedio del tiempo de retorno formateado a 2 decimales

    // Imprime la secuencia cronológica de la simulación (Diagrama de tiempos)
    cout << "\nSimulacion:" << endl;
    cout << tiempos[0];
    for (int i = 0; i < num_cambios; ++i) {
        cout << " [" << orden[i] << "] " << tiempos[i+1];
    }
    cout << "\n\n";
}
// Implementación del algoritmo de planificación Round Robin
void RoundRobin::ejecutar(dqueue* cola_original) {
    dqueue* copia = cola_original->clonar(); // Crea una copia de la cola original para no alterarla
    int n = copia->size();
    if (n == 0) return; // Si la cola está vacía, termina la ejecución

    // Calcula el quantum dinámicamente como el promedio de los tiempos de los procesos
    int suma_tiempos = 0;
    dqueue::node* aux_q = copia->getStart();
    while (aux_q != nullptr) {
        suma_tiempos += aux_q->tiempo;
        aux_q = aux_q->nxt;
    }
    quantum = suma_tiempos / n; 
    if (quantum == 0) quantum = 1; // Asegura que el quantum sea al menos 1
    
    int max_cambios = 1000; 
    char* orden = new char[max_cambios]; // Almacena el ID de los procesos ejecutados en orden
    int* tiempos = new int[max_cambios + 1]; // Almacena los puntos de tiempo en la línea de tiempo
    
    int tiempo_actual = 0, idx = 0, completados = 0;
    tiempos[0] = 0;

    cout << "\n=== Simulacion Round-Robin / Quantum = " << quantum << ") ===\n";
    cout << "Evolucion de la cola:\n";
    mostrarEstadoCola(copia); 

    // Bucle principal: se ejecuta hasta que todos los procesos hayan terminado
    while (completados < n) {
        dqueue::node* aux = copia->getStart();

        // Busca el primer proceso que aún tenga tiempo restante por ejecutar
        while (aux != nullptr && aux->tiempo_restante == 0) {
            aux = aux->nxt;
        }
        
        if (aux != nullptr) {
            // Define si el proceso se ejecuta todo su quantum o el tiempo restante que le queda
            int tiempo_ejecucion = (aux->tiempo_restante < quantum) ? aux->tiempo_restante : quantum;
            
            orden[idx] = aux->ID;
            tiempos[idx + 1] = tiempo_actual + tiempo_ejecucion;
            idx++;
            
            aux->tiempo_restante -= tiempo_ejecucion; // Reduce el tiempo pendiente del proceso
            tiempo_actual += tiempo_ejecucion; // Avanza el reloj global de la simulación

            // Si el proceso finalizó, registra su tiempo de retorno; si no, lo manda al final de la cola
            if (aux->tiempo_restante == 0) {
                aux->tiempo_retorno = tiempo_actual;
                completados++;
            } else {
                copia->moverAlFinal(aux->ID);
            }
            cout << " -> ";
            mostrarEstadoCola(copia);
        }
    }
    cout << "\n";

    mostrarResultados(copia, orden, tiempos, idx); // Muestra los resultados finales
    delete[] orden; delete[] tiempos; delete copia; // Libera la memoria dinámica reservada "Todo lo creado con new se borra con delete"
}

// Implementación del algoritmo de planificación por Prioridades
void Prioridad::ejecutar(dqueue* cola_original) {
    dqueue* copia = cola_original->clonar(); // Clona la cola original
    int n = copia->size();
    if (n == 0) return;

    // Cálculo automático del quantum
    int suma_tiempos = 0;
    dqueue::node* aux_q = copia->getStart();
    while (aux_q != nullptr) {
        suma_tiempos += aux_q->tiempo;
        aux_q = aux_q->nxt;
    }
    quantum = suma_tiempos / n; 
    if (quantum == 0) quantum = 1;

    int max_cambios = 1000; 
    char* orden = new char[max_cambios];
    int* tiempos = new int[max_cambios + 1];
    
    int tiempo_actual = 0, idx = 0, completados = 0;
    tiempos[0] = 0;
    char ultimo_id = '\0'; // Rastrea el último proceso ejecutado para agrupar bloques en el Gantt

    cout << "\n=== Simulacion Prioridad / Quantum = " << quantum << " ===\n";
    cout << "Evolucion de la cola:\n";
    mostrarEstadoCola(copia); 

    while (completados < n) {
        dqueue::node* aux = copia->getStart();
        dqueue::node* mejor_proceso = nullptr;
        int mejor_prioridad = -999999; 

        // Busca en toda la cola el proceso con mayor prioridad que aún tenga tiempo restante
        while (aux != nullptr) {
            if (aux->tiempo_restante > 0 && aux->prioridad > mejor_prioridad) {
                mejor_prioridad = aux->prioridad;
                mejor_proceso = aux;
            }
            aux = aux->nxt;
        }

        if (mejor_proceso != nullptr) {
            int tiempo_ejecucion = (mejor_proceso->tiempo_restante < quantum) ? mejor_proceso->tiempo_restante : quantum;

            // Control para registrar cambios en el orden de ejecución evitando duplicados consecutivos
            if (ultimo_id != mejor_proceso->ID) {
                if (idx > 0) tiempos[idx] = tiempo_actual; 
                orden[idx] = mejor_proceso->ID;
                ultimo_id = mejor_proceso->ID;
                idx++;
            } else if (idx == 0) {
                orden[idx] = mejor_proceso->ID;
                ultimo_id = mejor_proceso->ID;
                idx++;
            }

            mejor_proceso->tiempo_restante -= tiempo_ejecucion;
            tiempo_actual += tiempo_ejecucion;

            // Envejecimiento dinámico de la prioridad
            if (mejor_proceso->prioridad > 0) {
                mejor_proceso->prioridad--; 
            }       

            // Verifica si el proceso terminó o se reubica al final de la cola
            if (mejor_proceso->tiempo_restante == 0) {
                mejor_proceso->tiempo_retorno = tiempo_actual;
                completados++;
            } else {
                copia->moverAlFinal(mejor_proceso->ID);
            }
            
            cout << " -> ";
            mostrarEstadoCola(copia);
        }
    }
    cout << "\n";
    tiempos[idx] = tiempo_actual; // Registra el tiempo final de la ejecución
    
    mostrarResultados(copia, orden, tiempos, idx); // Muestra estadísticas y resultados
    delete[] orden; delete[] tiempos; delete copia; // Libera la memoria dinámica
}
