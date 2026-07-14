/* mapa.c - Implementación del TAD mapa matricial */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "agentes.h"

int enemigo_presente(ListaEnemigos *enemigos, int x, int y);

/* Asigna un mapa bidimensional de tamaño filas x columnas */
char **crear_mapa(int filas, int columnas) {
    if (filas <= 0 || columnas <= 0) return NULL;
    char **mapa = malloc(filas * sizeof(char *));
    if (!mapa) return NULL;
    for (int i = 0; i < filas; i++) {
        mapa[i] = malloc(columnas * sizeof(char));
        if (!mapa[i]) {
            /* liberar lo asignado hasta el punto de fallo */
            for (int j = 0; j < i; j++) free(mapa[j]);
            free(mapa);
            return NULL;
        }
    }
    return mapa;
}

/* Libera toda la memoria asociada al mapa */
void liberar_mapa(char **mapa, int filas) {
    if (!mapa) return;
    for (int i = 0; i < filas; i++) {
        if (mapa[i]) free(mapa[i]);
    }
    free(mapa);
}

/* Inicializa el mapa con paredes, espacios libres y algunos ítems */
void inicializar_mapa(char **mapa, int filas, int columnas) {
    if (!mapa) return;
    /* 1 = pared, . = vacío, * = ítem, P = jugador, O = oso */
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1) {
                mapa[i][j] = '1';   /* pared */
            } else {
                mapa[i][j] = '.';   /* espacio libre */
            }
        }
    }
    /* Colocar algunos ítems aleatorios (máx 5) */
    int max_items = (filas * columnas) / 8;
    for (int k = 0; k < max_items; k++) {
        int x = rand() % (filas - 2) + 1;
        int y = rand() % (columnas - 2) + 1;
        if (mapa[x][y] == '.') {
            mapa[x][y] = '*';
        }
    }
}

/* Renderizar el mapa en consola */
void renderizar_mapa(char **mapa, int filas, int columnas,
                      Jugador *jugador, ListaEnemigos *enemigos) {
    system("cls||clear");   /* limpiar pantalla (Windows | Linux/Mac) */
    printf("Mapa: %dx%d  \\n", filas, columnas);
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            /* Sobreimprimir el jugador y los enemigos */
            int imprime_personaje = 0;
            if (jugador && i == jugador->posicion_x && j == jugador->posicion_y) {
                printf("🐧");
                imprime_personaje = 1;
            }
            if (!imprime_personaje && enemigo_presente(enemigos, i, j)) {
                printf("🦭");
                imprime_personaje = 1;
            }
            if (!imprime_personaje) {
                char c = mapa[i][j];
                if (c == '1') printf("🧱");       /* pared */
                else if (c == '.') printf("⬛"); /* vacío */
                else if (c == '*') printf("🎓"); /* ítem */
                else printf("%c ", c);            /* fallback */
            }
        }
        putchar('\n');
    }
}

/* Verificar si una casilla es transitable */
int es_valido(char **mapa, int filas, int columnas, int x, int y) {
    if (!mapa) return 0;
    if (x < 0 || x >= filas || y < 0 || y >= columnas) return 0;
    return mapa[x][y] != '1'; /* Todo lo que no sea pared es transitable */
}

/* Funciones utilitarias para manipular el mapa */
void mapper_set_char(char **mapa, int x, int y, char c) {
    if (mapa && x >= 0 && y >= 0) mapa[x][y] = c;
}
char mapper_get_char(char **mapa, int x, int y) {
    if (!mapa) return '\0';
    if (x >= 0 && y >= 0 && x < MAPA_ALTO_MAX && y < MAPA_ANCHO_MAX) {
        return mapa[x][y];
    }
    return '\0';
}
void mapper_set_item(char **mapa, int x, int y, char c) {
    if (mapa && x >= 0 && y >= 0) mapa[x][y] = c;
}

/* Funciones auxiliares */
int enemigo_presente(ListaEnemigos *enemigos, int x, int y) {
    if (!enemigos) return 0;
    NodoEnemigo *actual = enemigos->primero;
    while (actual) {
        if (actual->x == x && actual->y == y) return 1;
        actual = actual->siguiente;
    }
    return 0;
}