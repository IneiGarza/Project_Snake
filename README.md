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

// Version II

**Función gotoxy y Ocultar Cursor:**

**gotoxy(int x, int y):**

Mueve el cursor a la posición (x, y) en la consola.

**HideCursor():**

Oculta el cursor para que no parpadee en la pantalla.

**Pantalla de Bienvenida:**

**WelcomeScreen():**
Muestra un mensaje de bienvenida y espera a que el usuario presione una tecla para comenzar el juego.

**Doble Buffer:**

Usamos la función gotoxy(0, 0) al principio de la función Draw() para mover el cursor al inicio de la consola antes de redibujar todo el tablero. Esto elimina el parpadeo.
