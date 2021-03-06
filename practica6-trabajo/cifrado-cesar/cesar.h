﻿/********************************************************************************\
 * Programación 1. Práctica 6: Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 17 de Enero de 2020
 * Resumen: Fichero cesar.h del proyecto "cifrado-cesar"
\********************************************************************************/
#ifndef CESAR_H_INCLUDED
#define CESAR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "pedir-nombre-fichero.h"

//Declaramos la longitud maxima de cada linea a cifrar/descifrar
const int MAX_LONG_LINEA = 250;

//Declaramos el texto de la opcion 1, "Cifrar un texto"
const char MSJ_OPC_1 []  = "Nombre del fichero a cifrar: ";
//Declaramos el texto de la opcion 2,3 y 4; "Descifrar un texto"
const char MSJ_OPC_2_3_4 []  = "Nombre del fichero a descifrar: ";

//Declaramos Mensaje de exito al acabar la opcion 1 o 2
const char MSJ_EXITO_PT1 []  = "El contenido del fichero \"";
const char MSJ_EXITO_C_PT2 []  = "\" ha sido cifrado con clave ";
const char MSJ_EXITO_D_PT2 []  = "\" ha sido descifrado con clave ";
const char MSJ_EXITO_PT3 []  = " y almacenado en \"";

//Declaramos el texto de la clave de desplazamiento para la opcion 1 y opcion 2
const char MSJ_CLAVE []  = "Clave de desplazamiento: ";

//Declaramos lso mensajes de error al abrir/crear los ficheros
const char ERROR_FICH_ORIGEN [] = "No se ha podido acceder al fichero \"";
const char ERROR_FICH_DESTINO [] = "No ha podido crearse el fichero \"";

//Declaramos los diferentes sufijos que van a tener los archivos
const char SUFIJO_CIFRADO [] = "-cifrado";
const char SUFIJO_DESCIFRADO [] = "-descifrado";

//Declaramos variables para saber si estamos en modo descifrar o cifrar
const char MODO_CIFRAR = 'c';
const char MODO_DESCIFRAR = 'd';

const int CLAVE_SEGUN_ANALISIS = -999;

/**
 * PRE:  Se le pasa una cadena de texto llamada linea, un entero llamado
 *       desplazamiento, otra cadena de texto llamada lineaTransformada y
 *       finalmente un char llamdo modo que sera el encargado de elegir que algoritmo
 *       usar: si el de cifrar o el de descifrar 
 * POST: funcion que se encarga de recibir una linea de texto y un valor
 *       de desplazamiento para cifrarla/descifrarla segund el valor del caracter
 *       <<modo>> y copiarla a la cadena de lineaTransformada
 */
void cifrarODescifarLinea(const char linea [], int desplazamiento, char lineaTransformada [], const char modo);


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
 void pedirDatos(const int opcion, int& claveDesplazamiento, char origenUsu [], char destinoUsu []);
 

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
void cifrarTexto(const int claveDesplazamiento, const char origenUsu [], const char destinoUsu []);


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
void descifrarTexto(const int claveDesplazamiento, const char rutaOrigen [], const char rutaDestino []);


/**
 * PRE:  ---
 * POST: ---
 */
void prepararCifrarTexto();


/**
 * PRE:  ---
 * POST: ---
 */
void prepararDescifrarTexto();


#endif // CESAR_H_INCLUDED