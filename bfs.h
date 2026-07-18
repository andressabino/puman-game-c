#ifndef BFS_H
#define BFS_H

#include "utils.h"


Cola     *crear_cola(void);
void      encolar(Cola *cola, int x, int y);
NodoCola *desencolar(Cola *cola);
int       tiene_elementos(Cola *cola);
void      liberar_cola(Cola *cola);

#endif 