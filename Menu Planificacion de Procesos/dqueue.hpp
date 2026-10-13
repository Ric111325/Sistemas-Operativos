#ifndef dqueue_hpp
#define dqueue_hpp


#include <iostream>

using namespace std;

class dqueue{
public:

    class node {
    
    public: 
        char ID;
        int prioridad;
        int tiempo;
        int tiempo_restante;
        int tiempo_retorno;

        node *nxt;
        node(char _id, int _tiempo, int _prioridad);
    };
private:
        
        node *start;
        node *end;
        int s;

public:    
        dqueue();
        ~dqueue();


        void enqueue(char id, int tiempo, int prioridad); //Agrega un elemento al final de la cola
        void dequeue(); //Elimina un elemento del frente de la cola
        void limpiar(); //Elimina todos los elementos de la cola

        
        int size() const {return s;} //Devuelve el tamaño de la cola
        bool Empty() const {return s == 0;} //Devuelve true si la cola esta vacia
    
        node* getStart() const { return start; } //Devuelve el primer elemento de la cola
        dqueue* clonar() const; //Crea una copia de la cola actual

        void ordenarPorTiempo(); //Ordena los elementos de la cola por tiempo de menor a mayor
    };  
    
#endif // dqueue_hpp