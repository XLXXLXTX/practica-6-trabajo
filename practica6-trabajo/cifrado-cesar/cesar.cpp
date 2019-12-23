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
void cifrarTexto(){
    //Establecemos las variables donde se va a montar la ruta + nombreFichero
    //que va a dar el ususario en el metodo "pedirFichero()"
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaOrigen, DIR_DATOS);
    strcpy(rutaDestino, DIR_RESULTADOS);
    
    //Llamamos a la funcion de pedirFichero para leer el archivo de teclado
    //del ususario
    pedirNombreFichero(MSJ_OPC_1, SUFIJO_CIFRADO, rutaOrigen, rutaDestino);


    //Establecemos las variables donde se va a montar la ruta + nombreFichero
    //que va a dar el ususario en el metodo "pedirFichero()"
    cout << MSJ_CLAVE;
    int claveDesplazamiento;
    cin >> claveDesplazamiento;


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
            char lineaACifrar [200];
            ficheroOriginal.getline(lineaACifrar, 200);
            
            char cifrada [200];
            
            while(!ficheroOriginal.eof()){
                char vacia [200] = "";
                strcpy(cifrada, vacia);
                
                //FALTA SOLUCIONAR COMO LIDIAR CON LAS TABULACIONES YA QUE NO SE PUEDEN CONTAR COMO VARIOS ESPACIOS JUNTOS ???
                cifrarODescifarLinea(lineaACifrar, claveDesplazamiento, cifrada, MODO_CIFRAR);
                
                ficheroDestino << cifrada << endl;
                
                strcpy(lineaACifrar, vacia);
                ficheroOriginal.getline(lineaACifrar, 200);
                
            }
            
            cout << MSJ_EXITO_PT1 << rutaOrigen << MSJ_EXITO_C_PT2 << claveDesplazamiento << MSJ_EXITO_PT3<< rutaDestino << "'" << endl;
        }
        ficheroDestino.close();
    }
    ficheroOriginal.close();
}


/**
 * PRE: ---
 * POST: funcion que se encarga de englobar todas las ordenes necesarias 
 *       para descifrar un texto, opcion 2 del menu, sabiendo la clave de 
 *       desplazamiento y el nombre del fichero (que debe estar en la carpeta  
 *       <<datos>>). Una vez acabado, el archivo descifrado se encuentra en 
 *       la carpeta <<resultados>> y con el nombre del archivo acabado en 
 *       "-descifrado". Si algunoo error se produce durante la lectura o 
 *       escritura del archivo original/descifrado se muestra por pantalla 
 *       un error especificando el fallo. 
 */
void descifrarTexto(){

    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaOrigen, DIR_DATOS);
    strcpy(rutaDestino, DIR_RESULTADOS);
    
    pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_DESCIFRADO, rutaOrigen, rutaDestino);

    cout << MSJ_CLAVE;
    int claveDesplazamiento;
    cin >> claveDesplazamiento;
    
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
            
            char lineaADescifrar [200];
            ficheroOriginal.getline(lineaADescifrar, 200);
            
            char descifrada [200];
            
            while(!ficheroOriginal.eof()){
                char vacia [200] = "";
                strcpy(descifrada, vacia);
                    
                cifrarODescifarLinea(lineaADescifrar, claveDesplazamiento, descifrada, MODO_DESCIFRAR);
                
                ficheroDestino << descifrada << endl;
                    
                strcpy(lineaADescifrar, vacia);
                ficheroOriginal.getline(lineaADescifrar, 200);
                
            }
            cout << MSJ_EXITO_PT1 << rutaOrigen << MSJ_EXITO_D_PT2 << claveDesplazamiento << MSJ_EXITO_PT3<< rutaDestino << "'" << endl;
        }
        ficheroDestino.close();
    }
    ficheroOriginal.close();
}



