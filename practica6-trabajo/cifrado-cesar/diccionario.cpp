/****************************************************************************\
 * Curso de Programación 1. Práctica 6 y trabajo obligatorio
 * Autor: Miguel Ángel Latre Abadía
 * Ultima revisión: 9 de diciembre de 2019
 * Resumen: Fichero de implementación «diccionario.cpp» de un módulo que 
 *          define una función denominada «contarPalabras» que, dado un
 *          fichero de texto, cuenta el número de palabras que aparecen y que
 *          no aparecen en un diccionario almacenado en el fichero
 *          «FICH_DICCIONARIO». 
 * Codificación de caracteres original de este fichero: UTF-8 sin BOM
\****************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include "diccionario.h"
using namespace std;

const int MAX_LONG_PALABRA = 30;
const int MAX_PALABRAS = 170000;

struct Diccionario {
    char palabras[MAX_PALABRAS][MAX_LONG_PALABRA];
    int numPalabras = 0;
    bool cargado = false;
};


/*
 * Pre:  «palabra» es una cadena de caracteres acabada en el carácter '\0' y
 *       de menos de MAX_LONG caracteres que no contiene ningún
 *       carácter blanco (ni espacios en blanco, tabulaciones o caracteres de
 *       cambio de línea).
 * Post: Cuando se ha terminado de ejecutar esta función, la cadena de
 *       caracteres «palabra» contiene únicamente las letras del alfabeto
 *       inglés que contenía inicialmente (cuando se comenzó a ejecutar esta
 *       función), en minúsculas. Cualquier otro carácter ha sido eliminado.
 *
 *       Ejemplos:
 *
 *       Valor inicial de «palabra»         Valor final de «palabra»
 *       -----------------------------------------------------------
 *       ""                                 ""
 *       "En"                               "en"
 *       "un"                               "un"
 *       "Mancha,"                          "mancha"
 *       "corredor."                        "corredor"
 *       "-¡Oh!"                            "oh"
 *       "¿Duermen?"                        "duermen"
 *       "1604"                             ""
 *       "H2SO4"                            "hso"
 */
void limpiar(char palabra[]) {
    // Índice con el que consultar cada carácter del valor original de la
    // cadena «palabra». Se va a incrementar de forma constante en 1 unidad
    // en el bucle que procesará palabra.
    int indOriginal = 0;

    // Índice con el que escribir cada carácter del valor final de «palabra».
    // Se va a incrementar en 1 o 0 componentes por iteración, dependiendo de
    // si palabra[indOriginal] es una letra o no. Por ello, se va a cumplir
    // que indLimpia <= indOriginal.
    int indLimpia = 0;

    while (palabra[indOriginal] != '\0') {
        if (isalpha(palabra[indOriginal])) {
            palabra[indLimpia] = tolower(palabra[indOriginal]);
            indLimpia++;
        }
        indOriginal++;
    }
    // palabra[indOriginal] == '\0'

    // Como indLimpia <= indOriginal, hay que asegurarse de que la palabra
    // limpia termina con un carácter nulo en la posición indexada por
    // «indLimpia».
    palabra[indLimpia] = '\0';
}


/*
 * Pre:  Existe un fichero de texto denominado «FICH_DICCIONARIO» que contiene
 *       una única palabra por línea, escrita exclusivamente en minúsculas.
 *       Las palabras del mismo están ordenadas alfabéticamente de forma
 *       ascendente. En el fichero no hay más de «MAX_PALABRAS» y todas ellas
 *       son de menos de «MAX_LONG» caracteres. El vector 
 *       «dicc.palabras» tiene al menos «MAX_PALABRAS» componentes.
 * Post: Ha asignado al campo «numPalabras» de la variable global
 *       «dicc» el número de palabras que contiene el fichero
 *       «FICH_DICCIONARIO», y a las «dicc.numPalabras» primeras
 *       componentes del vector «dicc.palabras», las palabras
 *       contenidas en el fichero, en el mismo orden en que aparecen en el
 *       fichero (ordenadas alfabéticamente). Ha devuelto «true» si el fichero
 *       «nombreFichero» se ha podido leer, y «false» en caso contrario.
 */
