#ifndef PACIENTE_H
#define PACIENTE_H

#include "../estructuras.h"

void insertPaciente();
void updatePaciente();
void deletePaciente();
void findPaciente();
void findAllPacientes();

NodoPaciente* getPacienteByNSS(char nss[11]);
bool deletePacienteByNSS(char nssPaciente[11]);
void printPaciente(NodoPaciente* paciente);
const char* getNivelPrioridad(int prioridad);
const char* getEstadoRevision(int estadoRevision);

#endif