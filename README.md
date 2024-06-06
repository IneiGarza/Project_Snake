**Explicación del Código**
**Definición de Constantes y Variables:**

WIDTH y HEIGHT definen las dimensiones del tablero de juego.

Variables para la posición de la cabeza de la serpiente (x, y), la fruta (fruitX, fruitY), la puntuación (score), y las posiciones de la cola de la serpiente (tailX, tailY).

**Funciones:**

**Setup():**
Inicializa el juego, colocando la serpiente y la fruta en posiciones iniciales.
**Draw():**
Dibuja el tablero de juego en la consola.
**Input():**
Detecta la entrada del teclado para mover la serpiente.
**Logic():**
Actualiza la lógica del juego, moviendo la serpiente, detectando colisiones y comiendo frutas.
**Bucle Principal:**
Llama a las funciones Draw(), Input() y Logic() en un bucle infinito, con una pausa (Sleep(100)) para controlar la velocidad del juego.
