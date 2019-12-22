/*********************************************************************************
 * Curso de Programación 1. Práctica 6 y trabajo obligatorio
 * Autor: Miguel Ángel Latre Abadía
 * Ultima revisión: 8 de diciembre de 2019
 * Resumen: Fichero de interfaz «pedir-nombre-fichero.h» de un módulo que declara
 *          una función denominada «pedirNombreFichero» que facilita la labor de
 *          convertir el nombre de un fichero solicitado al usuario en una ruta de
 *          acceso relativa al directorio de ejecución del proyecto solicitado 
 *          en esta tarea y en la siguiente. 
 * Codificación de caracteres original de este fichero: UTF-8 sin BOM
\********************************************************************************/

#ifndef PEDIR_NOMBRE_FICHERO_H_INCLUDED
#define PEDIR_NOMBRE_FICHERO_H_INCLUDED

const int MAX_LONG_NOMBRE_FICHERO = 200;
//const char DIR_DATOS[] = "../../datos/";
const char DIR_DATOS[] = "./datos/";
//const char DIR_RESULTADOS[] = "../../resultados/";
const char DIR_RESULTADOS[] = "./resultados/";

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
void pedirNombreFichero(const char mensaje[], const char interfijo[],
                        char rutaOrigen[], char rutaDestino[]);

#endif // PEDIR_NOMBRE_FICHERO_H_INCLUDED