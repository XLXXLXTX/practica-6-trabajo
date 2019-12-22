﻿#ifndef CESAR_H_INCLUDED
#define CESAR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <iostream>

#include "pedir-nombre-fichero.h"

//Declaramos el texto de la opcion 1, "Cifrar un texto"
const char MSJ_OPC_1 []  = "Nombre del fichero a cifrar: ";

//Declaramos el texto de la clave de desplazamiento para la opcion 1 y opcion 2
const char MSJ_CLAVE []  = "Clave de desplazamiento: ";

//Declaramos lso mensajes de error al abrir/crear los ficheros
const char ERROR_FICH_ORIGEN [] = "No se ha podido acceder al fichero '";
const char ERROR_FICH_DESTINO [] = "No ha podido crearse el fichero '";

//Declaramos los diferentes sufijos que van a tener los archivos
const char SUFIJO_CIFRADO [] = "-cifrado";
const char SUFIJO_DESCIFRADO [] = "-descifrado";

//Declaramos un vector con todas las letras en minusculas y mayusculas
//const char ALFABETO [] ="abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
const char ALFABETO_MINUS [] ="abcdefghijklmnopqrstuvwxyz";
const char ALFABETO_MAYUS [] ="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//Declaracion de un vector con los caracteres que no deben cifrarse
const char NO_CIFRAR [] = " .,¿?!¡:;()áéíóúñÁÉÍÓÚÑ";


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
void cifrarTexto();


/**
 * PRE:  Se le pasa una cadena de texto llamada linea, un entero llamado
 *       desplazamiento y u otra cadena de texto llamada lineaCifrada.
 * POST: funcion que se encarga de recibir una linea de texto y un valor
 *       de desplazamiento para cifrarla y copiarla a la cadena de lineaCifrada
 */
void cifrarLinea(const char linea [], int desplazamiento, char lineaCifrada []);


#endif // CESAR_H_INCLUDED