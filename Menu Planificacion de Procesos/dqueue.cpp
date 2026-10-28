#include "dqueue.hpp"

dqueue::node::node(char _id, int _tiempo, int _prioridad) { // Constructor del nodo
    ID = _id;
    tiempo = _tiempo;
    prioridad = _prioridad;
    tiempo_restante = _tiempo;
    tiempo_retorno = 0;
    nxt = nullptr;
}

dqueue::dqueue() {  // Constructor de la cola
    start = nullptr;
    end = nullptr;
    s = 0; 
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
    if(s <= 1) return; 
    
    bool huboCambio;
    do {
        huboCambio = false;
        node *actual = start;
        while (actual->nxt != nullptr) {
            if (actual->tiempo > actual->nxt->tiempo) {
                swap(actual->ID, actual->nxt->ID);
                swap(actual->tiempo, actual->nxt->tiempo);
                swap(actual->prioridad, actual->nxt->prioridad);
                swap(actual->tiempo_restante, actual->nxt->tiempo_restante);
                huboCambio = true;

            }
            actual = actual->nxt;
        }
    } while (huboCambio);
}

// ... (Deja todo tu codigo anterior de dqueue_2.cpp arriba de esto) ...

void dqueue::moverAlFinal(char id) {
    if (s <= 1) return;
    if (end->ID == id) return; 
    
    node* actual = start;
    node* previo = nullptr;
    
   
    while (actual != nullptr && actual->ID != id) {
        previo = actual;
        actual = actual->nxt;
    }
    
    if (actual == nullptr) return;
    
  
    if (previo == nullptr) {
        start = start->nxt; 
    } else {
        previo->nxt = actual->nxt; 
    }
    
    actual->nxt = nullptr;
    end->nxt = actual;
    end = actual;
}