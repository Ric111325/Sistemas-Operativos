#ifndef dqueue_hpp
#define dqueue_hpp

#include <iostream>

using namespace std;

// Clase principal que representa la cola de procesos
class dqueue{
public:

// Clase interna anidada que representa cada nodo
    class node {
    public: 
        char ID; // Identificador único del proceso
        int tiempo; // Duración total estimada del proceso
        int prioridad; // Nivel de prioridad del proceso
        
        int tiempo_restante; // Tiempo de ejecución que le falta por completar
        int tiempo_retorno; // Tiempo total desde que el proceso ingresó hasta que finalizó

        node *nxt; // Puntero al siguiente nodo en la cola

        // Constructor del nodo para inicializar sus atributos principales
        node(char _id, int _tiempo, int _prioridad);
    };
private:
        node *start; // Puntero al primer nodo (frente de la cola)
        node *end; // Puntero al último nodo (final de la cola)
        int s; // Entero que almacena el tamaño actual (size)

public:    
        dqueue(); // Constructor de la cola
        ~dqueue(); // Destructor de la cola

        void enqueue(char id, int tiempo, int prioridad); // Inserta un nuevo proceso al final de la cola
        void dequeue(); // Elimina el primer proceso del frente de la cola
        void limpiar(); // Elimina todos los elementos y vacía la cola por completo
        
        int size() const {return s;} // Devuelve la cantidad de procesos en la cola
        bool Empty() const {return s == 0;} // Indica si la cola está vacía (`true`) o tiene elementos (`false`)
    
        node* getStart() const { return start; } // Devuelve un puntero al primer nodo para poder recorrer la cola
        dqueue* clonar() const; // Crea y devuelve una copia exacta de la cola

        void ordenarPorTiempo(); // Ordena los procesos de la cola de menor a mayor duración
        void moverAlFinal(char id); // Busca un proceso por su ID y lo traslada al final de la cola
    };  
    
#endif // dqueue_hpp
