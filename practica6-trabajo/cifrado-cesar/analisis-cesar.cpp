#include <stdio.h>
#include <string.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include <cmath>

//------------------
#include <string>
#include <sstream>
//------------------

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
 *       y no se podra modificar en este metodo
 * POST: Muestra por pantalla un listado con el formato mas adecuado para que 
 *       que el usuario visualice la lista de las 26 claves posibles a usar 
 *       para descifrar el fichero, con un porcentaje de exito y el numero 
 *       total de palabras de cada clave que son reconocidas en el archivo 
 *       diccionario.dic.
 */
void mostrarListadoClaves(const Clave infoClaves []){
    //Habria que pasarle una lista de registros
    //que tuviese los campos de 
    //-Clave
    //-Palabras reconocidas en el diccionario.dic
    //-Porcentaje en entre las palabras reconocias den el diccionario
    //y el total de palabras en el archivo
    
    
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
 *       le pasa como constante el vector de char [] rutaTemp que es donde 
 *       se generan los archivos temporales del descifrado con la clave k.
 * POST: Funcion que se encarga de analizar el archivo temporal creado para 
 *       la clave k (0 <= k < 26) a traves de la busqueda de palabras
 *       en el archivo diccionario.dicc.
 */
void analizarFuerzaBruta(Clave& claveAIntentar, const char rutaTemp[]){
    int encontradas = 0;
    int noEncontradas = 0;
    contarPalabras(rutaTemp, encontradas, noEncontradas);
    
//    cout << "Clave: " << claveAIntentar.valor << "----> Encontradas: " << encontradas << " No encontradas: " << noEncontradas << endl;
    double porcentaje = ( encontradas / ( (double) (encontradas + noEncontradas) ) ) * 100;
    
    if(isnan(porcentaje)){
        porcentaje = 0.00;
    }
    
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
//    cout << endl;
//    cout << "----------------------------CLAVE " << claveAIntentar.valor <<"----------------------------" << endl;
//    int k = claveAIntentar.valor;
//    stringstream  nomArchivo;
//    string extensionArchivo = ".txt";
//    string claveString(1, char(k));
//    nomArchivo << "D:/temporalesPractica6/archivoDescifrado-clave-" << k << extensionArchivo;
//    cout << "nomArchivo --> " << nomArchivo.str() << endl; 
//    ofstream archivoDescifrado(nomArchivo.str());

    //Aqui tendriamos que probar el valor que viene en claveAIntentar.valor
    //transformar el fichero con esa clave
    int clave = claveAIntentar.valor;
    
    char lineaADescifrar [MAX_LONG_LINEA];
    fOriginal.getline(lineaADescifrar, MAX_LONG_LINEA);
            
    char descifrada [MAX_LONG_LINEA];
    
    while(!fOriginal.eof()){
        char vacia [MAX_LONG_LINEA] = "";
        strcpy(descifrada, vacia);
                    
        cifrarODescifarLinea(lineaADescifrar, clave, descifrada, MODO_DESCIFRAR);

        fTemp << descifrada << endl;
        
//        cout << "   ---   " << endl;             
//        if(archivoDescifrado.is_open()){
//            archivoDescifrado << descifrada << endl;
//            cout << "   -- escrito en archivo descifrado--   " << endl;
//        }                                   
                    
        strcpy(lineaADescifrar, vacia);
        fOriginal.getline(lineaADescifrar, MAX_LONG_LINEA);
                
    }
    
//    archivoDescifrado.close();
}


/**
 * PRE:  Se le pasa un valor entero llamado opcion, segun el valor de opcion
 *       puede hacer dos cosas: si opcion=3, no muestra un el analisis de 
 *       todas las claves probadas, en cambio si opcion = 4, si muestra el
 *       analisis; tambien se le pasa una cadena de caracteres llamada ruta 
 *       en la que se guardara la rutaOrigenConocida y rutaDestinoConocida 
 *       del archivo a analizar, ya que asi, no se necesitara que se vuelva  
 *       a pedir en otro metodo como podira ser descifrarAutomaticamente();   
 * POST: Funcion que se encarga de englobar todas las ordenes necesarias 
 *       para hacer el analisis de todas las posibles clave k (0 <= k < 26), 
 *       opcion 4 del menu, sabiendo el nombre del fichero (que debe estar 
 *       en la carpeta <<datos>>). Una vez acabado, se muestra por pantalla 
 *       el resultado de la funcion mostrarListadoClaves(), Si algunoo error
 *       se produce durante la lectura o escritura del archivo original/cifrado 
 *       se muestra por pantalla un error especificando el fallo.
 *       Ademas esta funcion devuelve un entero que puede ser: un numero n cuyo
 *       valor es 0<=n<26 para indicar cual es la clave con mas porcentaje de 
 *       coincidencias al descifrar;
 */
int analizarClavesAutomaticamente(const int opcion, char rutaOrigenConocida [], char rutaDestinoConocida []){
    
    char rutaOrigen [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestino [MAX_LONG_NOMBRE_FICHERO];
    
    strcpy(rutaOrigen, DIR_DATOS);
    strcpy(rutaDestino, RUTA_TEMP);
    
    pedirNombreFichero(MSJ_OPC_2_3_4, SUFIJO_TEMP, rutaOrigen, rutaDestino);
    
    strcpy(rutaOrigenConocida, rutaOrigen);
    strcpy(rutaDestinoConocida, rutaDestino);
    
    ifstream ficheroOriginal;
    
    
    //Definimos el vector de registros de tipo Clave, donde se van a guardar la informacion
    //de las pruebas que se hara de las claves k (0 <= k < 26) 
    Clave datosClave [TOTAL_CLAVES];
    
    for(int i=0; i<TOTAL_CLAVES; i++){
        
        ficheroOriginal.open(rutaOrigen);
        
        if(!ficheroOriginal.is_open()){
            cerr << ERROR_FICH_ORIGEN << rutaOrigen << "'" << endl;
        }else{
        
        //Hay que crear un fichero para cada clave
        
        
            
            //Abro el fichero del temporal de la clave k=i
            //tanto como escritura porque es donde voy a escribir el texto cifrado con la clave k
            //como para lectura ya que luego voy a leer las palabras que reconoce al aplicar 
            //laa clave k al descifrar el ficheroOriginal
            
            cout << "----> rutaDestino => " << rutaDestino << endl;
            ofstream ficheroTemp;
            ficheroTemp.open(rutaDestino);
            
            if(!ficheroTemp.is_open()){
                cerr << ERROR_FICH_DESTINO << rutaDestino << "'" << endl;
            }else{
//                    cout << "Valor de i: " << i << endl;
                    
                    datosClave[i].valor = i;
                    
//                    cout << "Valor de datosClave[i].valor: " << datosClave[i].valor << endl;
                    
                    //Fuerza bruta con el valor de k = i
                    ejecutarFuerzaBruta(datosClave[i], ficheroOriginal, ficheroTemp);
                    ficheroTemp.close();
                    //Ahora que ya tenemos el fichero temporal de la clave con valor k = i
                    //podriamos leerlo para sacar las palabras y porcentaje con el diccionario
                    //y ya tendriamos un pocision del vector de datosClave rellenado.
                    //leer todas las palabras 
                    //leer cuales de ellas esta en el diccionario
                    //sacar el porcentaje de encontradas
                    //modificar claveAIntenrar.palabras y claveAIntentar.porcentaje 
                    
                    //Aprovechamos que el flujo es tambien de lectura para el fichero temporal 
                    //donde se ha escrito el contenido descifrado con la funcion ejecutarFuerzaBruta()
                    analizarFuerzaBruta(datosClave[i], rutaDestino);
                    ficheroOriginal.close();
                    
            }
            //Cerramos el flujo de escritura del archivo ya que no nos va a hacer falta volver a escribir en el 
            
            
            //Ahora borramos el archivo temporal
            remove(rutaDestino);
//            if(remove(rutaDestino) == 0){
//                cout << "Fichero temporal borrado " << endl;
//            }else{
//                cout << "Fichero temporal NO borrado " << endl;
//            }

        }
        
    }
    
    //Nueva lista de tipo Clave para que guardemos ahi, la lista ordenada 
    //de menor a mayor porcentaje de palabras encontradas al aplicar la clave
    Clave infoClavesOrdenadas [TOTAL_CLAVES];

    ordenarClaves(datosClave, infoClavesOrdenadas);
    
    if(opcion == 4){
        mostrarListadoClaves(infoClavesOrdenadas);
    }    
    
    return infoClavesOrdenadas[TOTAL_CLAVES-1].valor;
}

/**
 * PRE:  ---
 * POST: Funcion que llama a metodos de las otras opcion del programa, 
 *       para poder descifrar un fichero sin que el usuario le de la clave 
 *       solo dejandole que introduza el fichero a descifrar
 */
void descifrarAutomaticamente(){
    char rutaOrigenConocida [MAX_LONG_NOMBRE_FICHERO];
    char rutaDestinoConocida [MAX_LONG_NOMBRE_FICHERO];
    
    int clave  = analizarClavesAutomaticamente(3, rutaOrigenConocida, rutaDestinoConocida);
    descifrarTexto(clave, rutaOrigenConocida, rutaDestinoConocida);
}