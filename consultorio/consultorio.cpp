#include <iostream>
#include "../estructuras.h"
#include "consultorio.h"
#include <cstring>
#include <cstdlib>

using namespace std;
NodoConsultorio *headConsultorio = NULL;

// Se crea una cantidad "default" de consultorios cerrados
void createConsultorios(){
    for (int i = 1; i <= 5; i++){
        NodoConsultorio *nuevo = (NodoConsultorio *)malloc(sizeof(NodoConsultorio));
        nuevo->consultorio.numero = i;
        strcpy(nuevo->consultorio.medico, "Sin Asignar");
        strcpy(nuevo->consultorio.paciente, "Ninguno");
        nuevo->consultorio.estado = 0;         // Empiezan inhabilitados (0), 1-> habilitados
        nuevo->consultorio.disponibilidad = 0; // 0->No Disponible, 1->Disponible
        nuevo->siguiente = NULL;

        if (headConsultorio == NULL){
            headConsultorio = nuevo;
        }
        else{
            NodoConsultorio *temp = headConsultorio;
            while (temp->siguiente != NULL){
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
    }
}
// Función para agregar consultorios adicionales
void insertConsultorio(){
    char medico[80];

    // Solicitud de datos referentes al consultorio
    cout << "\n\n=================================";
    cout << "\nRegistar nuevo consultorio";
    cout << "\n=================================";
    cin.ignore();
    cout << "\nNombre del médico asignado: ";
    cin.getline(medico, 80);

    // Se crea el nuevo nodo a insertar a la lista de consultorios
    NodoConsultorio *newConsultorio = (NodoConsultorio *)malloc(sizeof(NodoConsultorio));
    if (newConsultorio == NULL){
        cout << "\nError de memoria";
        return;
    }
    strcpy(newConsultorio->consultorio.medico, medico);
    strcpy(newConsultorio->consultorio.paciente, "Ninguno"); // Asignación por defecto
    newConsultorio->consultorio.estado = 1;
    newConsultorio->consultorio.disponibilidad = 1;
    newConsultorio->siguiente = NULL;

    if (headConsultorio == NULL){
        newConsultorio->consultorio.numero = 1;
        headConsultorio = newConsultorio;
    }
    else{
        NodoConsultorio *temp = headConsultorio;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }

        newConsultorio->consultorio.numero = temp->consultorio.numero + 1;
        temp->siguiente = newConsultorio;
    }

    cout << "Consultorio registrado con éxito";

    // mostramos consultorios
    findAllConsultorios();
}
// Función para modificar la información de un consultorio
void updateConsultorio(){
    if (headConsultorio == NULL){
        cout << "\nNo hay consultorios en el sistema.";
        return;
    }

    int numBuscar;
    cout << "\nIngrese el número de consultorio: ";
    cin >> numBuscar;

    NodoConsultorio *consultorio = getConsultorio(numBuscar);

    if (consultorio == NULL){
        cout << "\nNo se encontró el consultorio #" << numBuscar;
        return;
    }
    char medicoNuevo[80];
    int opc;
    printConsultorio(consultorio);
    cout << "\n¿Qué desea realizar?";
    cout << "\n\n1.- Habilitar/Inhabilitar consultorio";
    cout << "\n2.- Modificar médico asignado";
    cout << "\n3.- Cancelar";
    cout << "\n\nIngrese el número de la operación a realizar: ";
    cin >> opc;

    switch (opc){
    case 1:
        if (consultorio->consultorio.estado == 1 && consultorio->consultorio.disponibilidad == 0) {
            cout << "\nNo se puede inhabilitar el consultorio #" << numBuscar; 
            cout << " porque tiene una consulta activa\n";
            return;
        }
        if (consultorio->consultorio.estado == 0){
            consultorio->consultorio.estado = 1;
            consultorio->consultorio.disponibilidad = 1;
            cout << "Se habilitó el consultorio #" << numBuscar << "\n";
            // registrar médico después de habilitar un consultorio
            cout << "\n\n---------------------------------";
            cin.ignore();
            cout << "\nNombre del médico asignado: ";
            cin.getline(medicoNuevo, 80);
            strcpy(consultorio->consultorio.medico, medicoNuevo);
            strcpy(consultorio->consultorio.paciente, "Ninguno"); // Asignación por defecto
        }
        else{
            strcpy(consultorio->consultorio.medico, "Sin Asignar");
            strcpy(consultorio->consultorio.paciente, "Ninguno");
            consultorio->consultorio.estado = 0;
            consultorio->consultorio.disponibilidad = 0;

            cout << "Se deshabilitó el consultorio #" << numBuscar << "\n";
        }
        printConsultorio(consultorio);
        break;
    case 2:
        if(consultorio->consultorio.estado == 0){
            cout << "\nEl consultorio #" << numBuscar << " está inhabilitado";
            return;
        }
        if(consultorio->consultorio.disponibilidad == 0){
            cout << "\nNo se puede cambiar de médico por el momento. Hay una consulta activa";
            return;
        }
        cout << "Médico asignado (actual): " << consultorio->consultorio.medico << "\n";
        cin.ignore();
        cout << "Ingrese el nuevo nombre del médico: ";
        cin.getline(medicoNuevo, 80);
        // actualización
        strcpy(consultorio->consultorio.medico, medicoNuevo);
        cout << "Médico actualizado\n";
        printConsultorio(consultorio);
        break;
    case 3:
        cout << "No se realizaron cambios\n";
        break;
    default:
        cout << "Opción no disponible\n";
        break;
    }
}

void findConsultorio(){
    int idBuscar;
    cout << "\nIngrese el número de consultorio a buscar: ";
    cin >> idBuscar;

    NodoConsultorio *aux = getConsultorio(idBuscar);
    if (aux != NULL){
        printConsultorio(aux);
    }
    else{
        cout << "\nConsultorio no encontrado.";
    }
}

void findAllConsultorios(){
    cout << "\n\n========================================";
    cout << "\nLISTADO DE CONSULTORIOS";
    cout << "\n========================================\n";

    if (headConsultorio == NULL){
        cout << "\nNo hay consultorios registrados.\n";
        return;
    }
    NodoConsultorio *temp = headConsultorio;

    while (temp != NULL){
        printConsultorio(temp);
        temp = temp->siguiente;
    }
    cout << "\n========================================\n";
}

NodoConsultorio *getConsultorio(int num){
    NodoConsultorio *aux = headConsultorio;
    while (aux != NULL){
        if (aux->consultorio.numero == num){
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

void printConsultorio(NodoConsultorio *consultorio){
    cout << "\n----------------------------------------";
    cout << "\nCONSULTORIO #" << consultorio->consultorio.numero;
    cout << "\n----------------------------------------";

    cout << "\nMédico asignado: " << consultorio->consultorio.medico;
    if (consultorio->consultorio.estado == 0){
        cout << "\nEstado: Inhabilitado";
    }
    else{
        cout << "\nEstado: Habilitado";
    }
    if (consultorio->consultorio.disponibilidad == 0){
        cout << "\n----- No Disponible -----";
    }
    else{
        cout << "\n------- Disponible ------";
    }
    cout << "\nPaciente actual: " << consultorio->consultorio.paciente;
    cout << "\n";
}
