/********************************************************************************\
 * Programación 1. Práctica 6: Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 17 de Enero de 2020
 * Resumen: Fichero cesar.cpp del proyecto "cifrado-cesar"
\********************************************************************************/
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


/**
 * PRE:  Funcion a la que se le pasa:
 *       opcion: valor de la opcion elegida por el ususario.
 *       claveDesplazamiento: variable donde se guardara la clave, si es 
 *       necesario que el ususario la introduzca por pantalla para el 
 *       para el desarrollo de la opcion.
 *       origenUsu: variable donde guardar ruta del fichero a manipular
 *       si es necesario que el usuario lo ingrese por teclado.
 *       destinoUsu: variable donde guardar ruta del fichero de destino
 * POST: Funcion en la que dependiendo de la opcion, se le dan los valores
 *       que el usuario introduce, a las variables que recibe el metodo,
 *       para facilitar la organizacion de los datos que se envian a 
 *       cada metodo de las opciones 
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


/**
 * PRE:  Funcion a la que se le pasan tres constantes:
 *       <<claveDesplzamiento>>: clave para el cifrado.
 *       <<rutaOrigen>>: ruta de origen del fichero a cifrar
 *       <<rutaDestino>>: ruta de destino del fichero cifrado
 * POST: funcion que se encarga de englobar todas las ordenes necesarias 
 *       para cifrar un texto, opcion 1 del menu, sabiendo <<claveDesplazamiento>>
 *       y el la <<rutaOrigen>> del fichero. Una vez acabado, 
 *       el archivo cifrado se encuentra en la <<rutaDestino>> y con
 *       el nombre del archivo acabado en "-cifrado". Si algunoo error 
 *       se produce durante la lectura o escritura del archivo original/cifrado
 *       se muestra por pantalla un error especificando el fallo. 
 */
 void cifrarTexto(const int claveDesplazamiento, const char rutaOrigen [], const char rutaDestino []){

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
 * PRE:  Funcion a la que se le pasan tres constantes:
 *       <<claveDesplzamiento>>: clave para el descifrado.
 *       <<rutaOrigen>>: ruta de origen del fichero a descifrar
 *       <<rutaDestino>>: ruta de destino del fichero descifrado
 * POST: funcion que se encarga de englobar todas las ordenes necesarias 
 *       para descifrar un texto, opcion 2 del menu, sabiendo <<claveDesplazamiento>>
 *       y el la <<rutaOrigen>> del fichero. Una vez acabado, 
 *       el archivo descifrado se encuentra en la <<rutaDestino>> y con
 *       el nombre del archivo acabado en "-descifrado". Si algunoo error 
 *       se produce durante la lectura o escritura del archivo original/descifrado
 *       se muestra por pantalla un error especificando el fallo. 
 */
void descifrarTexto(const int claveDesplazamiento, const char rutaOrigen [], const char rutaDestino []){
    
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


/**
 * PRE:  ---
 * POST: Funcion que se encarga de preparar los datos para 
 *       cifrar un fichero.
 */ 
void prepararCifrarTexto(){
    
    int claveDesplazamiento;
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    pedirDatos(1, claveDesplazamiento, rutaOrigen, rutaDestino);
    
    cifrarTexto(claveDesplazamiento, rutaOrigen, rutaDestino);
}

/**
 * PRE:  ---
 * POST: Funcion que se encarga de preparar los datos para 
 *       descifrar un fichero.
 */ 
void prepararDescifrarTexto(){
    
    int claveDesplazamiento;
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    pedirDatos(2, claveDesplazamiento, rutaOrigen, rutaDestino);
    
    descifrarTexto(claveDesplazamiento, rutaOrigen, rutaDestino);
}


