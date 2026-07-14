#ifndef UTILS_H
#define UTILS_H

/* -------------------------------------------------
   UTILIDADES COMUNES – DEFINICIONES Y PROTOTIPOS
   ------------------------------------------------- */

/* --- Includes necesarios ------------------------------------------------ */
#include <stdio.h>      /* printf, scanf, etc.                     */
#include <stdlib.h>     /* malloc, free, rand, etc.                */
#include <string.h>     /* strlen, strcpy, strcmp, etc.            */
#include <time.h>     /* time, clock                           */
#include <conio.h>     /* getch() en Windows                      */
                                 /* En Linux/Mac: incluir <unistd.h> y usar getchar() */

/* --- Constantes y tamaños ------------------------------------------------ */
#define MAX_NOMBRE      50      /* longitud máxima de un nombre            */
#define MAX_REGISTROS   1000    /* capacidad máxima del ranking            */
#define MAPA_ANCHO_MAX  10       /* tamaño máximo de columnas del mapa       */
#define MAPA_ALTO_MAX   10       /* tamaño máximo de filas del mapa          */

/* --- Estructuras compartidas ------------------------------------------------ */
typedef struct {
    char nombre[MAX_NOMBRE];
    int  posicion_x;
    int  posicion_y;
    int  items_recolectados;
    int  tiempo_segundos;
    int  puntaje_final;
} Jugador;

typedef struct {
    char  nombre[MAX_NOMBRE];
    int   puntaje;
    int   tiempo;
} RegistroRanking;

/* --- Lista enlazada de enemigos ------------------------------------------ */
typedef struct NodoEnemigo {
    int   x, y;
    struct NodoEnemigo *siguiente;
} NodoEnemigo;

/* Lista de enemigos completa */
typedef struct {
    NodoEnemigo *primero;
} ListaEnemigos;

/* --- Cola utilizada por el algoritmo BFS ----------------------------------- */
typedef struct NodoCola {
    int   x, y;
    struct NodoCola *siguiente;
} NodoCola;

typedef struct {
    NodoCola *frente;
    NodoCola *fin;
} Cola;

/* --- Prototipos de funciones utilitarias -------------------------------- */

/* Operaciones de acceso al mapa (definidas en mapa.c) */
void mapper_set_char   (char **mapa, int x, int y, char c);
char mapper_get_char   (char **mapa, int x, int y);
void mapper_set_item   (char **mapa, int x, int y, char c);

/* Validación de movimiento y renderizado (definidos en mapa.c) */
int  es_valido         (char **mapa, int filas, int columnas,
                        int x, int y);

/* Funciones de gestión de enemigos (definidas en agentes.c) */
ListaEnemigos *crear_lista_enemigos(void);
void           agregar_enemigo      (ListaEnemigos *lista, int x, int y);
void           mover_enemigos       (ListaEnemigos *lista,
                                    char **mapa,
                                    int filas,
                                    int columnas,
                                    Jugador *jugador);
int            verificar_colision   (Jugador *jugador,
                                    ListaEnemigos *enemigos);
void           liberar_lista_enemigos (ListaEnemigos *lista);

/* Cola auxiliar utilizada por BFS (definida en bfs.c) */
Cola          *crear_cola           (void);
void           encolar              (Cola *cola, int x, int y);
NodoCola      *desencolar           (Cola *cola);
int            tiene_elementos      (Cola *cola);
void           liberar_cola         (Cola *cola);

/* Lógica del ranking (definida en ranking.c) */
void           cargar_ranking       (RegistroRanking **registros,
                                    int            *cantidad);
void           guardar_ranking      (RegistroRanking *registros,
                                    int            cantidad);
void           ordenar_ranking      (RegistroRanking *registros,
                                    int            cantidad);
void           mostrar_ranking      (RegistroRanking *registros,
                                    int            cantidad);
void           agregar_registro     (RegistroRanking **registros,
                                    int            *cantidad,
                                    const char     *nombre,
                                    int             puntaje,
                                    int             tiempo);

#endif /* UTILS_H */