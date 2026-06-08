#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

//PACIENTES
struct Paciente{
    char nombre[40];
    char apellidos[40];
    int edad;
    char nss[11];
    int prioridad;
    int estadoRevision;
    char enfermedad[40];
};
struct NodoPaciente{
    Paciente paciente;
    NodoPaciente * siguiente;
};


//CONSULTORIOS
struct Consultorio
{
    int numero;
    char medico[80];
    char pacienteNss[11];
    //char paciente[80];
    int estado;
    int disponibilidad;
};

struct NodoConsultorio
{
    Consultorio consultorio;
    NodoConsultorio* siguiente;
};

//Lista de Espera
struct NodoCola
{
    Paciente paciente; //para tener toda la info de pacientes completa
    int prioridad;
    NodoCola* siguiente;
};

// Historial (pila)
struct RegistroHistorial
{
    char fecha[100];
    char accion[100];
};

struct NodoHistorial
{
    RegistroHistorial registro;
    NodoHistorial* siguiente;
};

#endif