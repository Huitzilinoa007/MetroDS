#include<iostream>
#include "menu.h"
#include "../paciente/paciente.h"
#include "../consultorio/consultorio.h"
#include "../atencion/atencion.h"

using namespace std;

void menuPrincipal(){
    bool verifi = true;
    do{
        cout<<"\n\n=================================";
        cout<<"\nISSSTEC";
        cout<<"\nInstituto de Servicios de Software y Sistemas Tecnológicos";
        cout<<"\n=================================";
        cout<<"\n\n1.- Pacientes";
        cout<<"\n2.- Consultorios";
        cout<<"\n3.- Atención médica";
        cout<<"\n4.- Consultas";
        cout<<"\n5.- Ordenamientos";
        cout<<"\n6.- Estadísticas";
        cout<<"\n7.- Historial";
        cout<<"\n8.- Salir\n\nIngrese el número del menú al que desea ingresar: ";

        int opc = 0;
        cin>>opc;
        switch (opc){
        case 1:
            menuPacientes();
            break;    
        case 2:
            menuConsultorios();
            break;
        case 3:
            menuAtencionMedica();
            break;
        case 4:
            menuConsultas();
            break;
        case 5:
            menuOrdenamientos();
            break;
        case 6:
            menuEstadisticas();
            break;
        case 7:
            menuHistorial();
            break;
        case 8: 
            cout<<"\n\n=================================";
            cout<<"\nFin del programa";
            cout<<"\n=================================\n";
            verifi = false;
            break;
        default:
            cout<<"ERROR: Ingrese un valor en el rango dado.";
            verifi = false;
            break;
        }
    }while(verifi);
}


//Los cout's sólo los puse para probar que funcione
//se los puedes quitar después, va?
void menuPacientes(){
    bool verifi;
    do{
        cout<<"\n\n=================================";
        cout<<"\nPacientes";
        cout<<"\n=================================";
        cout<<"\n\n1.- Registrar paciente";
        cout<<"\n2.- Modifiar paciente";
        cout<<"\n3.- Eliminar paciente";
        cout<<"\n4.- Consultar paciente";
        cout<<"\n5.- Mostrar todos los pacientes";
        cout<<"\n6.- Salir\n\nIngrese el número de la operación que desea realizar: ";
        cout<<"";

        int opc = 0;
        cin>>opc;

        switch (opc){
        case 1:
            insertPaciente();
            break;
        case 2:
            updatePaciente();
            break;
        case 3:
            deletePaciente();
            break;
        case 4:
            findPaciente();
            break;
        case 5:
            findAllPacientes();
            break;
        case 6:
            verifi = false;
            break;
        default:
            verifi = false;
            break;
        }

    }while(verifi);
}

void menuConsultorios(){
    bool verifi;
    createConsultorios();
    do{
        cout<<"\n\n=================================";
        cout<<"\nConsultorios";
        cout<<"\n=================================";
        cout<<"\n\n1.- Registrar consultorio";
        cout<<"\n2.- Modificar consultorio";
        cout<<"\n3.- Buscar consultorio";
        cout<<"\n4.- Mostrar todos los consultorios";
        cout<<"\n5.- Salir\n\nIngrese el número de la operación que desea realizar: ";
        cout<<"";

        int opc = 0;
        cin>>opc;

        switch (opc){
        case 1:
            insertConsultorio();
            break;
        case 2:
            updateConsultorio();
            break;
        case 3:
            findConsultorio();
            break;
        case 4:
            findAllConsultorios();
            break;
        case 5:
            verifi = false;
            break;
        default:
            verifi = false;
            break;
        }

    }while(verifi);
}
void menuAtencionMedica(){
    bool verifi;
    createConsultorios();
    do{
        cout<<"\n\n=================================";
        cout<<"\nAtención médica";
        cout<<"\n=================================";
        cout<<"\n\n1.- Agregar paciente a la lista de espera";
        cout<<"\n2.- Atender paciente";
        cout<<"\n3.- Finalizar consulta";
        cout<<"\n4.- Mostrar lista de espera";
        cout<<"\n5.- Salir\n\nIngrese el número de la operación que desea realizar: ";
        cout<<"";

        int opc = 0;
        cin>>opc;

        switch (opc){
        case 1:
            agregarACola();
            break;
        case 2:
            atenderPaciente();
            break;
        case 3:
            finalizarConsulta();
            break;
        case 4:
            mostrarColaEspera();
            break;
        case 5:
            verifi = false;
            break;
        default:
            verifi = false;
            break;
        }

    }while(verifi);
}
void menuConsultas(){
    cout<<"Consultas";
}
void menuOrdenamientos(){
    cout<<"Ordenamientos";
}
void menuEstadisticas(){
    cout<<"Estadísticas";
}
void menuHistorial(){
    cout<<"Historial";
}
