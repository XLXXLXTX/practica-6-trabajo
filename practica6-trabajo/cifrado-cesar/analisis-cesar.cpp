#include <stdio.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <cmath>

#include <diccionario.h>
#include <pedir-nombre-fichero.h>
#include <cesar.h>
#include "analisis-cesar.h"

using namespace std;

/**
 * PRE:  una = A y otra = B
 * POST: una = B y otra = A
 */
void permutarClaves (Clave &una, Clave &otra) {
    Clave aux = una;
    una = otra;
    otra = aux;
}


/**
 * PRE:  Recibe una lista de registro de tipo Clave como una constante, y otra 
 *       lista del mismo tipo de dato llamada infoClavesOrdenadas en la que 
 *       se guardara los valores de la primera pero ordenados.
 * POST: Se ordenan los registro de tipo Clave de la lista infoClaves de menor 
 *       a mayor segun el porcentaje que lleva asigando cada registro, y se 
 *       guardan ordenados en infoClavesOrdenadas. 
 */
void ordenarClaves(const Clave infoClaves [], Clave infoClavesOrdenadas []){
    
    for(int i=0; i<TOTAL_CLAVES; i++){
        infoClavesOrdenadas[i] = infoClaves[i];
    }
    
    // Se ha programado un algoritmo de ordenación de una tabla por el método
    // de selección.
    for (int i = 0; i < TOTAL_CLAVES - 1; ++i) {

        int iMayor = i;
        for (int j = i + 1; j < TOTAL_CLAVES; ++j) {
            if ( infoClavesOrdenadas[j].porcentaje < infoClavesOrdenadas[iMayor].porcentaje ) {
                iMayor = j;
            }
        }
        permutarClaves(infoClavesOrdenadas[i], infoClavesOrdenadas[iMayor]);
    }
}


/**
 * PRE:  Se le pasa una vector de registros de tipo Clave el cual es constante
 *       y no se podra modificar en este metodo.
 * POST: Muestra por pantalla un listado con el formato mas adecuado para que 
 *       que el usuario visualice la lista de las 26 claves posibles a usar 
 *       para descifrar el fichero, con un porcentaje de coincidencia en un 
 *       diccionario y el numero total de palabras de cada clave que son 
 *       reconocidas en el archivo diccionario.dic.
 */
void mostrarListadoClaves(const Clave infoClaves []){
   
    //Se le pasa la lista de registro con los campos necesarios para hacer la tabla 
    
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
             << infoClaves[i].numPalabras << setw(MIN_ANCHO*3) 
             << setprecision(1)
             << infoClaves[i].porcentaje << " %" << endl;
    }
}


/**
 * PRE:  Se le para un registro de tipo Clave, en el cual solo esta definida
 *       el campo claveAIntentar.valor donde se guarda el valor de la clave k,
 *       el numero de palabras encontradas y el porcentaje de entre palabras 
 *       encontradas y el total de palabras del archvio a descifrar tambien se 
 *       le pasa como constante el vector de char rutaTemp [] que es donde 
 *       se generan los archivos temporales del descifrado con la clave k.
 * POST: Funcion que se encarga de analizar el archivo temporal creado para 
 *       la clave k (0 <= k < 26) a traves de la busqueda de palabras
 *       en el archivo diccionario.dicc.
 */
