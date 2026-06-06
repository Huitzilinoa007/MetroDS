#include <iostream>
#include "string"
#include "../estructuras.h"

using namespace std;
NodoPaciente* headPaciente = NULL;

void insertPaciente(){
    int idPaciente, edad, prioridad, estadoRevision = 0;
    string nombre, apellidos, nss, enfermedad = "s/n", fechaIngreso;

    cout<<"\n\n=================================";
    cout<<"\nDar de alta paciente";
    cout<<"\n=================================";
    cout<<"\n\nIngrese los datos del paciente";

    cin.ignore();
    cout<<"\nNombre(s): ";
    getline(cin, nombre);
    cout<<"Apellidos: ";
    getline(cin, apellidos);
    cout<<"Edad: ";
    cin>>edad;
    cout<<"Número de Seguridad Social (NSS): ";
    cin>>nss;
    cout<<"Nivel de prioridad: ";
    cin>>prioridad;
    cout<<"Fecha de ingreso (DD/MM/YYYY): ";
    cin>>fechaIngreso;

    NodoPaciente* newPaciente;
    newPaciente = (NodoPaciente*) malloc(sizeof(NodoPaciente));
    newPaciente->paciente.nombre = nombre;
    newPaciente->paciente.apellidos = apellidos;
    newPaciente->paciente.edad = edad;
    newPaciente->paciente.nss = nss;
    newPaciente->paciente.prioridad = prioridad;
    newPaciente->paciente.estadoRevision = 0;
    newPaciente->paciente.enfermedad = "Ninguna";
    newPaciente->paciente.fechaIngreso = fechaIngreso;
    newPaciente->siguiente = NULL;

    //aquí se pone el nuevo paciente en la lista de pacientes
    if(headPaciente==nullptr){
        headPaciente->siguiente = newPaciente;
    }else{
        NodoPaciente* temp = headPaciente;
        while(temp->siguiente != nullptr){
            temp=temp->siguiente;
        }
        temp->siguiente = newPaciente;
    }

    cout<<"Paciente registrado con éxito";
}

void updatePaciente(){
}

void deletePaciente(){

}

void findPaciente(){

}

void findAllPacientes(){

}