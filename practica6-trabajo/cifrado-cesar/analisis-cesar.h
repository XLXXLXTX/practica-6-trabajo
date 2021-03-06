/********************************************************************************\
 * Programación 1. Práctica 6: Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 17 de Enero de 2020
 * Resumen: Fichero analisis-cesar.h del proyecto "cifrado-cesar"
\********************************************************************************/
#ifndef ANALISIS_CESAR_H_INCLUDED
#define ANALISIS_CESAR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include "pedir-nombre-fichero.h"

const int MIN_ANCHO = 3;
const int TOTAL_CLAVES = 26;

const char SUFIJO_TEMP [] = "-descifrado";
const char RUTA_TEMP []= "./resultados/";

using namespace std;


/**
 * Tipo de dato creado para hacer mas facil el guardado de la informacion 
 * referente a cada clave que se usa, para luego facilitar el analisis de 
 * esos intentos de fuerza bruta.
 */
struct Clave {
    int valor;
    int numPalabras;
    double porcentaje;
};


/**
 * PRE:  una = A y otra = B
 * POST: una = B y otra = A
 */
void permutarClaves (Clave &una, Clave &otra);


/**
 * PRE:  Recibe una lista de registro de tipo Clave como una constante, y otra 
 *       lista del mismo tipo de dato llamada infoClavesOrdenadas en la que 
 *       se guardara los valores de la primera pero ordenados.
 * POST: Se ordenan los registro de tipo Clave de la lista infoClaves de menor 
 *       a mayor segun el porcentaje que lleva asigando cada registro, y se 
 *       guardan ordenados en infoClavesOrdenadas. 
 */
void ordenarClaves(const Clave infoClaves [], Clave infoClavesOrdenadas []);


/**
 * PRE:  Se le pasa una vector de registros de tipo Clave el cual es constante
 *       y no se podra modificar en este metodo.
 * POST: Muestra por pantalla un listado con el formato mas adecuado para que 
 *       que el usuario visualice la lista de las 26 claves posibles a usar 
 *       para descifrar el fichero, con un porcentaje de coincidencia en un 
 *       diccionario y el numero total de palabras de cada clave que son 
 *       reconocidas en el archivo diccionario.dic.
 */
void mostrarListadoClaves(const Clave infoClaves []);


/**
 * PRE:  Se le para un registro de tipo Clave, en el cual solo esta definida
 *       el campo claveAIntentar.valor donde se guarda el valor de la clave k,
 *       el numero de palabras encontradas y el porcentaje de entre palabras 
 *       encontradas y el total de palabras del archvio a descifrar tambien se 
 *       le pasa como constante el vector de char [] rutaTemp que es donde 
 *       se generan los archivos temporales del descifrado con la clave k.
 * POST: Funcion que se encarga de analizar el archivo temporal creado para 
 *       la clave k (0 <= k < 26) a traves de la busqueda de palabras
 *       en el archivo diccionario.dicc.
 */
void analizarFuerzaBruta(Clave& claveAIntentar, const char rutaTemp[]);


/**
 * PRE:  Se le pasa a esta funcion las variables claveAIntentar como
 *       constante, de donde sacamos el valor de la clave k, el flujo 
 *       fOriginal (que es el flujo de lectura del fichero a descifar)
 *       y el flujo de fTemp ( el flujo del fichero temporal donde se 
 *       descifra usando la clave k).
 * POST: Funcion que se encarga de probar la clave k (0 <= k < 26) y 
 *       crear el archivo temporal decifrado en esa clave para usarlo 
 *       mas adelante.
 */
void ejecutarFuerzaBruta(const Clave claveAIntentar, istream& fOriginal, ofstream& fTemp);


/**
 * PRE:  Se le pasa un valor entero llamado opcion, segun el valor de opcion
 *       puede hacer dos cosas: 
 *       si opcion=3, no muestra un el analisis de todas las claves probadas
 *       si opcion = 4, si muestra el analisis 
 *       Tambien se le pasan unas cadenas de caracteres llamadas rutaOrigen 
 *       y rutaDestino en las que estan los valores del fichero original 
 *       (rutaOrigen) a analizar y la ruta donde se van a generar los ficheros
 *       temporales para el analisis (rutaDestino).
 *       Finalmente, se le pasa una variable llamada claveExito, donde guardaremos 
 *       la clave con mayor porcentaje de todas las probadas
 * POST: Funcion que se encarga de englobar todas las ordenes necesarias 
 *       para hacer el analisis de todas las posibles clave k (0 <= k < 26), 
 *       opcion 4 del menu.
 *       Sabiendo la rutaOrigen y rutaDestino, una vez acabado, se muestra 
 *       por pantalla la lista de info de las claves probadas, Si algun error
 *       se produce durante la lectura o escritura del archivo original/cifrado 
 *       se muestra por pantalla un error especificando el fallo.
 *       Ademas esta funcion guarda un entero n cuyo valor es 0<=n<26 para 
 *       indicar cual es la clave con mas porcentaje de coincidencias.
 */
void analizarClavesAutomaticamente(const int opcion, char rutaOrigenConocida [], char rutaDestinoConocida [], int& claveExito);


/**
 * PRE:  ---
 * POST: Funcion que llama a metodos de las otras opcion del programa, 
 *       para poder descifrar un fichero sin que el usuario le de la clave 
 *       solo dejandole que introduza el fichero a descifrar
 */
void descifrarAutomaticamente();


/**
 * PRE:  ---
 * POST: Funcion que se encarga de preparar los datos para 
 *       analizar un fichero y averiguar la clave de cifrado.
 */ 
void prepararAnalizarAutomaticamente();


#endif // ANALISIS_CESAR_H_INCLUDED