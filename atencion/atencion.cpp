#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../estructuras.h"
#include "atencion.h"
#include "../consultorio/consultorio.h"

using namespace std;
NodoCola* frenteCola = NULL;

const char* getNivelPrioridad(int prioridad){
    switch(prioridad){
        case 0:
            return "CONSULTA GENERAL";
        case 1:
            return "MENOR DE EDAD";
        case 2:
            return "PERSONA CON DISCAPACIDAD";
        case 3:
            return "MAYOR DE EDAD";
        case 4:
            return "EMBARAZO";
        case 5:
            return "URGENCIA NO CRITICA";
        case 6:
            return "URGENCIA GRAVE";
        case 7:
            return "RIESGO VITAL";
        default:
            return "DESCONOCIDA";
    }
}
//función para agregar a la lista de espera
void agregarACola(Paciente pcnt, int prioridad){
    NodoCola* nuevoP = (NodoCola*) malloc(sizeof(NodoCola));
    if (nuevoP == NULL) {
        cout << "\nError de memoria";
        return;
    }
    nuevoP->paciente = pcnt;
    nuevoP->prioridad = prioridad;
    nuevoP->siguiente = NULL;

    //insertarlo al frente si está vacía la lista o si tiene mayor prioridad
    if (frenteCola == NULL || prioridad > frenteCola->prioridad) {
        nuevoP->siguiente = frenteCola;
        frenteCola = nuevoP;
    //buscar posición por prioridades
    } else {
        NodoCola* temp = frenteCola;
        while (temp->siguiente != NULL && temp->siguiente->prioridad >= prioridad) {
            temp = temp->siguiente;
        }
        nuevoP->siguiente = temp->siguiente;
        temp->siguiente = nuevoP;
    }
    cout << "\nPaciente ingresado a la lista de espera";
}

void atenderPaciente(){
    if(frenteCola == NULL){
        cout << "\nNo hay pacientes en la lista de espera actualmente";
    }
    //para obtener la lista de los consultorios y variable global
    extern NodoConsultorio* headConsultorio; 
    NodoConsultorio* aux = headConsultorio;
    NodoConsultorio* consDestino = NULL;

    while (aux != NULL){
        if(aux->consultorio.estado == 1 && aux->consultorio.disponibilidad == 1){
            consDestino = aux;
            break;
        }
        aux = aux->siguiente;
    }
    if(consDestino == NULL){
        cout << "[x] No se puede atender al paciente. Todos los consultorios están ocupados";
        return;
    }
    //para quitar al paciente de la lista de espera
    NodoCola* pacienteActual = frenteCola;
    frenteCola = frenteCola->siguiente;
    //asignamos al consultorio la nueva información
    strcpy(consDestino->consultorio.paciente, pacienteActual->paciente.nombre); 
    consDestino->consultorio.disponibilidad = 0;

    cout<<"\n\n=================================";
    cout<<"\n      Ingreso a consultorio";
    cout<<"\n=================================";
    cout<<"\nPaciente: "<< pacienteActual->paciente.nombre;
    cout<<"\nMotivo: "<< pacienteActual->paciente.enfermedad;
    cout<<"\n[!]: "<< getNivelPrioridad(pacienteActual->prioridad);
    cout<<"\nAsignado a Consultorio #"<< consDestino->consultorio.numero;
    cout<<"\nAtendido por: "<< consDestino->consultorio.medico;
    cout<<"\n---------------------------------";

    free(pacienteActual);
}

void mostrarColaEspera(){
    cout << "\n\n========================================";
    cout << "\n  LISTA DE ESPERA";
    cout << "\n========================================";

    if(frenteCola == NULL){
        cout << "\nLista de espera vacía.\n";
        return;
    }
    NodoCola* temp = frenteCola;
    int pos = 1;
    while(temp != NULL){
        cout << "\n " << pos << ".- " << temp->paciente.nombre; 
        cout << "\nNSS: " << temp->paciente.nss;
        cout << "\n[!] Prioridad: " << getNivelPrioridad(temp->prioridad);
        cout << "\n-----------------------------------------";
        temp = temp->siguiente;
        pos++;
    }
    cout << "\n========================================\n";
}
