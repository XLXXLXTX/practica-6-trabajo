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
#include "analisis-cesar.h"

using namespace std;


/**
 * PRE:  ---
 * POST: Muestra por pantalla las posibles opciones del programa.  
 */
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

/**
 * PRE:  Se le pasa un entero como constante llamado opcion. 
 * POST: Segun el valor de la variable opcion, se llama al metodo que necesario 
 *       para la opcion seleccionada.
 */
void elegirOpcion(const int opcion){
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
        case 4: //cout << "llamando a la funcion analizarProbabilidad() ..." ;
                analizarClavesAutomaticamente();
                break;
    }
    cout << endl;
}

/**
 * PRE:  ---
 * POST: Metodo que muestra en bucle el menu de opciones del programa hasta que 
 *       se introduce por teclado el numero de una opcion valida (1-4), si se 
 *       introduce el valor 0, el programa finaliza. Mientras se introduzcan 
 *       valores fuera de los valores comprendido de n, siendo estos 0<= n <=4, 
 *       se mostrara un mensaje de error diciendo que la opcion no es valida.
 *       
 */
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