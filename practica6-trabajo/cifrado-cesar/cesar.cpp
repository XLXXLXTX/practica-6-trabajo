#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <pedir-nombre-fichero.h>
#include "cesar.h"

using namespace std;


/**
 * PRE:  Se le pasa una cadena de texto llamada linea, un entero llamado
 *       desplazamiento y u otra cadena de texto llamada lineaCifrada.
 * POST: funcion que se encarga de recibir una linea de texto y un valor
 *       de desplazamiento para cifrarla y copiarla a la cadena de lineaCifrada
 */
void cifrarLinea(const char linea [], int desplazamiento, char lineaCifrada []){
     
    //---------------------------
//    cout << "linea" << endl;
//    cout << linea << endl;
    
    lineaCifrada[strlen(linea)] = '\0';
   
    int posicionAlfabeto;
    bool buscando;

    //Bucle para recorrer cada caracter
    for (int i=0; linea[i] != '\0'; i++){
        
        posicionAlfabeto = 0;
        buscando = true;
        
        //Bucle para comparar si ese caracter esta en el vector de letras a cifrar
        while( (posicionAlfabeto < strlen(ALFABETO_MINUS)) && buscando){
            if( strchr(NO_CIFRAR, linea[i]) ){
                lineaCifrada[i] = linea[i];
                buscando = false;
            }
            
            if( linea[i] == ALFABETO_MINUS[posicionAlfabeto] ){
                lineaCifrada[i] = ALFABETO_MINUS[(posicionAlfabeto + desplazamiento) % strlen(ALFABETO_MINUS)];
                buscando = false;
            }
            if( linea[i] == ALFABETO_MAYUS[posicionAlfabeto] ){
                lineaCifrada[i] = ALFABETO_MAYUS[(posicionAlfabeto + desplazamiento) % strlen(ALFABETO_MAYUS)];
                buscando = false;
            }
 
            posicionAlfabeto++;
        }
    }
    
    //---------------------------
//    cout << "cifrada" << endl;
//    cout << lineaCifrada << endl;
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
                cifrarLinea(lineaACifrar, claveDesplazamiento, cifrada);
                
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
 * PRE:  Se le pasa una cadena de texto llamada linea, un entero llamado
 *       desplazamiento y u otra cadena de texto llamada lineaDescifrada.
 * POST: funcion que se encarga de recibir una linea de texto y un valor
 *       de desplazamiento para descifrarla y copiarla a la cadena de lineaDescifrada
 */
void descifrarLinea(const char linea [], int desplazamiento, char lineaDescifrada []){
         
    //---------------------------
//    cout << "linea" << endl;
//    cout << linea << endl;
    
    lineaDescifrada[strlen(linea)] = '\0';
   
    int posicionAlfabeto;
    bool buscando;

    //Bucle para recorrer cada caracter
    for (int i=0; linea[i] != '\0'; i++){
        
        posicionAlfabeto = 0;
        buscando = true;
        
        //Bucle para comparar si ese caracter esta en el vector de letras a cifrar
        while( (posicionAlfabeto < strlen(ALFABETO_MINUS)) && buscando){
            if( strchr(NO_CIFRAR, linea[i]) ){
                lineaDescifrada[i] = linea[i];
                buscando = false;
            }
            
            if( linea[i] == ALFABETO_MINUS[posicionAlfabeto] ){
                lineaDescifrada[i] = ALFABETO_MINUS[(posicionAlfabeto + (26 - desplazamiento ) ) % strlen(ALFABETO_MINUS)];
                buscando = false;
            }
            if( linea[i] == ALFABETO_MAYUS[posicionAlfabeto] ){
                lineaDescifrada[i] = ALFABETO_MAYUS[(posicionAlfabeto + (26 - desplazamiento ) ) % strlen(ALFABETO_MAYUS)];
                buscando = false;
            }
 
            posicionAlfabeto++;
        }
    }
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
    
    pedirNombreFichero(MSJ_OPC_2, SUFIJO_DESCIFRADO, rutaOrigen, rutaDestino);

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
                
            
            descifrarLinea(lineaADescifrar, claveDesplazamiento, descifrada);
            
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



