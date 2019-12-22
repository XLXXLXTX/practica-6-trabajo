#include <stdio.h>
#include <string.h>
#include <iostream>
#include <pedir-nombre-fichero.h>

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
    //mensaje[] --> "Inserta el nombre del fichero"
    //1º ESCRIBE POR PANTALLA <<MENSAJE>>
    cout << mensaje;
    char nombreArchivo [MAX_LONG_NOMBRE_FICHERO];
    cin >> nombreArchivo;
    
//    //2º LEER NOMBRE DEL FICHERO
    char rutaCompletaOrigen [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaCompletaOrigen, rutaOrigen);
    strcat(rutaCompletaOrigen, nombreArchivo);
    
    //rutaCompletaOrigen --> RUTA DEL ARCHIVO A LEER ENTERA
    
    //3º CREA <<RUTA ORIGEN>>
   
    //4º CREA <<RUTA DESTINO>>
    char rutaCompletaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaCompletaDestino, rutaOrigen);
    
    
    char* nombre = strtok(nombreArchivo, ".");
    char* extensionArchivo = strtok(NULL, ".");
    
    
    strcpy(rutaCompletaDestino, rutaDestino);
    strcat(rutaCompletaDestino, nombre);
    strcat(rutaCompletaDestino, interfijo);
    strcat(rutaCompletaDestino, ".");
    strcat(rutaCompletaDestino, extensionArchivo);
    
//    cout << "rutaCompletaOrigen: --> " << rutaCompletaOrigen << endl;
//    cout << "rutaCompletaDestino: --> " << rutaCompletaDestino << endl;
    //Se puede usar strtok para delimitar el nombre del fichero y dividirlo
    
    //Se les copia a las variables la ruta completas del archivo original y del final
    strcpy(rutaOrigen, rutaCompletaOrigen);
    strcpy(rutaDestino, rutaCompletaDestino);
    
    
    
    //pchr = strtok(nombre, '.');
    //pchr = strtok(NULL, '.')
    
}