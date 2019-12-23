#include <stdio.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <cmath>

//------------------
#include <string>
#include <sstream>
//------------------



#include <diccionario.h>
#include <pedir-nombre-fichero.h>
#include <cesar.h>
#include "analisis-cesar.h"

using namespace std;


/**
 * PRE: ----
 * POST: Muestra por pantalla un listado con el formato mas adecuado para que 
 *       que el usuario visualice la lista de las 26 claves posibles a usar 
 *       para descifrar el fichero, con un porcentaje de exito y el numero 
 *       total de palabras de cada clave que son reconocidas en el archivo 
 *       diccionario.dic
 */
void mostrarListadoClaves(const Clave infoClaves []){
    
    //Habria que pasarle una lista de registros
    //que tuviese los campos de 
    //-Clave
    //-Palabras reconocidas en el diccionario.dic
    //-Porcentaje en entre las palabras reconocias den el diccionario
    //y el total de palabras en el archivo
    
    
    cout << "---------------------------" << endl;
        
    cout << setw(MIN_ANCHO*2) 
         << "Clave" << setw(MIN_ANCHO*3) 
         << "Palabras" << setw(MIN_ANCHO*4) 
         << "Porcentaje " 
         << endl;
         
    cout << "---------------------------" << endl;  
    
    for(int i=0; i<TOTAL_CLAVES; i++){
        cout << fixed;
        cout << setw(MIN_ANCHO*2)
             << infoClaves[i].valor << setw(MIN_ANCHO*3) 
             << infoClaves[i].numPalabras << setw(MIN_ANCHO*4) 
             << setprecision(1)
             << infoClaves[i].porcentaje << " %" << endl;
//             << "16" << setw(MIN_ANCHO*3) 
//             << "274" << setw(MIN_ANCHO*4) 
//             << "0.1 %" << endl;
    }
}

/**
 * PRE: ---
 * POST: funcion que se encarga de probar la clave k (0 <= k < 26) y crear el archivo temporal
 *       decifrado en esa clave para usarlo mas adelante 
 */
void ejecutarFuerzaBruta(Clave claveAIntentar, istream& fOriginal, ofstream& fTemp){
    
    //------------------------------------------------------
    int k = claveAIntentar.valor;
    stringstream  nomArchivo;
    string extensionArchivo = ".txt";
//    char fileNombre [400];
    
    string claveString(1, char(k));
//    h += ".txt";
    
//    strcpy(fileNombre, nomArchivo);
    
//    strcat(fileNombre, claveString );
    
    nomArchivo << "D:/temporalesPractica6/archivoDescifrado-clave-" << k << extensionArchivo;
    
//    strcat(fileNombre, extensionArchivo);
    
    cout << "nomArchivo --> " << nomArchivo.str() << endl; 
    
    ofstream archivoDescifrado(nomArchivo.str());
    
    
    //------------------------------------------------------
    
    
    
    
    
    //Aqui tendriamos que probar el valor que viene en claveAIntentar.valor
    //transformar el fichero con esa clave
    int clave = claveAIntentar.valor;
    
//    cout << "CLAVE EN ejecutarFuerzaBruta: " << clave << endl;
    
    char lineaADescifrar [200];
    fOriginal.getline(lineaADescifrar, 200);
            
    char descifrada [200];
            
    while(!fOriginal.eof()){
        char vacia [200] = "";
        strcpy(descifrada, vacia);
                    
        cifrarODescifarLinea(lineaADescifrar, clave, descifrada, MODO_DESCIFRAR);
                
        fTemp << descifrada << endl;
        
    //------------------------------------------------------                
        if(archivoDescifrado.is_open()){
            archivoDescifrado << descifrada << endl;
        }            
    //------------------------------------------------------                           
                    
        strcpy(lineaADescifrar, vacia);
        fOriginal.getline(lineaADescifrar, 200);
                
    }
    
    archivoDescifrado.close();
}


/**
 * PRE: ---
 * POST: funcion que se encarga de analizar el archivo temporal creado para la clave k (0 <= k < 26) 
 *       a traves de la busqueda de palabras en el archivo diccionario.dicc
 */
