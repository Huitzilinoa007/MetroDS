#include <iostream>
#include "../estructuras.h"
#include "paciente.h"
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;
NodoPaciente* headPaciente = NULL;

void insertPaciente(){
    int edad, prioridad, estadoRevision = 0;
    char nombre[40], apellidos[40], nss[11], enfermedad[40];

    //Se piden los datos del paciente
    cout<<"\n\n=================================";
    cout<<"\nDar de alta paciente";
    cout<<"\n=================================";
    cout<<"\n\nIngrese los datos del paciente";

    cin.ignore();
    cout<<"\nNombre(s): ";
    cin.getline(nombre, 40);
    cout<<"Apellidos: ";
    cin.getline(apellidos, 40);
    cout<<"Edad: ";
    cin>>edad;
    cout<<"Número de Seguridad Social (NSS): ";
    cin>>nss;
    cout<<"Nivel de prioridad: ";
    cin>>prioridad;

    //Se crea el nuevo nodo a insertar a la lista de pacientes 
    NodoPaciente* newPaciente;
    newPaciente = (NodoPaciente*) malloc(sizeof(NodoPaciente));
    strcpy(newPaciente->paciente.nombre, nombre);
    strcpy(newPaciente->paciente.apellidos, apellidos);
    newPaciente->paciente.edad = edad;
    strcpy(newPaciente->paciente.nss, nss);
    newPaciente->paciente.prioridad = prioridad;
    newPaciente->paciente.estadoRevision = 0;
    strcpy(newPaciente->paciente.enfermedad, "Ninguna");
    newPaciente->siguiente = NULL;

    //aquí se pone el nuevo paciente en la lista de pacientes
    if(headPaciente==NULL){
        headPaciente = newPaciente;
    }else{
        NodoPaciente* temp = headPaciente;
        while(temp->siguiente != NULL){
            temp=temp->siguiente;
        }
        temp->siguiente = newPaciente;
    }

    cout<<"Paciente registrado con éxito";

    //y ya que se registró al paciente, se muestran los pacientes registrados
    findAllPacientes();
}

void updatePaciente(){
    if(headPaciente == NULL){
        cout<<"\nNo hay pacientes registrados, vaya al menú 'Registrar paciente'";
        return;
    }

    char nss[11];
    cout<<"\n\n=======================================";
    cout<<"\nActualizar información de los pacientes";
    cout<<"\n=======================================";
    cout<<"\n\nIngrese el NSS del paciente a actualizar su información: ";
    cin>>nss;

    NodoPaciente* nodoPaciente = getPacienteByNSS(nss);
    if(nodoPaciente == NULL){
        cout<<"\nNo se encontró al paciente con NSS: "<< nss << "\nIntente con otro NSS.";
        return;
    }

    bool repModificar = false;
    int opcMenu = 0;
    int opcVolverModifi = 0;
    do{
        cout<<"\n¿Qué desea modificar de '"<< nodoPaciente->paciente.nombre << " " << nodoPaciente->paciente.apellidos <<"' con NSS: "<< nodoPaciente->paciente.nss <<"?";
        cout<<"\n\n1.- Nombre(s): ";
        cout<<"\n2.- Apellidos";
        cout<<"\n3.- Edad";
        cout<<"\n4.- Enfermedad";
        cout<<"\n5.- Prioridd"; 
        cout<<"\n6.- Estado de Revisión";
        cout<<"\n7.- Cancelar";
        cout<<"\n\nIngrese el número de la operación que desea realizar: ";
        cin>>opcMenu;

        switch (opcMenu){
            case 1:{
                char nombre[40];
                cout<<"\nIngrese el nuevo nombre del paciente: ";
                cin.ignore();
                cin.getline(nombre, 40);
                strcpy(nodoPaciente->paciente.nombre, nombre);
                break;
            }
                
            case 2:{
                char apellidos[40];
                cout<<"\nIngrese los nuevos apellidos del paciente: ";
                cin.ignore();
                cin.getline(apellidos, 40);
                strcpy(nodoPaciente->paciente.apellidos, apellidos);
                break;
            }
            case 3:{
                int edad = 0;
                cout<<"\nIngrese la nueva edad del paciente: ";
                cin>>edad;
                nodoPaciente->paciente.edad = edad;
                break;
            }
            case 4:{
                char enfermedad[40];
                cout<<"\nIngrese la nueva enfermedad del paciente: ";
                cin.ignore();
                cin.getline(enfermedad, 40);
                strcpy(nodoPaciente->paciente.enfermedad, enfermedad);
                break;
            }
            case 5:{
                int prioridad;
                cout<<"\nIngrese el nuevo nivel de prioridad del paciente: ";
                cin>>prioridad;
                nodoPaciente->paciente.prioridad = prioridad;
                break;
            }
            case 6:{
                int estadoRevision;
                cout<<"\nIngrese el nuevo estado de revisión del paciente: ";
                cin>>estadoRevision;
                nodoPaciente->paciente.estadoRevision = estadoRevision;
                break;
            }
            case 7:
                cout<<"\nOperación cancelada con éxito";
                break;
            default:
                cout<<"ERROR: Ingrese un número válido en el rango dado.";
                break;
        }
        if(opcMenu>=1 && opcMenu<=6){
            cout<<"\nInformación actualizada con éxito";
            printPaciente(nodoPaciente);

            cout<<"\n¿Desea modificar otro dato de '"<< nodoPaciente->paciente.nombre << " " <<nodoPaciente->paciente.apellidos <<"' con NSS: "<< nodoPaciente->paciente.nss <<"?";
            cout<<"\n1.- Si";
            cout<<"\n2.- No";
            cout<<"\nIngrese el número de la operación a realizar: ";
            cin>>opcVolverModifi;
            if(opcVolverModifi == 1){
                repModificar = true;
            }else{
                repModificar = false;
            }
        }

    }while(repModificar);
}

