#include "dqueue.hpp"

// Constructor de la clase interna 'node'
dqueue::node::node(char _id, int _tiempo, int _prioridad) { // Constructor del nodo
    ID = _id; // Asigna el identificador único del proce
    tiempo = _tiempo; 
    prioridad = _prioridad; // Asigna el nivel de prioridad
    tiempo_restante = _tiempo;
    tiempo_retorno = 0; // Inicializa el tiempo de retorno en 0
    nxt = nullptr;
}

dqueue::dqueue() {  // Constructor de la cola
    start = nullptr;
    end = nullptr;
    s = 0; // El tamaño inicial de la cola es 0
}


dqueue::~dqueue() { // Destructor de la cola
    limpiar();
}



void dqueue::limpiar() { // Elimina todos los elementos de la cola
    node *temp;
    while (start != nullptr) {
        temp = start;
        start = start->nxt;
        delete temp;
    }
    end = nullptr;
    s = 0;
}

void dqueue::enqueue(char id, int tiempo, int prioridad) { // Agrega un elemento al final de la cola
    node *nuevo = new node(id, tiempo, prioridad);
    
    if (Empty()) {
        start = nuevo;
        end = nuevo;
    } else {
        end->nxt = nuevo;
        end = nuevo;
    }
    s++;
}

dqueue* dqueue::clonar() const { // Crea una copia de la cola actual
    dqueue* copia = new dqueue(); 
    node *temp = start;
    while (temp != nullptr) {

        copia->enqueue(temp->ID, temp->tiempo, temp->prioridad);
        temp = temp->nxt;
    }
    return copia;
}

void dqueue::ordenarPorTiempo() { //Ordena los elementos segun el tiempo 
    if(s <= 1) return; // Si la cola tiene 0 o 1 elemento, ya está ordenada
    
    bool huboCambio;
    do {
        huboCambio = false;
        node *actual = start;
        while (actual->nxt != nullptr) {
            // Si el proceso actual dura más que el siguiente, se intercambian todos sus atributos
            if (actual->tiempo > actual->nxt->tiempo) {
                swap(actual->ID, actual->nxt->ID);
                swap(actual->tiempo, actual->nxt->tiempo);
                swap(actual->prioridad, actual->nxt->prioridad);
                swap(actual->tiempo_restante, actual->nxt->tiempo_restante);
                huboCambio = true;

            }
            actual = actual->nxt;
        }
    } while (huboCambio); // Repite mientras se hayan realizado intercambios
}


void dqueue::moverAlFinal(char id) {
    if (s <= 1) return; // Si hay 1 o ningún elemento, no hay nada que mover
    if (end->ID == id) return; // Si el proceso ya está al final, no se requiere acción
    
    node* actual = start;
    node* previo = nullptr;
    
   // Busca el nodo que coincida con el ID proporcionado, rastreando su nodo previo
    while (actual != nullptr && actual->ID != id) {
        previo = actual;
        actual = actual->nxt;
    }
    
    if (actual == nullptr) return; // Si no se encuentra el ID, termina
    
  // Desvincula el nodo encontrado de su posición actual
    if (previo == nullptr) {
        start = start->nxt; 
    } else {
        previo->nxt = actual->nxt; 
    }

    // Coloca el nodo desvinculado al final de la cola
    actual->nxt = nullptr;
    end->nxt = actual;
    end = actual;
}
