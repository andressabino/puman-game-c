#include "agentes.h"
  #include "mapa.h"
  #include "utils.h"
  #include <stdlib.h>

  
  ListaEnemigos *crear_lista_enemigos(void) {
      ListaEnemigos *l = malloc(sizeof(ListaEnemigos));
      if (!l) return NULL;
      l->primero = NULL;
      return l;
  }

  void agregar_enemigo(ListaEnemigos *lista, int x, int y) {
      if (!lista) return;
      NodoEnemigo *n = malloc(sizeof(NodoEnemigo));
      if (!n) return;
      n->x = x; n->y = y; n->siguiente = lista->primero;
      lista->primero = n;
  }

  /* ---------- Movimiento de enemigos (BFS) ---------- */


  int bfs_distancia(char **mapa, int filas, int columnas, int start_x, int start_y, int target_x, int target_y) {
      if (start_x == target_x && start_y == target_y) return 0;
      Cola *q = crear_cola();
      if (!q) return 9999;

      char **visitado = crear_mapa(filas, columnas);
      if (!visitado) { liberar_cola(q); return 9999; }

      
      for (int i = 0; i < filas; ++i)
          for (int j = 0; j < columnas; ++j) visitado[i][j] = -1;

      encolar(q, start_x, start_y);
      visitado[start_x][start_y] = 0;

      int dist_final = 9999;

      while (tiene_elementos(q)) {
          NodoCola *n = desencolar(q);
          if (!n) break;
          int cx = n->x, cy = n->y;

          if (cx == target_x && cy == target_y) {
              dist_final = visitado[cx][cy];
              free(n);
              break;
          }

          int dx[4] = { -1, 1, 0, 0 };
          int dy[4] = { 0, 0, -1, 1 };
          for (int d = 0; d < 4; ++d) {
              int nx = cx + dx[d], ny = cy + dy[d];
              if (nx >= 0 && nx < filas && ny >= 0 && ny < columnas &&
                  visitado[nx][ny] == -1 && es_valido(mapa, filas, columnas, nx, ny)) {
                  encolar(q, nx, ny);
                  visitado[nx][ny] = visitado[cx][cy] + 1;
              }
          }
          free(n);
      }

      liberar_cola(q);
      liberar_mapa(visitado, filas);
      return dist_final;
  }

  /* Movimiento de todos los enemigos */
  void mover_enemigos(ListaEnemigos *lista, char **mapa,
                      int filas, int columnas, Jugador *jugador) {
      if (!lista || !jugador) return;

      NodoEnemigo *act = lista->primero;
      while (act) {
          int min_dist = 9999;
          int best_x = act->x;
          int best_y = act->y;

          int dx[4] = { -1, 1, 0, 0 };
          int dy[4] = { 0, 0, -1, 1 };

          for (int d = 0; d < 4; ++d) {
              int nx = act->x + dx[d], ny = act->y + dy[d];
              if (es_valido(mapa, filas, columnas, nx, ny)) {
                  int dist = bfs_distancia(mapa, filas, columnas, nx, ny, jugador->posicion_x, jugador->posicion_y);
                  if (dist < min_dist) {
                      min_dist = dist;
                      best_x = nx;
                      best_y = ny;
                  }
              }
          }

          
          if (best_x != act->x || best_y != act->y) {
              
              if (mapper_get_char(mapa, act->x, act->y) == 'O') {
                  mapper_set_char(mapa, act->x, act->y, '.');
              }
              act->x = best_x;
              act->y = best_y;
          }

          act = act->siguiente;
      }
  }

  /* ---------- Detección de colisión ---------- */
  int verificar_colision(Jugador *jugador, ListaEnemigos *enemigos) {
      if (!jugador || !enemigos) return 0;
      NodoEnemigo *n = enemigos->primero;
      while (n) {
          if (n->x == jugador->posicion_x && n->y == jugador->posicion_y)
              return 1;
          n = n->siguiente;
      }
      return 0;
  }

 
  void liberar_lista_enemigos(ListaEnemigos *lista) {
      if (!lista) return;
      NodoEnemigo *n = lista->primero;
      while (n) {
          NodoEnemigo *sig = n->siguiente;
          free(n);
          n = sig;
      }
      free(lista);
  }