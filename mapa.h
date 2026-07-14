
  #ifndef MAPA_H
  #define MAPA_H

  #include "utils.h"

  /* Declaraciones de la capa de mapa */
  char **crear_mapa(int filas, int columnas);
  void   liberar_mapa(char **mapa, int filas);
  void   inicializar_mapa(char **mapa, int filas, int columnas);
  void   renderizar_mapa(char **mapa, int filas, int columnas,
                         Jugador *jugador, ListaEnemigos *enemigos);
  int    es_valido(char **mapa, int filas, int columnas, int x, int y);
  void   mapper_set_char(char **mapa, int x, int y, char c);
  char   mapper_get_char(char **mapa, int x, int y);
  void   mapper_set_item(char **mapa, int x, int y, char c);

  #endif /* MAPA_H */