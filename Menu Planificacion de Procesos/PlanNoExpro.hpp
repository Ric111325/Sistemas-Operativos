#ifndef PlanNoExpro_HPP
#define PlanNoExpro_HPP

#include "dqueue.hpp"
#include <iostream>
#include <iomanip>

using namespace std;


class NoExpropiativo {
protected:
    void mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios); // Muestra los resultados de la planificación de procesos
public:
    virtual void ejecutar(dqueue* cola_original) = 0; // Método virtual para ejecutar la planificación de procesos
};


class FIFO : public NoExpropiativo { // Clase que implementa la planificación FIFO
public:
    void ejecutar(dqueue* cola_original) override;
};

class SJF : public NoExpropiativo { // Clase que implementa la planificación SJF
public:
    void ejecutar(dqueue* cola_original) override;
};


#endif