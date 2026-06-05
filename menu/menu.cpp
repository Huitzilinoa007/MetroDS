#include<iostream>
#include "menu.h"

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
    cout<<"Pacientes";
}
void menuConsultorios(){
    cout<<"Consultorios";
}
void menuAtencionMedica(){
    cout<<"Atención médica";
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