void analizarFuerzaBruta(Clave& claveAIntentar, const char rutaTemp[]){
    int encontradas = 0;
    int noEncontradas = 0;
    contarPalabras(rutaTemp, encontradas, noEncontradas);
    
    cout << "Clave: " << claveAIntentar.valor << "----> Encontradas: " << encontradas << " No encontradas: " << noEncontradas << endl;
    double porcentaje = ( encontradas / ( (double) (encontradas + noEncontradas) ) ) * 100;
    
    if(isnan(porcentaje)){
        porcentaje = 0.00;
    }
    
    claveAIntentar.numPalabras = encontradas;
    claveAIntentar.porcentaje = porcentaje;
    
}


/**
 * PRE: ---
 * POST: funcion que se encarga de englobar todas las ordenes necesarias 
 *       para hacer el analisis de todas las posibles clave k (0 <= k < 26), 
 *       opcion 4 del menu, sabiendo el nombre del fichero (que debe estar 
 *       en la carpeta <<datos>>). Una vez acabado, se muestra por pantalla 
 *       el resultado de la funcion mostrarListadoClaves(), Si algunoo error
 *       se produce durante la lectura o escritura del archivo original/cifrado 
 *       se muestra por pantalla un error especificando el fallo.
 */
void analizarClavesAutomaticamente(){
    
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaOrigen, DIR_DATOS);
    strcpy(rutaDestino, RUTA_TEMP);
    
    pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_TEMP, rutaOrigen, rutaDestino);
    
    ifstream ficheroOriginal;
    ficheroOriginal.open(rutaOrigen);
    
    //Definimos el vector de registros de tipo Clave, donde se van a guardar la informacion
    //de las pruebas que se hara de las claves k (0 <= k < 26) 
    Clave datosClave [TOTAL_CLAVES];
    
    if(!ficheroOriginal.is_open()){
        cerr << ERROR_FICH_ORIGEN << rutaOrigen << "'" << endl;
    }else{
        
        //Hay que crear un fichero para cada clave
        
        for(int i=15; i<TOTAL_CLAVES; i++){
            
            //Abro el fichero del temporal de la clave k=i
            //tanto como escritura porque es donde voy a escribir el texto cifrado con la clave k
            //como para lectura ya que luego voy a leer las palabras que reconoce al aplicar 
            //laa clave k al descifrar el ficheroOriginal
            
            ofstream ficheroTemp;
//            fstream ficheroTemp
//            ficheroTemp.open(rutaDestino, ios::in|ios:: out);
            ficheroTemp.open(rutaDestino);
            
            if(!ficheroTemp.is_open()){
                cerr << ERROR_FICH_DESTINO << rutaDestino << "'" << endl;
            }else{
//                    cout << "Valor de i: " << i << endl;
                    
                    datosClave[i].valor = i;
                    
//                    cout << "Valor de datosClave[i].valor: " << datosClave[i].valor << endl;
                    
                    //Fuerza bruta con el valor de k = i
                    ejecutarFuerzaBruta(datosClave[i], ficheroOriginal, ficheroTemp);
                    
                    //Ahora que ya tenemos el fichero temporal de la clave con valor k = i
                    //podriamos leerlo para sacar las palabras y porcentaje con el diccionario
                    //y ya tendriamos un pocision del vector de datosClave rellenado.
                    //leer todas las palabras 
                    //leer cuales de ellas esta en el diccionario
                    //sacar el porcentaje de encontradas
                    //modificar claveAIntenrar.palabras y claveAIntentar.porcentaje 
                    
                    //Aprovechamos que el flujo es tambien de lectura para el fichero temporal 
                    //donde se ha escrito el contenido descifrado con la funcion ejecutarFuerzaBruta()
                    analizarFuerzaBruta(datosClave[i], rutaDestino);
                    
                    
            }
            //Cerramos el flujo de escritura del archivo ya que no nos va a hacer falta volver a escribir en el 
            ficheroTemp.close();
            
            //Ahora borramos el archivo temporal
            if(remove(rutaDestino) == 0){
                cout << "Fichero temporal borrado " << endl;
            }else{
                cout << "Fichero temporal NO borrado " << endl;
            }
        }
        ficheroOriginal.close();
    }
    
    mostrarListadoClaves(datosClave);
}