void deletePaciente(){
    if(headPaciente == NULL){
        cout<<"\nNo hay pacientes registrados, vaya al menú 'Registrar paciente'";
        return;
    }

    char nss[11];
    cout<<"\n\n=======================================";
    cout<<"\nEliminar paciente";
    cout<<"\n=======================================";
    cout<<"\n\nIngrese el NSS del paciente a eliminar: ";
    cin>>nss;

    bool pacienteBorrado = deletePacienteByNSS(nss);
    if(deletePacienteByNSS){
        cout<<"El paciente con NSS: " << nss << " fue eliminado con éxito";
    }else{
        cout<<"No se encontró al paciente con NSS: " << nss << "\nIntente con otro NSS.";
    }
    
}

void findPaciente(){
    if(headPaciente == NULL){
        cout<<"\nNo hay pacientes registrados, vaya al menú 'Registrar paciente'";
        return;
    }

    char nss[11];
    cout<<"\n\n=======================================";
    cout<<"\nConsultar paciente";
    cout<<"\n=======================================";
    cout<<"\n\nIngrese el NSS del paciente a consultar: ";
    cin>>nss;

    NodoPaciente* nodoPaciente = getPacienteByNSS(nss);
    if(nodoPaciente == NULL){
        cout<<"\nNo se encontró al paciente con NSS: "<< nss << "\nIntente con otro NSS.";
        return;
    }else{
        printPaciente(nodoPaciente);
    }
}


void findAllPacientes()
{
    if(headPaciente == NULL)
    {
        cout << "\nNo hay pacientes registrados, vaya al menú 'Registrar paciente'";
        return;
    }
    cout << "\n\n========================================";
    cout << "\nLISTADO DE PACIENTES";
    cout << "\n========================================\n";
    NodoPaciente* temp = headPaciente;

    while(temp != NULL)
    {
        printPaciente(temp);
        temp = temp->siguiente;
    }

    cout << "\n========================================\n";
}

NodoPaciente* getPacienteByNSS(char nssPaciente[11]){
    NodoPaciente* aux = headPaciente;

    while(aux != NULL){
        if(strcmp(aux->paciente.nss, nssPaciente) == 0){
            return aux;
        }
        aux = aux->siguiente;
    }

    return NULL;
}

bool deletePacienteByNSS(char nssPaciente[11]){
    //Para la lista vacía
     if(headPaciente == NULL){
        return false;
    }

    // Caso especial: borrar el primero
    if(strcmp(headPaciente->paciente.nss, nssPaciente) == 0){
        NodoPaciente* temp = headPaciente;
        headPaciente = headPaciente->siguiente;
        free(temp);
        return true;
    }

    NodoPaciente* aux = headPaciente;
    while(aux->siguiente != NULL){
        if(strcmp(aux->siguiente->paciente.nss, nssPaciente) == 0){
            NodoPaciente* temp = aux->siguiente;
            aux->siguiente = temp->siguiente;
            free(temp);
            return true;
        }
        aux = aux->siguiente;
    }

    return false;
}

void printPaciente(NodoPaciente* paciente){
    cout << "\n-----------------------------------------";
    cout << "\n" << paciente->paciente.nombre << " " << paciente->paciente.apellidos;
    cout << "\n-----------------------------------------";

    cout << "\nNombre(s): "<< paciente->paciente.nombre;
    cout << "\nApellidos: "<< paciente->paciente.apellidos;
    cout << "\nEdad: " << paciente->paciente.edad;
    cout << "\nNSS: " << paciente->paciente.nss;
    cout << "\nEnfermedad: " << paciente->paciente.enfermedad;
    cout << "\nPrioridad: " << getNivelPrioridad(paciente->paciente.prioridad);
    cout << "\nEstado: " << getEstadoRevision(paciente->paciente.estadoRevision);
    cout << "\n";
}

const char* getNivelPrioridad(int prioridad)
{
    switch(prioridad)
    {
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

const char* getEstadoRevision(int estadoRevision)
{
    switch(estadoRevision)
    {
        case 0:
            return "SIN CITA";

        case 1:
            return "EN LISTA DE ESPERA";

        case 2:
            return "EN CONSULTA";

        case 3:
            return "ATENDIDO";

        case 4:
            return "CANCELADO";

        default:
            return "DESCONOCIDA";
    }
}