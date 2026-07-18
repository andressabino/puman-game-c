  #include "utils.h"
  #include "mapa.h"
  #include "agentes.h"
  #include "bfs.h"
  #include "ranking.h"
  #include <windows.h>

  #define MAX_JUGADORES 100

  int main(void) {
      SetConsoleOutputCP(CP_UTF8);
      srand((unsigned)time(NULL));

      
      char nombre[50];
      int filas;
      printf("=== Bienvenido a PUMAN ===\n");
      printf("Ingresa tu nombre: ");
      scanf("%49s", nombre);
      printf("Selecciona el tamaño del mapa (entre 5 y 10): ");
      scanf("%d", &filas);
      if (filas < 5) filas = 5;
      if (filas > 10) filas = 10;

      /* ---------- Creación del mapa ---------- */
      char **mapa = crear_mapa(filas, filas);
      if (!mapa) {
          fprintf(stderr, "Error al crear el mapa.\n");
          return 1;
      }
      inicializar_mapa(mapa, filas, filas);

      /* ---------- Creación del jugador ---------- */
      Jugador *jugador = malloc(sizeof(Jugador));
      if (!jugador) {
          fprintf(stderr, "Error al asignar memoria al jugador.\n");
          liberar_mapa(mapa, filas);
          return 1;
      }
      strcpy(jugador->nombre, nombre);
      jugador->posicion_x = filas / 2;
      jugador->posicion_y = filas / 2;
      jugador->items_recolectados = 0;
      jugador->tiempo_segundos = 0;
      jugador->puntaje_final = 0;

      /* ---------- Lista de enemigos ---------- */
      ListaEnemigos *enemigos = crear_lista_enemigos();
      if (!enemigos) {
          fprintf(stderr, "Error al crear la lista de enemigos.\n");
          free(jugador);
          liberar_mapa(mapa, filas);
          return 1;
      }
      
      agregar_enemigo(enemigos, 1, 1);
      agregar_enemigo(enemigos, filas - 2, filas - 2);

      
      char tecla;
      while (1) {
          renderizar_mapa(mapa, filas, filas, jugador, enemigos);
          printf("Puntaje: %d  Tiempo: %ds  Items: %d\n",
                 jugador->puntaje_final,
                 jugador->tiempo_segundos,
                 jugador->items_recolectados);
          printf("Controles: WASD para mover, Q para salir\n");
          tecla = getch();  

          if (tecla == 'q' || tecla == 'Q') break;   

         
          ++jugador->tiempo_segundos;

          
          int nx = jugador->posicion_x;
          int ny = jugador->posicion_y;
          switch (tecla) {
              case 'w': case 'W': nx--; break;
              case 's': case 'S': nx++; break;
              case 'a': case 'A': ny--; break;
              case 'd': case 'D': ny++; break;
              default: continue;   
          }

          
          if (es_valido(mapa, filas, filas, nx, ny)) {
              
              if (mapa[nx][ny] == '*') {
                  ++jugador->items_recolectados;
                  mapper_set_item(mapa, nx, ny, '.');  
              }
              
              mapper_set_char(mapa, jugador->posicion_x,
                              jugador->posicion_y, '.');
              jugador->posicion_x = nx;
              jugador->posicion_y = ny;
              mapper_set_char(mapa, nx, ny, 'P');     
          }

          
          if (verificar_colision(jugador, enemigos)) {
              mapper_set_char(mapa, jugador->posicion_x, jugador->posicion_y, '.');
              jugador->posicion_x = -1; 
              jugador->posicion_y = -1;
              renderizar_mapa(mapa, filas, filas, jugador, enemigos);
              printf("Puntaje: %d  Tiempo: %ds  Items: %d\n", jugador->puntaje_final, jugador->tiempo_segundos, jugador->items_recolectados);
              printf("\n¡Has sido atrapado por un tiburón!\n");
              break;
          }

          
          mover_enemigos(enemigos, mapa, filas, filas, jugador);

          
          if (verificar_colision(jugador, enemigos)) {
              mapper_set_char(mapa, jugador->posicion_x, jugador->posicion_y, '.');
              jugador->posicion_x = -1; 
              jugador->posicion_y = -1;
              renderizar_mapa(mapa, filas, filas, jugador, enemigos);
              printf("Puntaje: %d  Tiempo: %ds  Items: %d\n", jugador->puntaje_final, jugador->tiempo_segundos, jugador->items_recolectados);
              printf("\n¡Has sido atrapado por un tiburón!\n");
              break;
          }
      }

      /* ---------- Fin del juego – actualizar ranking ---------- */
      RegistroRanking *ranking = NULL;
      int cant = 0;
      cargar_ranking(&ranking, &cant);
      agregar_registro(&ranking, &cant,
                       jugador->nombre,
                       jugador->items_recolectados * 100 - jugador->tiempo_segundos * 2,
                       jugador->tiempo_segundos);
      ordenar_ranking(ranking, cant);
      mostrar_ranking(ranking, cant);
      guardar_ranking(ranking, cant);

      
      free(jugador);
      liberar_mapa(mapa, filas);
      liberar_lista_enemigos(enemigos);
      free(ranking);

      printf("Gracias por jugar!\n");
      return 0;
  }