bool cargarDiccionario(Diccionario& dicc) {
    ifstream f(FICH_DICCIONARIO);
    if (f.is_open()) {
        dicc.numPalabras = 0;
        f.getline(dicc.palabras[dicc.numPalabras], MAX_LONG_PALABRA);
        while (!f.eof() && dicc.numPalabras < MAX_PALABRAS - 1) {
            dicc.numPalabras++;
            f.getline(dicc.palabras[dicc.numPalabras], MAX_LONG_PALABRA);
        }
        f.close();
        dicc.cargado = true;
        return true;
    }
    else {
        cerr << "No se ha podido abrir el fichero \"" << FICH_DICCIONARIO
             << "\"." << endl;
        return false;
    }
}


/*
 * Pre:  «palabra» es una cadena de caracteres acabada en el carácter '\0' y
 *       de menos de MAX_LONG caracteres; numPalabras > 0; el vector
 *       «dicc» tiene al menos «numPalabras» componentes, que son
 *       cadenas de caracteres, cada una de ellas acabadas en el carácter '\0'
 *       y de menos de MAX_LONG caracteres; las
 *       «numPalabras» primeras componentes del vector «dicc» están
 *       ordenadas alfabéticamente de forma ascendente.
 * Post: Si entre las cadenas de caracteres del vector «dicc» hay una
 *       igual al valor del parámetro «palabra», ha devuelto el índice de
 *       dicha cadena en el vector; en caso contrario, ha devuelto un valor
 *       negativo.
 */
int buscar(const char palabra[], const Diccionario& dicc) {
    int inf = 0;
    int sup = dicc.numPalabras - 1;
    while (inf < sup) {
        int med = (inf + sup) / 2;
        if (strcmp(palabra, dicc.palabras[med]) > 0) {
            inf = med + 1;
        }
        else {
            sup = med;
        }
    }

    if (strcmp(palabra, dicc.palabras[inf]) == 0) {
        return inf;
    }
    else {
        return -1;
    }
}


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
                    int& encontradas, int& noEncontradas) {
    static Diccionario dicc;
    if (!dicc.cargado) {
        if (!cargarDiccionario(dicc)) {
            return false;
        }
    }
    ifstream texto(nombreFichero);
    if (texto.is_open()) {
        encontradas = 0;
        noEncontradas = 0;

        // La longitud de una palabra leída del fichero puede ser mucho más larga
        // que las del diccionario
        const int MAX_LONG_PALABRA_LEIDA = 200;
        char palabra[MAX_LONG_PALABRA_LEIDA];
        // Lectura con el operador de alto nivel, puesto que puede habar dos
        // delimitadores de «palabras» válidos: ' ' y '\n'. «getline» solo
        // permite especificar  un delimitador.
        // Como el método «eof» solo devuelve true cuando se han leído o
        // intentado leer más bytes de los que tiene el fichero, se intenta
        // leer una nueva palabra del texto antes de entrar en el bucle y
        // otra al final.
        texto >> palabra;

        while (!texto.eof()) {
            // texto.eof() es falso: el último intento de lectura (antes de
            // entrar en el bucle o antes de acabar la iteración anterior),
            // leyó correctamente una «palabra». Se procesa a continuación:
            limpiar(palabra);
            if (buscar(palabra, dicc) >= 0) {
                // El índice devuelto corresponde a una componente válida del
                // vector: «palabra» se ha encontrado en el diccionario.
                encontradas++;
            }
            else {
                // Se ha devuelto -1: «palabra» no está en el diccionario.
                noEncontradas++;
            }
            texto >> palabra;
        }
        texto.close();
        return true;
    }
    else {
        return false;
    }
}
