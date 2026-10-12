#ifndef dqueue_hpp
#define dqueue_hpp


#include <iostream>

using namespace std;

class dqueue{

    class node {

        int dat ;
        node *nxt;

        public:
        
            node(int);

            node *next() const { return nxt;} //Getter que devuelve la direccion de un nodo     //  Getter para el apuntador
            void next (node *p) { nxt = p;} // Setter que guarda la direccion en el nodo        //  Setter para el apuntador
            int ID() const {return dat;} //Getter que devuevle la info del nodo               //  Getter para el dato
            int tm() const {return dat;} //Getter que devuevle la info del nodo               //  Getter para el dato
            int prioridad() const {return dat;} //Getter que devuevle la info del nodo               //  Getter para el dato
        };      
        

        node *start;

        int n; //Capacidad
        int s; //Tamaño

    public:
        dqueue(int);
        ~dqueue();


        void enqueue(int); //Agrega un elemento al final de la cola
        void dequeue(); //Elimina un elemento del frente de la cola
        int front() const; //Devuelve el elemento del frente de la cola

        int capacidad() const {return n;} //Devuelve la capacidad de la cola
        int size() const {return s;} //Devuelve el tamaño de la cola

        bool Empty() const {return s == 0;} //Devuelve true si la cola esta vacia
        bool Full() const {return s == n;} //Devuelve true si la cola esta llena

        void print(); //Imprime los elementos de la cola
    };  
    
#endif dqueue_hpp