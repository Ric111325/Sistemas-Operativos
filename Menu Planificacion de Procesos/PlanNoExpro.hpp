#ifndef PlanNoExpro_HPP
#define PlanNoExpro_HPP

#include "dqueue.hpp"
#include <iostream>
#include <iomanip>

using namespace std;


class NoExpropiativo {
protected:
    void mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios); // Muestra los resultados de la planificacion de procesos
    void mostrarEstadoCola(dqueue* cola); // Muestra como va cambiando la cola 
public:
    virtual void ejecutar(dqueue* cola_original) = 0; // Metodo virtual para ejecutar la planificacion de procesos
};


class FIFO : public NoExpropiativo { // Clase que implementa a FIFO
public:
    void ejecutar(dqueue* cola_original) override;
};

class SJF : public NoExpropiativo { // Clase que implementa a SJF
public:
    void ejecutar(dqueue* cola_original) override; // Metodo que ejecuta la planificacion de procesos SJF
};


#endif