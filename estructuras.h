#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include <string>

using namespace std;

//PACIENTES
struct Paciente{
    int idPaciente;
    string nombre;
    string apellidos;
    int edad;
    string nss;
    int prioridad;
    int estadoRevision;
    string enfermedad;
    string fechaIngreso;
};
struct NodoPaciente{
    Paciente paciente;
    NodoPaciente * siguiente;
};


//CONSULTORIOS
struct Consultorio
{
    int numero;
    string medico;
    string especialidad;
};

struct NodoConsultorio
{
    Consultorio dato;
    NodoConsultorio* siguiente;
};

//Lista de Espera
struct NodoListaEspera
{
    Paciente paciente;
    NodoListaEspera* siguiente;
};

// Historial (pila)
struct RegistroHistorial
{
    string fecha;
    string accion;
};

struct NodoHistorial
{
    RegistroHistorial registro;
    NodoHistorial* siguiente;
};

#endif