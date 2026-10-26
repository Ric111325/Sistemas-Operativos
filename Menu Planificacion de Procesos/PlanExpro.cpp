#include "PlanExpro.hpp"

void Expropiativo::mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios) {
    float suma_tr = 0;
    int n = cola_simulada->size();

    cout << "\n--- Resultados de la Planificacion ---" << endl;

    dqueue::node* aux = cola_simulada->getStart();
    while (aux != nullptr) {
        cout << "ID: " << aux->ID 
             << " | Tiempo: " << aux->tiempo 
            
             << " | Prioridad Final: " << aux->prioridad 
             << " | Tiempo de Retorno: " << aux->tiempo_retorno << endl;
             
        suma_tr += aux->tiempo_retorno;
        aux = aux->nxt;
    }
    
    cout << "-------------------------------------------------------" << endl;
    cout << "Tiempo de Retorno Promedio: " << fixed << setprecision(2) << (suma_tr / n) << endl;

    cout << "\nSimulacion (Diagrama de Gantt):" << endl;
    cout << tiempos[0];
    for (int i = 0; i < num_cambios; ++i) {
        cout << " [" << orden[i] << "] " << tiempos[i+1];
    }
    cout << "\n\n";
}

void RoundRobin::ejecutar(dqueue* cola_original) {
    dqueue* copia = cola_original->clonar();
    int n = copia->size();
    if (n == 0) return;
    
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
    
    int tiempo_actual = 0;
    int idx = 0;
    tiempos[0] = 0;
    int completados = 0;

    while (completados < n) {
        bool progreso = false;
        dqueue::node* aux = copia->getStart();
        
        while (aux != nullptr) {
            if (aux->tiempo_restante > 0) {
                progreso = true;
                orden[idx] = aux->ID;
                
                if (aux->tiempo_restante > quantum) {
                    tiempo_actual += quantum;
                    aux->tiempo_restante -= quantum;
                } else {
                    tiempo_actual += aux->tiempo_restante;
                    aux->tiempo_restante = 0;
                    aux->tiempo_retorno = tiempo_actual;
                    completados++;
                }
                tiempos[idx + 1] = tiempo_actual;
                idx++;
            }
            aux = aux->nxt;
        }
        if (!progreso) break;
    }

    cout << "\n=== Planificacion Round-Robin (Quantum Calculado = " << quantum << ") ===";
    mostrarResultados(copia, orden, tiempos, idx);

    delete[] orden; delete[] tiempos; delete copia;
}

void Prioridad::ejecutar(dqueue* cola_original) {
    dqueue* copia = cola_original->clonar();
    int n = copia->size();
    
    int max_cambios = 1000; 
    char* orden = new char[max_cambios];
    int* tiempos = new int[max_cambios + 1];
    
    int tiempo_actual = 0;
    int idx = 0;
    tiempos[0] = 0;
    int completados = 0;

    char ultimo_id = '\0';

    while (completados < n) {
        dqueue::node* aux = copia->getStart();
        dqueue::node* mejor_proceso = nullptr;
        
        int mejor_prioridad = -999999; 

        while (aux != nullptr) {
  
            if (aux->tiempo_restante > 0 && aux->prioridad > mejor_prioridad) {
                mejor_prioridad = aux->prioridad;
                mejor_proceso = aux;
            }
            aux = aux->nxt;
        }

        if (mejor_proceso != nullptr) {
            if (ultimo_id != mejor_proceso->ID) {
                if (idx > 0) {
                    tiempos[idx] = tiempo_actual; 
                }
                orden[idx] = mejor_proceso->ID;
                ultimo_id = mejor_proceso->ID;
                idx++;
            }

            
            mejor_proceso->tiempo_restante--;
            
           
            if (mejor_proceso->prioridad > 0) {
                mejor_proceso->prioridad--; 
            }       

            tiempo_actual++;

            if (mejor_proceso->tiempo_restante == 0) {
                mejor_proceso->tiempo_retorno = tiempo_actual;
                completados++;
            }
        }
    }
    tiempos[idx] = tiempo_actual; 

    cout << "\n=== Planificacion por Prioridad (Expropiativa y Dinamica) ===";
    mostrarResultados(copia, orden, tiempos, idx);

    delete[] orden; delete[] tiempos; delete copia;
}