#include "bfs.h"
#include <stdlib.h>

Cola *crear_cola(void) {
    Cola *c = malloc(sizeof(Cola));
    if (!c) return NULL;
    c->frente = NULL;
    c->fin = NULL;
    return c;
}


void encolar(Cola *cola, int x, int y) {
    if (!cola) return;
    NodoCola *n = malloc(sizeof(NodoCola));
    if (!n) return;
    n->x = x; n->y = y; n->siguiente = NULL;
    if (!cola->fin) {
        cola->frente = cola->fin = n;
    } else {
        cola->fin->siguiente = n;
        cola->fin = n;
    }
}


NodoCola *desencolar(Cola *cola) {
    if (!cola || !cola->frente) return NULL;
    NodoCola *tmp = cola->frente;
    cola->frente = tmp->siguiente;
    if (!cola->frente) cola->fin = NULL;
    return tmp;
}


int tiene_elementos(Cola *cola) {
    return (cola && cola->frente) ? 1 : 0;
}

/* ---------- Liberar toda la cola ---------- */
void liberar_cola(Cola *cola) {
    if (!cola) return;
    while (tiene_elementos(cola)) {
        NodoCola *tmp = desencolar(cola);
        if (tmp) free(tmp);
    }
    free(cola);
}