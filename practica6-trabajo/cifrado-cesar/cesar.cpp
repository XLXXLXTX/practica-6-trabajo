#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <pedir-nombre-fichero.h>
#include "cesar.h"

using namespace std;

/**
 * PRE:  Se le pasa una cadena de texto llamada linea, un entero llamado
 *       desplazamiento, otra cadena de texto llamada lineaTransformada y
 *       finalmente un char llamdo modo que sera el encargado de elegir que algoritmo
 *       usar: si el de cifrar o el de descifrar 
 * POST: funcion que se encarga de recibir una linea de texto y un valor
 *       de desplazamiento para cifrarla/descifrarla segund el valor del caracter
 *       <<modo>> y copiarla a la cadena de lineaTransformada
 */
void cifrarODescifarLinea(const char linea [], int desplazamiento, char lineaTransformada [], const char modo){
    //Seleccion del algoritmo para cifrar o descifrar el archivo
    int algoritmo;
    
    if(modo == MODO_CIFRAR){
        algoritmo = desplazamiento;
    }if(modo == MODO_DESCIFRAR){
        algoritmo = 26 - desplazamiento;
    }

    lineaTransformada[strlen(linea)] = '\0';
    
    //Bucle para recorrer cada caracter
    for (int i=0; linea[i] != '\0'; i++){
        char c = linea[i];
        if('a' <= c && c <= 'z'){
            lineaTransformada[i] = 'a' + ( (c - 'a' + algoritmo) % 26);
        }else if('A' <= c && c <= 'Z'){
            lineaTransformada[i] = 'A' + ( (c - 'A' + algoritmo) % 26);
        }else{
            lineaTransformada[i] = c;
        }
    }
}

//----------------------------------------------------------------------------------------------------
/**
 * PRE:  ---
 * POST: ---
 */
 void pedirDatos(const int opcion, int& claveDesplazamiento, char origenUsu [], char destinoUsu []){
     
     //Establecemos las variables donde se va a montar la ruta + nombreFichero
    //que va a dar el ususario en el metodo "pedirFichero()"
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    strcpy(rutaOrigen, DIR_DATOS);
    strcpy(rutaDestino, DIR_RESULTADOS);
    
    //Llamamos a la funcion de pedirFichero para leer el archivo de teclado
    //del ususario y la clave dependiendo de la opcion que se elija se daran 
    //unos valores u otros
    switch(opcion){
        case 1: pedirNombreFichero(MSJ_OPC_1, SUFIJO_CIFRADO, rutaOrigen, rutaDestino);
                cout << MSJ_CLAVE;
                cin >> claveDesplazamiento;
                break;
        case 2: pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_DESCIFRADO, rutaOrigen, rutaDestino);
                cout << MSJ_CLAVE;
                cin >> claveDesplazamiento;
                break;
        case 3: pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_DESCIFRADO, rutaOrigen, rutaDestino);
                claveDesplazamiento = CLAVE_SEGUN_ANALISIS;
                break;
        case 4: pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_DESCIFRADO, rutaOrigen, rutaDestino);
                break;
    }
    
    //Establecemos las variables donde se va a montar la ruta + nombreFichero
    //que va a dar el ususario en el metodo "pedirFichero()"
    strcpy(origenUsu, rutaOrigen);
    strcpy(destinoUsu, rutaDestino);
 }

//----------------------------------------------------------------------------------------------------

/**
 * PRE: ---
 * POST: funcion que se encarga de englobar todas las ordenes necesarias 
 *       para cifrar un texto, opcion 1 del menu, sabiendo la clave de 
 *       desplazamiento y el nombre del fichero (que debe estar en la carpeta  
 *       <<datos>>). Una vez acabado, el archivo cifrado se encuentra en 
 *       la carpeta <<resultados>> y con el nombre del archivo acabado en 
 *       "-cifrado". Si algunoo error se produce durante la lectura o 
 *       escritura del archivo original/cifrado se muestra por pantalla 
 *       un error especificando el fallo. 
 */
 void cifrarTexto(const int claveDesplazamiento, const char rutaOrigen [], const char rutaDestino []){
//void cifrarTexto(){
    //Establecemos las variables donde se va a montar la ruta + nombreFichero
    //que va a dar el ususario en el metodo "pedirFichero()"
//    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
//    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];

//    strcpy(rutaOrigen, DIR_DATOS);
//    strcpy(rutaDestino, DIR_RESULTADOS);
    
    //Llamamos a la funcion de pedirFichero para leer el archivo de teclado
    //del ususario
//    pedirNombreFichero(MSJ_OPC_1, SUFIJO_CIFRADO, rutaOrigen, rutaDestino);


    //Establecemos las variables donde se va a montar la ruta + nombreFichero
    //que va a dar el ususario en el metodo "pedirFichero()"
//    cout << MSJ_CLAVE;
//    int claveDesplazamiento;
//    cin >> claveDesplazamiento;


    //Se procede a abrir el archivo indicado por el ususario
    ifstream ficheroOriginal;
    ficheroOriginal.open(rutaOrigen);
    
    if(!ficheroOriginal.is_open()){
        cerr << ERROR_FICH_ORIGEN << rutaOrigen << "'" << endl;
    }else{
        ofstream ficheroDestino;
        ficheroDestino.open(rutaDestino);
        
        if(!ficheroDestino.is_open()){
            cerr << ERROR_FICH_DESTINO << rutaDestino << "'" << endl;
        }else{
            cout << endl;
            //Aqui ya empezariamos a leer una linea del fichero
            //cifrarla y copiarla al fichero de destino 
            char lineaACifrar [MAX_LONG_LINEA];
            ficheroOriginal.getline(lineaACifrar, MAX_LONG_LINEA);
            
            char cifrada [MAX_LONG_LINEA];
            
            while(!ficheroOriginal.eof()){
                char vacia [MAX_LONG_LINEA] = "";
                strcpy(cifrada, vacia);
                
                //FALTA SOLUCIONAR COMO LIDIAR CON LAS TABULACIONES YA QUE NO SE PUEDEN CONTAR COMO VARIOS ESPACIOS JUNTOS ???
                cifrarODescifarLinea(lineaACifrar, claveDesplazamiento, cifrada, MODO_CIFRAR);
                
                ficheroDestino << cifrada << endl;
                
                strcpy(lineaACifrar, vacia);
                ficheroOriginal.getline(lineaACifrar, MAX_LONG_LINEA);
                
            }
            
            cout << MSJ_EXITO_PT1 << rutaOrigen << MSJ_EXITO_C_PT2 << claveDesplazamiento << MSJ_EXITO_PT3<< rutaDestino << "'" << endl;
        }
        ficheroDestino.close();
    }
    ficheroOriginal.close();
}


