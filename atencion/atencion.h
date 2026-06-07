#ifndef ATENCION_H
#define ATENCION_H

#include "../estructuras.h"

struct NodoCola {
    Paciente paciente;
    int prioridad;
    NodoCola* siguiente;
};

void agregarACola();
void atenderPaciente();
void finalizarConsulta();
void mostrarColaEspera();

#endif