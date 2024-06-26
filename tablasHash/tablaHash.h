/**
 * @file tablaHash.h
 * @date 21/02/2024
 * @brief Define una estructura y operaciones básicas para manejar una 
 * tabla de hash para tokens.
 * 
 * La tabla utiliza encadenamiento para resolver colisiones y se 
 * redimensiona dinámicamente para mantener un factor de carga óptimo.
*/

#ifndef TABLAHASH_H 
#define TABLAHASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Estructura que representa un token en la tabla de hash.
 * @param componente Código numérico del componente léxico.
 * @param lexema Representación textual del token.
 * @param next Puntero al siguiente token en caso de colisión.
 * 
 * @param valorUnion Union que permite almacenar diferentes tipos de valores
 * 
 * @param valorUnion.valor Valor numérico asociado al token.
 * @param valorUnion.comando Puntero a función asociado al token.
 * @param valorUnion.funcion1Arg Puntero a función asociado al token con un argumento.
 * @param valorUnion.uncion2Args Puntero a función asociado al token con dos argumentos.
*/
typedef struct token {
    int componente;  // Código numérico del componente léxico.
    char *lexema;    // Representación textual del token.
    struct token *next; // Para manejar colisiones mediante listas enlazadas.

    union {
        float valor;  // Valor numérico asociado al token.
        double (*comando) (); // Puntero a función asociado al token.
        double (*funcion1Arg)(double); // Puntero a función asociado al token.
        double (*funcion2Args)(double, double); // Puntero a función asociado al token.
    } valorUnion;
    
} token;

// Alias para mejorar la legibilidad del código al trabajar con la tabla de hash. 
// El doble puntero se debe a que es un array de punteros a estructura.
typedef token **hashTable;

/**
 * Inicializa la tabla de hash con un tamaño especificado.
 * Reserva memoria para la tabla y la inicializa a NULL.
 * @param tabla Puntero a la tabla de hash.
 * @param size Tamaño de la tabla.
 * @return 1 si la inicialización fue exitosa, 0 en caso de error.
 */
int initHashTable(hashTable *tabla, int size);


/**
 * Libera la memoria asociada con la tabla de hash y sus elementos.
 * @param tabla Puntero a la tabla de hash.
 * @return Siempre devuelve 1.
 */
int deleteHashTable(hashTable tabla);

/**
 * Redimensiona la tabla de hash a un nuevo tamaño.
 * @param tabla Puntero a la tabla de hash.
 * @param newSize Nuevo tamaño de la tabla.
 * @return 1 si la redimensión fue exitosa, 0 en caso de error.
 */
int resizeHashTable(hashTable *tabla, int newSize);

/**
 * Imprime la tabla hash con cada lexema y su componente léxico.
 * @param tabla: tabla de hash que se imprimirá
*/
void printTable(hashTable tabla);

/**
 * Inserta un nuevo token en la tabla de hash.
 * Si el factor de carga supera 0.75, se redimensiona la tabla.
 * @param tabla Puntero a la tabla de hash.
 * @param tokenInsertado Token a insertar.
 * @return 1 si la inserción fue exitosa, 0 en caso contrario.
 */
int insertToken(hashTable *tabla, token tokenInsertado);

/**
 * Busca un token en la tabla de hash por su lexema.
 * @param tabla Tabla de hash.
 * @param lexema Lexema del token a buscar.
 * @return Componente léxico del token si se encuentra, 0 si no se encuentra.
 */
int searchTokenComponent(hashTable tabla, char *lexema);

/**
 * Elimina un token de la tabla de hash.
 * @param tabla Tabla de hash.
 * @param lexema Lexema del token a eliminar.
 * @return 1 si el token fue eliminado correctamente, 0 si no se encontró.
 */
int deleteToken(hashTable tabla, char *lexema);

/**
 * Modifica el componente léxico de un token existente en la tabla de hash.
 * @param tabla Puntero a la tabla de hash.
 * @param lexema Lexema del token a modificar.
 * @param componente Nuevo componente léxico para el token.
 * @param valor Nuevo valor asociado al token.
 * @return 1 si la modificación fue exitosa, 0 si no se encontró el token.
 */
int modifyToken(hashTable *tabla, char * lexema, int componente, float valor);

/**
 * Obtiene el valor asociado a un token en la tabla de hash.
 * @param lexema Lexema del token a buscar.
 * @param tabla Tabla de hash.
 * @return Valor asociado al token si se encuentra, 0 si no se encuentra.
*/
float getValue(char *lexema, hashTable tabla);

/**
 * Imprime el espacio de trabajo con los tokens y sus valores asociados.
 * @param tabla Tabla de hash que se imprimirá.
*/
void printWorkingSpace(hashTable tabla);

/**
 * Elimina todos los elementos de la tabla de hash.
 * @param tabla Tabla de hash.
*/
void deleteWorkingSpace(hashTable tabla); 

/**
 * Obtiene el token asociado a un lexema en la tabla de hash.
 * @param lexema Lexema del token a buscar.
 * @param tabla Tabla de hash.
 * @return Token asociado al lexema si se encuentra, NULL si no se encuentra.
*/
token getToken(hashTable tabla, char *lexema);

#endif //TABLAHASH_H