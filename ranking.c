#include "ranking.h"
  #include "utils.h"
  #include <stdio.h>
  #include <string.h>

  #define RANKING_FILE "ranking.txt"

  /* ---------- Cargar ranking desde archivo ---------- */
  void cargar_ranking(RegistroRanking **registros, int *cantidad) {
      FILE *f = fopen(RANKING_FILE, "r");
      if (!f) { *registros = NULL; *cantidad = 0; return; }

      *registros = malloc(sizeof(RegistroRanking) * MAX_REGISTROS);
      if (!*registros) { fclose(f); *registros = NULL; *cantidad = 0; return; }

      int idx = 0;
      while (idx < MAX_REGISTROS &&
             fscanf(f, " %49[^:]:%d:%d",
                    (*registros)[idx].nombre,
                    &(*registros)[idx].puntaje,
                    &(*registros)[idx].tiempo) == 3) {
          ++idx;
      }
      *cantidad = idx;
      fclose(f);
  }

  
  void guardar_ranking(RegistroRanking *registros, int cantidad) {
      FILE *f = fopen(RANKING_FILE, "w");
      if (!f) return;
      for (int i = 0; i < cantidad; ++i) {
          fprintf(f, "%s:%d:%d\n",
                  registros[i].nombre,
                  registros[i].puntaje,
                  registros[i].tiempo);
      }
      fclose(f);
  }

  
  static int comparar(const void *a, const void *b) {
      const RegistroRanking *ra = a;
      const RegistroRanking *rb = b;
      if (ra->puntaje != rb->puntaje) return rb->puntaje - ra->puntaje;   
      return ra->tiempo - rb->tiempo;                                    
  }

  void ordenar_ranking(RegistroRanking *registros, int cantidad) {
      qsort(registros, (size_t)cantidad, sizeof(RegistroRanking), comparar);
  }

  
  void mostrar_ranking(RegistroRanking *registros, int cantidad) {
      printf("\n=== RANKING ===\n");
      for (int i = 0; i < cantidad; ++i) {
          printf("%2d) %-15s %4d pts  %3d s\n",
                 i + 1,
                 registros[i].nombre,
                 registros[i].puntaje,
                 registros[i].tiempo);
      }
  }

  
  void agregar_registro(RegistroRanking **registros, int *cantidad,
                        const char *nombre, int puntaje, int tiempo) {
      if (!registros || !cantidad) return;
      
      if (*cantidad == MAX_REGISTROS) {
          return;
      }
      RegistroRanking *tmp = realloc(*registros,
                                     sizeof(RegistroRanking) * ((*cantidad) + 1));
      if (!tmp) return;
      *registros = tmp;

      strncpy((*registros)[*cantidad].nombre, nombre, MAX_NOMBRE - 1);
      (*registros)[*cantidad].nombre[MAX_NOMBRE - 1] = '\0';
      (*registros)[*cantidad].puntaje = puntaje;
      (*registros)[*cantidad].tiempo  = tiempo;
      (*cantidad)++;

      ordenar_ranking(*registros, *cantidad);
  }