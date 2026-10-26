#ifndef PlanExpro_HPP
#define PlanExpro_HPP

#include "dqueue.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

class Expropiativo {
protected:
    int quantum;
    void mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios);
public:
    virtual void ejecutar(dqueue* cola_original) = 0;
};

class RoundRobin : public Expropiativo {
public:
    void ejecutar(dqueue* cola_original) override;
};

class Prioridad : public Expropiativo {
public:
    void ejecutar(dqueue* cola_original) override;
};

#endif