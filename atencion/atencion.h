#ifndef ATENCION_H
#define ATENCION_H

#include "../estructuras.h"

struct NodoCola {
    Paciente paciente;
    int prioridad;
    NodoCola* siguiente;
};

void agregarACola(Paciente p, int prioridad);
void atenderPaciente();
void mostrarColaEspera();

#endif