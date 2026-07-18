#ifndef RANKING_H
  #define RANKING_H

  #include "utils.h"

  
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