/**
 * PRE:  Se le pasa la constate con nombre clave, donde se le puede pasar 
 *       la clave con la que se va a descifrar si se invoca a esta funcion
 *       desde otro metodo o dejar que el usuario introduzaca la que el 
 *       quiera por teclado mas adelante en la ejecucion de esta funcion. 
 *       Se la clave con la que se va a decifrar ya se sabe y no es necesario 
 *       que el usuario la escirba por teclado, tambien se le pasa la cedana de 
 *       caracteres de la rutaDestinoConocida y rutaOrigenConocida para evitar 
 *       que tenga que volver a introducirlocomo pasaba con la clave.
 * POST: funcion que se encarga de englobar todas las ordenes necesarias 
 *       para descifrar un texto, opcion 2 del menu, sabiendo la clave de 
 *       desplazamiento y el nombre del fichero (que debe estar en la carpeta  
 *       <<datos>>). Una vez acabado, el archivo descifrado se encuentra en 
 *       la carpeta <<resultados>> y con el nombre del archivo acabado en 
 *       "-descifrado". Si algunoo error se produce durante la lectura o 
 *       escritura del archivo original/descifrado se muestra por pantalla 
 *       un error especificando el fallo. 
 */
//void descifrarTexto(const int clave, const char rutaOrigenConocida [], const char rutaDestinoConocida []){
//void descifrarTexto(){
void descifrarTexto(const int claveDesplazamiento, const char rutaOrigen [], const char rutaDestino []){
    
//    int claveDesplazamiento;
//    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
//    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
//    
//    pedirDatos(2, claveDesplazamiento, rutaOrigen, rutaDestino);
//    
//    
//    if(clave == CLAVE_SEGUN_USUARIO){
//        strcpy(rutaOrigen, DIR_DATOS);
//        strcpy(rutaDestino, DIR_RESULTADOS);
//    
//        pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_DESCIFRADO, rutaOrigen, rutaDestino);
//    
//        cout << MSJ_CLAVE;
//        cin >> claveDesplazamiento;
//    }else{
//        strcpy(rutaOrigen, rutaOrigenConocida);
//        strcpy(rutaDestino, rutaDestinoConocida);
//        claveDesplazamiento = clave;
//    }
    
    ifstream ficheroOriginal;
    ficheroOriginal.open(rutaOrigen);
    
    if(!ficheroOriginal.is_open()){
        cerr << ERROR_FICH_ORIGEN << rutaOrigen << "'" << endl;
    }else{
        ofstream ficheroDestino;
        ficheroDestino.open(rutaDestino);
        
        if(!ficheroDestino.is_open()){
            cerr << ERROR_FICH_DESTINO << rutaDestino << "'" << endl;
        }else{
            cout << endl;
            
            char lineaADescifrar [MAX_LONG_LINEA];
            ficheroOriginal.getline(lineaADescifrar, MAX_LONG_LINEA);
            
            char descifrada [MAX_LONG_LINEA];
            
            while(!ficheroOriginal.eof()){
                char vacia [MAX_LONG_LINEA] = "";
                strcpy(descifrada, vacia);
                    
                cifrarODescifarLinea(lineaADescifrar, claveDesplazamiento, descifrada, MODO_DESCIFRAR);
                
                ficheroDestino << descifrada << endl;
                    
                strcpy(lineaADescifrar, vacia);
                ficheroOriginal.getline(lineaADescifrar, MAX_LONG_LINEA);
                
            }
            cout << MSJ_EXITO_PT1 << rutaOrigen << MSJ_EXITO_D_PT2 << claveDesplazamiento << MSJ_EXITO_PT3<< rutaDestino << "'" << endl;
        }
        ficheroDestino.close();
    }
    ficheroOriginal.close();
}


void prepararCifrarTexto(){
    
    int claveDesplazamiento;
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    pedirDatos(1, claveDesplazamiento, rutaOrigen, rutaDestino);
    
    cifrarTexto(claveDesplazamiento, rutaOrigen, rutaDestino);
}

void prepararDescifrarTexto(){
    
    int claveDesplazamiento;
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    pedirDatos(2, claveDesplazamiento, rutaOrigen, rutaDestino);
    
    descifrarTexto(claveDesplazamiento, rutaOrigen, rutaDestino);
}


