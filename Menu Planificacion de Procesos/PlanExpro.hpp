#ifndef PlanExpro_HPP
#define PlanExpro_HPP

#include "dqueue.hpp" // Incluye la estructura de datos personalizada para la cola de procesos
#include <iostream>
#include <iomanip>

using namespace std;

// Clase base abstracta que modela un planificador de CPU expropiativo
class Expropiativo {
protected:
    int quantum; // Intervalo de tiempo máximo asignado a un proceso antes de ser interrumpido
    void mostrarResultados(dqueue* cola_simulada, char orden[], int tiempos[], int num_cambios);
    void mostrarEstadoCola(dqueue* cola);
public:
    virtual void ejecutar(dqueue* cola_original) = 0;
};

// Clase que hereda de Expropiativo para implementar el algoritmo Round Robin
class RoundRobin : public Expropiativo {
public:
    void ejecutar(dqueue* cola_original) override;
};

// Clase que hereda de Expropiativo para implementar la planificación por Prioridades
class Prioridad : public Expropiativo {
public:
    void ejecutar(dqueue* cola_original) override;
};

#endif
