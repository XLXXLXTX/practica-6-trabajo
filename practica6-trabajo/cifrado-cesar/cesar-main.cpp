#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

//Para los caracteres especiales como ñ o Ñ
// Añade paquete de idiomas
#include <locale.h>
#include <windows.h>

//Para el system(CLS)
#include <stdlib.h>
//Incluimos el archivo con el metodo de pedir-nombre-fichero
#include "pedir-nombre-fichero.h"
#include "cesar.h"

using namespace std;

void mostrarMenu(){
    cout << "MENU DE OPERACIONES" << endl;
    cout << "===================" << endl;
    
    cout << "0 - Finalizar " << endl;
    cout << "1 - Cifrar un texto " << endl;
    cout << "2 - Descifrar un texto proporcionando la clave " << endl;
    cout << "3 - Descrifrar un texto automaticamente" << endl;
    cout << "4 - Analizar la probabilidad de las claves de un texto cifrado" << endl;
    cout << endl;
}

void elegirOpcion(int opcion){
    //Limpiamos la pantalla para que no se solape el menu con el mensaje de la opcion elegida
    //Funciona en la consola de windows
    system ("CLS");
    
    switch(opcion){
        //1 --> cifrarTexto()
        case 1: //cout << "llamando a la funcion cifrarTexto() ..." << endl;
                cifrarTexto();
                break;
        case 2: //cout << "llamando a la funcion descifrarConClave...";
                descifrarTexto();
                break;        
        case 3: cout << "llamando a la funcion descifradoAutomatico() ...";
                break;
        case 4: cout << "llamando a la funcion analizarProbabilidad() ..." ;
                break;
                
    }
    cout << endl;
}


void iterarMenu(){
    int opcion;
    do{
        mostrarMenu();
        
        cout << "Introduzca el numero de la operacion deseada: ";
        cin >> opcion;
        
        if(opcion >=1 && opcion <= 4){
            //Ejecutar las opciones de la lista
            //cout << "Ejecutando opcion del menu ..." << endl;
            
            //MANDAR EL NUMERO DE LA OPCION 
            //Y EN ESTE METODO CARGAR LO NECESARIO PARA ESA OPCION
            elegirOpcion(opcion);
            
        }
        
        if( !(opcion >=1 && opcion <= 4) ){
            cerr << "Debe seleccionar una opcion del menu. " << endl;
        }
    
    }while(opcion != 0 );
}


/**
 * Metodo main del programa
 */
int main(){
//    cifrarTexto();

    setlocale(LC_CTYPE, "Spanish"); // Cambiar locale - Suficiente para máquinas Linux
//    SetConsoleCP(1252); // Cambiar STDIN -  Para máquinas Windows
//    SetConsoleOutputCP(1252); // Cambiar STDOUT - Para máquinas Windows
    
//    setlocale(LC_ALL, "es_ES");
//    cout << "ñ Ñ " << endl;
//    cout << endl;
    iterarMenu();
    
    return 0;

}