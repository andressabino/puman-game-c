  #ifndef AGENTES_H
  #define AGENTES_H

  #include "utils.h"

  /* Operaciones sobre la lista enlazada de enemigos */
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

  #endif /* AGENTES_H */