void analizarFuerzaBruta(Clave& claveAIntentar, const char rutaTemp[]){
    
    int encontradas = 0;
    int noEncontradas = 0;
    contarPalabras(rutaTemp, encontradas, noEncontradas);
    
    double porcentaje = ( encontradas / ( (double) (encontradas + noEncontradas) ) ) * 100;
     
    claveAIntentar.numPalabras = encontradas;
    claveAIntentar.porcentaje = porcentaje;
}


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
void ejecutarFuerzaBruta(const Clave claveAIntentar, istream& fOriginal, ofstream& fTemp){

    int clave = claveAIntentar.valor;
    
    char lineaADescifrar [MAX_LONG_LINEA];
    fOriginal.getline(lineaADescifrar, MAX_LONG_LINEA);
            
    char descifrada [MAX_LONG_LINEA];
    
    while(!fOriginal.eof()){
        char vacia [MAX_LONG_LINEA] = "";
        strcpy(descifrada, vacia);
                    
        cifrarODescifarLinea(lineaADescifrar, clave, descifrada, MODO_DESCIFRAR);

        fTemp << descifrada << endl;
            
        strcpy(lineaADescifrar, vacia);
        fOriginal.getline(lineaADescifrar, MAX_LONG_LINEA);
                
    }
}


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
void analizarClavesAutomaticamente(const int opcion, char rutaOrigen [], char rutaDestino [], int& claveExito){
    
    ifstream ficheroOriginal;
    
    //Definimos el vector de registros de tipo Clave, donde se van a guardar la informacion
    //de las pruebas que se hara de las claves k (0 <= k < 26) 
    Clave datosClave [TOTAL_CLAVES];
    
    for(int i=0; i<TOTAL_CLAVES; i++){
        
        ficheroOriginal.open(rutaOrigen);
        
        if(!ficheroOriginal.is_open()){
            cerr << ERROR_FICH_ORIGEN << rutaOrigen << "'" << endl;
        }else{

            //Abro el fichero del temporal de la clave k=i
            //para escritura porque es donde voy a escribir el texto cifrado con la clave 
            
//            cout << "----> rutaDestino => " << rutaDestino << endl;
            ofstream ficheroTemp;
            ficheroTemp.open(rutaDestino);
            
            if(!ficheroTemp.is_open()){
                cerr << ERROR_FICH_DESTINO << rutaDestino << "'" << endl;
            }else{
                    
                    datosClave[i].valor = i;
                    
                    //Fuerza bruta con el valor de k = i
                    ejecutarFuerzaBruta(datosClave[i], ficheroOriginal, ficheroTemp);
                    ficheroTemp.close();
                    //Como ya hemos escrito el fichero temporal con la clave intentada i, se cierra
                    //porque ahora se va a nalizar para saber la informacion de esa clave usada
                
                    //Ahora le pasamos la ruta donde esta el fichero temporal descifrado con la clave i
                    //para que analice el fichero y guarde en datosClave[i].numPalabras las palabras que
                    //se reconocen al aplicar el cifrado y en datosClave[i].porcentaje el porcentaje 
                    //de palabras reconocidas en todo el fichero
                    analizarFuerzaBruta(datosClave[i], rutaDestino);
                    //Cerramos el fichero original, para que al abrirlo la siguiente iteracion
                    //vuelva a leer desde el principio, si no se cerrase no leeria nada porque 
                    //el curso estaria al final del archivo
                    ficheroOriginal.close();
            }
            //Ahora borramos el archivo temporal de la iteracion 
            remove(rutaDestino);
        }
    }
    //Nueva lista de tipo Clave para que guardemos ahi, la lista ordenada 
    //de menor a mayor porcentaje de palabras encontradas al aplicar la clave
    Clave infoClavesOrdenadas [TOTAL_CLAVES];

    ordenarClaves(datosClave, infoClavesOrdenadas);
    
    if(opcion == 4){
        mostrarListadoClaves(infoClavesOrdenadas);
    }    
    
    //Finalmente ahora que esta ordenada la lista, sabemos que en la ultima posicion
    //esta la clave con mas porcentaje, asique se la asignamos a claveExito
    claveExito = infoClavesOrdenadas[TOTAL_CLAVES-1].valor;

}


/**
 * PRE:  ---
 * POST: Funcion que llama a metodos de las otras opcion del programa, 
 *       para poder descifrar un fichero sin que el usuario le de la clave 
 *       solo dejandole que introduza el fichero a descifrar
 */
void descifrarAutomaticamente(){
    
    int claveExito;
    int claveDesplazamiento;
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    pedirDatos(3, claveDesplazamiento, rutaOrigen, rutaDestino);
    
    analizarClavesAutomaticamente(3, rutaOrigen, rutaDestino, claveExito);
    descifrarTexto(claveExito, rutaOrigen, rutaDestino);
}


/**
 * PRE:  ---
 * POST: Funcion que se encarga de preparar los datos para 
 *       analizar un fichero y averiguar la clave de cifrado.
 */
void prepararAnalizarAutomaticamente(){
    
    int claveExito;
    int claveDesplazamiento;
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    pedirDatos(4, claveDesplazamiento, rutaOrigen, rutaDestino);
    
    analizarClavesAutomaticamente(4, rutaOrigen, rutaDestino, claveExito);
}
