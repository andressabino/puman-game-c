Integrantes: Manuel Sabino, Diego Sandia,Andres Matheus.

 PUMAN — Casimiro sobreviviente

Un videojuego interactivo en consola desarrollado en C , donde el jugador controla a  Casimiro (mascota de la universidad) para recolectar créditos académicos mientras escapa de tiburones hambrientos.

Las mecánicas y arquitectura

Mecánica 1 — El Tablero Matricial
Temas: `matrices dinámicas`, `malloc / free`, `coordenadas 2D`

El entorno del juego se genera mediante una matriz bidimensional dinámica de caracteres. Al iniciar, el jugador decide el tamaño (ej. 10x10). Las paredes, ítems, jugador y enemigos navegan dentro de este arreglo bidimensional en tiempo real con renderizado en consola soportando UTF-8 (emojis).

 Mecánica 2 — La IA de Persecución (Búsqueda en Anchura - BFS)
Temas:  `TAD Cola (Queue)`, `BFS`, `búsqueda de rutas`

Los tiburones utilizan el algoritmo **BFS (Breadth-First Search)** para encontrar el camino más corto hacia el pingüino en un laberinto con paredes. En cada turno, el enemigo explora sus cuadrantes vecinos y utiliza una estructura de Cola (Queue) para calcular las distancias en un mapa virtual paralelo de celdas visitadas. Tras resolver el tablero temporal, se mueve hacia la celda adyacente que le ofrezca la ruta de menor distancia, logrando una persecución matemática perfecta estilo Pac-Man.

 Mecánica 3 — Sistema de Ranking y Persistencia
Temas: `archivos de texto I/O`, `estructuras (structs)`, `qsort`, `arreglos dinámicos`

Al finalizar la partida, la puntuación obtenida se almacena en `ranking.txt`. Al terminar o abrir el juego, el historial completo se carga en memoria utilizando *realloc*, se aplica el algoritmo QuickSort (ordenando de mayor a menor puntaje, desempatando por tiempo récord de supervivencia) y se despliega la tabla de los mejores jugadores.


 INSTRUCCIONES PARA JUGAR 

 1. Compilación
Abre una terminal y ejecuta el compilador GCC sobre todos los archivos `.c`:
```bash
gcc *.c -o puman
```

 2. Ejecución
```bash
.\puman
```

 3. Controles
Usa las teclas **W, A, S, D** seguido de **Enter** para moverte por el mapa de la universidad. 
- 🐧 **Casimiro** (Jugador)
- 🦈 **Tiburón Hambriento** (Enemigo persiguiéndote por BFS)
- 🎓 **Créditos** (Puntos que debes recoger)
- 🧱 **Paredes** (Muros inquebrantables)
- ⬛ **Espacio Vacío**
