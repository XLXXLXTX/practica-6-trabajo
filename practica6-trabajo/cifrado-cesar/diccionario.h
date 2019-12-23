/****************************************************************************\
 * Curso de Programación 1. Práctica 6 y trabajo obligatorio
 * Autor: Miguel Ángel Latre Abadía
 * Ultima revisión: 9 de diciembre de 2019
 * Resumen: Fichero de interfaz «diccionario» de un módulo que declara
 *          una función denominada «contarPalabras» que, dado un fichero de
 *          texto, cuenta el número de palabras que aparecen y que no aparecen
 *          en un diccionario almacenado en el fichero «FICH_DICCIONARIO». 
 * Codificación de caracteres original de este fichero: UTF-8 sin BOM
\****************************************************************************/

#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED

/*
 * Ruta de acceso y nombre del fichero diccionario que contiene una lista de
 * palabras en español, en minúsculas, a razón de una por línea y, por
 * limitaciones para trabajar con UTF-8 en C++ y con los compiladores utilizados,
 * sin eñes ni diacríticos.
 */
//const char FICH_DICCIONARIO[] = "../../datos/diccionario.dic";
const char FICH_DICCIONARIO[] = "./datos/diccionario.dic";

/*
 * Pre:  «nombreFichero» es una cadena de caracteres cuyo valor representa el
 *       nombre de un fichero de texto que utiliza la misma codificación de
 *       caracteres que el fichero «FICH_DICCIONARIO». Los valores de los
 *       parámetros «encontradas» y «noEncontradas» no están definidos.
 * Post: Ha asignado a los parámetros «encontradas» y «noEncontradas» el
 *       número de palabras contenidas en el fichero de nombre
 *       «nombreFichero» que, respectivamente, se encuentran y no se han
 *       encontrado en el diccionario almacenado en «FICH_DICCIONARIO». Ha
 *       devuelto «true» cuando el fichero de nombre «nombreFichero» ha podido
 *       procesarse correctamente, y «false» en caso contrario.
 */
bool contarPalabras(const char nombreFichero[],
                    int& encontradas, int& noEncontradas);

#endif // DICCIONARIO_H_INCLUDED