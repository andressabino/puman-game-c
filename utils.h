#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>      
#include <stdlib.h>     
#include <string.h>     
#include <time.h>     
#include <conio.h>     
                                 

#define MAX_NOMBRE      50      
#define MAX_REGISTROS   1000    
#define MAPA_ANCHO_MAX  10       
#define MAPA_ALTO_MAX   10       


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


typedef struct NodoEnemigo {
    int   x, y;
    struct NodoEnemigo *siguiente;
} NodoEnemigo;


typedef struct {
    NodoEnemigo *primero;
} ListaEnemigos;


typedef struct NodoCola {
    int   x, y;
    struct NodoCola *siguiente;
} NodoCola;

typedef struct {
    NodoCola *frente;
    NodoCola *fin;
} Cola;



void mapper_set_char   (char **mapa, int x, int y, char c);
char mapper_get_char   (char **mapa, int x, int y);
void mapper_set_item   (char **mapa, int x, int y, char c);


int  es_valido         (char **mapa, int filas, int columnas,
                        int x, int y);


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


Cola          *crear_cola           (void);
void           encolar              (Cola *cola, int x, int y);
NodoCola      *desencolar           (Cola *cola);
int            tiene_elementos      (Cola *cola);
void           liberar_cola         (Cola *cola);


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

#endif 