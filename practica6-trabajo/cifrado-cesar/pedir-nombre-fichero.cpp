/********************************************************************************\
 * Programación 1. Práctica 6: Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 17 de Enero de 2020
 * Resumen: Fichero pedir-nombre-fichero.cpp del proyecto "cifrado-cesar"
\********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <pedir-nombre-fichero.h>
#include <cesar.h>

using namespace std;
/*
 * Pre:  «rutaOrigen» y «rutaDestino» tienen una dimensión suficiente como
 *       para albergar una ruta relativa a un fichero cuya denominación
 *       escribirá el usuario.
 * Post: Ha solicitado al usuario el nombre de un fichero, utilizando para
 *       ello la cadena de caracteres «mensaje». A continuación, a leído dicha
 *       denominación del teclado (consistente en un nombre base que no
 *       contenía el carácter «.» y una extensión que comienza con el
 *       carácter «.»). Ha asignado a «rutaOrigen» una ruta de acceso relativa
 *       al mismo, consistente en la concatenación de los siguientes
 *       elementos:
 *          - la cadena «DIR_DATOS»
 *          - el nombre base del fichero leído del teclado
 *          - la extensión del fichero leído del teclado.
 *       Ha asignado a «rutaDestino» una ruta de acceso a un fichero
 *       consistente en la concatenación de los siguientes elementos:
 *          - la cadena «DIR_RESULTADOS»
 *          - el nombre base del fichero leído del teclado
 *          - el interfijo establecido por el valor del parámetro «interfijo»
 *          - la extensión del fichero leído del teclado.
 */
void pedirNombreFichero(const char mensaje[], const char interfijo[], char rutaOrigen[], char rutaDestino[]){
    //1º ESCRIBE POR PANTALLA <<MENSAJE>>
    cout << mensaje;
    char nombreArchivo [MAX_LONG_NOMBRE_FICHERO];
    cin >> nombreArchivo;
    
    //2º LEER NOMBRE DEL FICHERO Y SE PASA A OTRA CADENA PARA HACER LOS APAÑOS DE:
    //-Añadirle el prefijo del directorio ../datos/ a la variable "nombreArchivo"
    //-Añadirle el sufijo de cifrado o descifrado, ademas de el prefjo de ../resultado/ a la variable "nombreArchivo"
    
    //3º CREA <<RUTA ORIGEN>>
    char rutaCompletaOrigen [MAX_LONG_NOMBRE_FICHERO];
    
    //Montamos la ruta completa de origen con:
    // ../datos/ + "nombreArchivo"
    strcpy(rutaCompletaOrigen, rutaOrigen);
    strcat(rutaCompletaOrigen, nombreArchivo);
   
    //4º CREA <<RUTA DESTINO>>
    char rutaCompletaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaCompletaDestino, rutaOrigen);
    
    //Se puede usar strtok para delimitar el nombre del fichero y dividirlo
    //Separamos en nombre de archivo y extension, ya que se van a añadir cosas entre ambas partes
    char* nombre = strtok(nombreArchivo, ".");
    char* extensionArchivo = strtok(NULL, ".");
    
    //Montamos la ruta completa con:
    // ../resultados/ + "nombre" + "-cifrado"    + "."  + "extensionArchivo"
    // ../resultados/ + "nombre" + "-descifrado" + "."  + "extensionArchivo"
    strcpy(rutaCompletaDestino, rutaDestino);
    strcat(rutaCompletaDestino, nombre);
    strcat(rutaCompletaDestino, interfijo);
    strcat(rutaCompletaDestino, ".");
    strcat(rutaCompletaDestino, extensionArchivo);
    
    
    //Se les copia a las variables la ruta completas del archivo original y del final
    strcpy(rutaOrigen, rutaCompletaOrigen);
    strcpy(rutaDestino, rutaCompletaDestino);
    
}