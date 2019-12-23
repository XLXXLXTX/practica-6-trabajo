#ifndef ANALISIS_CESAR_H_INCLUDED
#define ANALISIS_CESAR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>

#include "pedir-nombre-fichero.h"

const int MIN_ANCHO = 3;
const int TOTAL_CLAVES = 26;
const char SUFIJO_TEMP [] = "-descifrado-temp";
const char RUTA_TEMP []= "./resultados/temp/";

using namespace std;

struct Clave {
    int valor;
    int numPalabras;
    double porcentaje;
};


/**
 * PRE: ----
 * POST: Muestra por pantalla un listado con el formato mas adecuado para que 
 *       que el usuario visualice la lista de las 26 claves posibles a usar 
 *       para descifrar el fichero, con un porcentaje de exito y el numero 
 *       total de palabras de cada clave que son reconocidas en el archivo 
 *       diccionario.dic
 */
void mostrarListadoClaves(const Clave infoClaves []);


/**
 * PRE:  funicion a la que se le pasan 3 variables: la variables claveAIntentar de tipo Clave
 *       el flujo llamado fOriginal que es flujo del archivo original cifrado para leer de el
 *       y finalmente el flujo de escritura fTemp del archivo temporal donde se escribira el 
 *       contenido de fOriginal pero descifrado con el valor k que esta en claveAIntentar.valor 
 * POST: funcion que se encarga de probar la clave k (0 <= k < 26) y crear el archivo temporal
 *       decifrado en esa clave para usarlo mas adelante 
 */
void ejecutarFuerzaBruta(const Clave claveAIntentar, istream& fOriginal, ofstream& fTemp);


/**
 * PRE: ---
 * POST: funcion que se encarga de analizar el archivo temporal creado para la clave k (0 <= k < 26) 
 *       a traves de la busqueda de palabras en el archivo diccionario.dicc
 */
void analizarFuerzaBruta(Clave& claveAIntentar, const char rutaTemp[]);

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
void analizarClavesAutomaticamente();

#endif // ANALISIS_CESAR_H_INCLUDED