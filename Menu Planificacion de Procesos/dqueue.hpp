#ifndef dqueue_hpp
#define dqueue_hpp

#include <iostream>

using namespace std;

class dqueue{
public:

    class node {
    public: 
        char ID;
        int tiempo;
        int prioridad;
        
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

        void enqueue(char id, int tiempo, int prioridad); 
        void dequeue(); 
        void limpiar(); 
        
        int size() const {return s;} 
        bool Empty() const {return s == 0;} 
    
        node* getStart() const { return start; } 
        dqueue* clonar() const; 

        void ordenarPorTiempo(); 
        void moverAlFinal(char id); // <--- NUEVA FUNCION AÑADIDA
    };  
    
#endif // dqueue_hpp