#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../estructuras.h"
#include "atencion.h"
#include "../consultorio/consultorio.h"
#include "../paciente/paciente.h"

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
void agregarACola(){
    char nssBuscar[11];

    cout<<"\n\n=======================================";
    cout<<"\nIngresar paciente a la lista de espera";
    cout<<"\n=======================================";
    cout<<"\n\nIngrese el NSS del paciente: ";
    cin>>nssBuscar;

    extern NodoPaciente* headPaciente; // accedemos a la lista de pacientes
    NodoPaciente* nodoP = getPacienteByNSS(nssBuscar);

    if (nodoP == NULL) {
        cout << "\nEl NSS no está registrado en el sistema";
        cout << "\nAccediendo al alta del paciente...\n";
        
        insertPaciente(); //registramos al paciente
        
        nodoP = getPacienteByNSS(nssBuscar);
        if (nodoP == NULL) {
            cout << "\nNo se encontró el registro del paciente";
            return;
        }
    }

    if (nodoP->paciente.estadoRevision == 1 || nodoP->paciente.estadoRevision == 2) {
        cout << "\nEste paciente ya se encuentra ";
        cout << (nodoP->paciente.estadoRevision == 1 ? "en la lista de espera" : "en consulta");
        return;
    }

    char enfermedadActual[40];
    int nuevaPrioridad;
    
    cout << "\nPaciente encontrado: " << nodoP->paciente.nombre << " " << nodoP->paciente.apellidos;
    cout << "\nIngrese el motivo de consulta: ";
    cin.ignore();
    cin.getline(enfermedadActual, 40);
    
    cout << "Actualice el nivel de prioridad: ";
    cin >> nuevaPrioridad;

    //se actualizan los nuevos datos
    strcpy(nodoP->paciente.enfermedad, enfermedadActual);
    nodoP->paciente.prioridad = nuevaPrioridad;
    nodoP->paciente.estadoRevision = 1; //se encuentra en la lista de espera

    NodoCola* nuevoP = (NodoCola*) malloc(sizeof(NodoCola));
    if (nuevoP == NULL) {
        cout << "\nError de memoria";
        return;
    }
    nuevoP->paciente = nodoP->paciente;
    nuevoP->prioridad = nuevaPrioridad;
    nuevoP->siguiente = NULL;

    //insertarlo al frente si está vacía la lista o si tiene mayor prioridad
    if (frenteCola == NULL || nuevaPrioridad > frenteCola->prioridad) {
        nuevoP->siguiente = frenteCola;
        frenteCola = nuevoP;
    //buscar posición por prioridades
    } else {
        NodoCola* temp = frenteCola;
        while (temp->siguiente != NULL && temp->siguiente->prioridad >= nuevaPrioridad) {
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
        return;
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
        cout << "No se puede atender al paciente. Todos los consultorios están ocupados";
        return;
    }
    //para quitar al paciente de la lista de espera
    NodoCola* pacienteActual = frenteCola;
    frenteCola = frenteCola->siguiente;
    NodoPaciente* nodoActual = getPacienteByNSS(pacienteActual->paciente.nss);
    if (nodoActual != NULL) {
        nodoActual->paciente.estadoRevision = 2; //se encuentra en consulta ahora
    }
    //asignamos al consultorio la nueva información
    strcpy(consDestino->consultorio.paciente, pacienteActual->paciente.nombre); 
    consDestino->consultorio.disponibilidad = 0;

    cout<<"\n\n=================================";
    cout<<"\n      Ingreso a consultorio";
    cout<<"\n=================================";
    cout<<"\nPaciente: "<< pacienteActual->paciente.nombre;
    cout<<"\nNSS: " << pacienteActual->paciente.nss;
    cout<<"\nMotivo: "<< pacienteActual->paciente.enfermedad;
    cout<<"\n[!]: "<< getNivelPrioridad(pacienteActual->prioridad);
    cout<<"\nAsignado a Consultorio #"<< consDestino->consultorio.numero;
    cout<<"\nAtendido por: "<< consDestino->consultorio.medico;
    cout<<"\n---------------------------------";

    free(pacienteActual);
}

void finalizarConsulta(){
    int numCons;
    cout << "\n=========================================";
    cout << "\n        Finalizar consulta";
    cout << "\n=========================================";
    cout << "\nIngrese el número del consultorio a liberar: ";
    cin >> numCons;

    extern NodoConsultorio* headConsultorio;
    NodoConsultorio* aux = headConsultorio;
    NodoConsultorio* consBuscado = NULL;

    while (aux != NULL) {
        if (aux->consultorio.numero == numCons) {
            consBuscado = aux;
            break;
        }
        aux = aux->siguiente;
    }
    if (consBuscado == NULL) {
        cout << "\nEl consultorio #" << numCons << " no existe";
        return;
    }
    if (consBuscado->consultorio.estado == 0) {
        cout << "\nEl consultorio #" << numCons << " está inhabilitado";
        return;
    }
    if (consBuscado->consultorio.disponibilidad == 1) {
        cout << "\nEl consultorio #" << numCons << " ya está disponible";
        return;
    }

    extern NodoPaciente* headPaciente;
    NodoPaciente* tempP = headPaciente;
    while(tempP != NULL) {
        if(strcmp(tempP->paciente.nombre, consBuscado->consultorio.paciente) == 0 && tempP->paciente.estadoRevision == 2) {
            tempP->paciente.estadoRevision = 3; //se cambia a atendido
            break;
        }
        tempP = tempP->siguiente;
    }
    cout << "\n >>> Finalizando consulta del paciente: " << consBuscado->consultorio.paciente;
    
    // reestablecemos el consultorio
    strcpy(consBuscado->consultorio.paciente, "Ninguno");
    consBuscado->consultorio.disponibilidad = 1; 

    cout << "\nEl consultorio #" << numCons << " ahora está disponible";
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
