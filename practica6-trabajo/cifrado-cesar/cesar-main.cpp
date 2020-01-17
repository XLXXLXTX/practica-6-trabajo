#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

//Para los caracteres especiales como ñ o Ñ
// Añade paquete de idiomas
//#include <locale.h>
//#include <windows.h>

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
    
    system("CLS");
    
    switch(opcion){
        case 1: prepararCifrarTexto();
                break;
        case 2: prepararDescifrarTexto();
                break;        
        case 3: descifrarAutomaticamente();
                break;
        case 4: prepararAnalizarAutomaticamente();
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
 */
void iterarMenu(){

    int opcion;
    do{
        mostrarMenu();
        
        cout << "Introduzca el numero de la operacion deseada: ";
        cin >> opcion;
        
        if(opcion >=1 && opcion <= 4){
            
            elegirOpcion(opcion);
            
            //PONER UN: Pulsa una tecla para volver al menu...
            //Igual usar un system(PAUSE) o algo asi y despues
            //usar un system(CLS) para limpiar pantalla de la ultima opcion hecha
            
            system("pause");
            
            system("CLS");
        }
        
        if( !(opcion >=1 && opcion <= 4) ){
            cerr << "Debe seleccionar una opcion del menu. " << endl;
        }
    
    }while(opcion != 0 );
}


/**
 * Metodo main del programa
 * 
 * PRE:     Para el correcto funcionamiento del programa main, debe exitir una serie
 *          de archivos alojados en la carpeta datos que esta situada en la raiz del proyecto,
 *          llamados: diccionario.txt en el que esten contenidas todas las palabras 
 *          que empiezan desde la letra "a" hasta la "z", y con el formato de una palabra
 *          por en cada linea del fichero. Tambien debe existir un fichero .txt con 
 *          un nombre cualquiera, para poder usarlo en la ejecucion de los diferente 
 *          opciones que tiene este programa.
 * POST:    Habiendose cumplido la precondicion, el programa propone 4 opciones en las 
 *          cuales, el archivo con un nombre cualquiera que introducira el usuario por teclado
 *          sera usado para hacer lo siguiente:
 *          -cifrar el texto de ese archivo de texto que introduce el usuario, con la clave que este elija 
 *          -descifrar el texto de ese archivo que introduce el usuario, con la clave que este elija 
 *          -descifrar automaticamente el archivo que el usuario introduce por teclado, 
 *           sin darle el usuario la clave con la que hacerla
 *          -analizar la probabilidad de todas las claves de cifrado cesar, que se pueden aplicar
 *           al texto cifrado del archivo, para poder descifrar la mayor o totalidad de su contenido 
 *           basandose en la palabras que se encuantran en el archivo diccionario, al descifrarlas 
 *           con una clave determinada.
 */
int main(){
    
    iterarMenu();
    
    return 0;

}