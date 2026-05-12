# El Caso del Detective

> Juego de deduccion en consola desarrollado en C++, donde encarnas a un detective que debe explorar una ciudad, recolectar pistas y atrapar al culpable — con el menor numero de movimientos posible.

---

## Tabla de Contenidos

- [Descripcion del juego](#descripcion-del-juego)
- [Como jugar](#como-jugar)
- [El mapa de la ciudad](#el-mapa-de-la-ciudad)
- [Elementos del mapa](#elementos-del-mapa)
- [Pistas y sus efectos](#pistas-y-sus-efectos)
- [Los sospechosos](#los-sospechosos)
- [Sistema de puntaje](#sistema-de-puntaje)
- [Ranking historico](#ranking-historico)
- [Estructuras de datos utilizadas](#estructuras-de-datos-utilizadas)
- [Arquitectura del proyecto](#arquitectura-del-proyecto)
- [Compilacion](#compilacion)

---

## Descripcion del juego

Un crimen ha ocurrido en la ciudad. Existen **8 sospechosos**, uno de los cuales es el culpable. Tu mision como detective es explorar las calles, recolectar evidencia y deducir la identidad del criminal antes de realizar tu acusacion.

La clave esta en la **eficiencia**: cada paso que das suma un punto a tu puntaje, y el objetivo es resolver el caso con el **menor puntaje posible**. Menos movimientos = mejor detective.

---

## Como jugar

Al iniciar el juego se te pedira tu nombre. Luego aparecera el mapa de la ciudad y el HUD con tu estado actual:

```
+--------------------------------------------------+
  NombreDetective  |  Puntaje: 12  |  Pistas: 3/10  |  Testigos en cola: 1
+--------------------------------------------------+
# # # # # # # # # # #
#         H       W #
#   |     o   C     #
#       I           #
#   T       P   |   #
# # # # # # # # # # #
+--------------------------------------------------+
  W: arriba  A: izquierda  s: abajo  D: derecha
  S: Sospechosos  T: Pistas  I: Interrogar  X: Usar pista  0: Salir
```

### Controles

| Tecla | Accion |
|-------|--------|
| `W` | Mover arriba |
| `A` | Mover izquierda |
| `S` (minuscula) | Mover abajo |
| `D` | Mover derecha |
| `S` (mayuscula) | Ver tabla de sospechosos |
| `T` | Ver pila de pistas recolectadas |
| `I` | Interrogar al siguiente testigo en cola |
| `X` | Usar la pista en el tope de la pila |
| `0` | Salir (se te preguntara si deseas acusar) |

> **Nota:** `s` minuscula mueve hacia abajo; `S` mayuscula muestra los sospechosos.

---

## El mapa de la ciudad

El mapa es una **cuadricula de 11x11** (9x9 de area jugable mas un borde de paredes). Se genera de forma **aleatoria** al inicio de cada partida. El detective comienza en una posicion aleatoria libre.

El mapa implementa una **red doblemente enlazada en 4 direcciones**: cada celda conoce a sus vecinas (arriba, abajo, izquierda, derecha), lo que permite moverse sin calcular indices de array.

### Mecanica de visibilidad (niebla de guerra)

Las celdas no visitadas se muestran como `o`. Al moverte, la celda queda **descubierta** y muestra su contenido real. Cuando usas una pista con `X`, el mapa se **vuelve a cubrir** (excepto las paredes `#` y callejones `|` ya descubiertos), obligandote a re-explorar.

---

## Elementos del mapa

| Simbolo | Nombre | Descripcion |
|---------|--------|-------------|
| `#` | Pared / Edificio | Borde infranqueable de la ciudad |
| `\|` | Callejon cerrado | Pasaje bloqueado, no se puede atravesar |
| `o` | Celda sin explorar | Contenido oculto hasta visitarla |
| ` ` (espacio) | Celda vacia | Ya explorada, no hay nada aqui |
| `I` | Detective | Tu posicion actual |
| `H` | Huella dactilar | Pista recolectable |
| `C` | Coartada | Pista recolectable |
| `T` | Testimonio | Pista recolectable |
| `P` | Prueba forense | Pista recolectable |
| `W` | Testigo | Deja una declaracion en la cola al pisarlo |

### Distribucion inicial aleatoria

En cada partida el juego coloca aleatoriamente:
- **16 callejones** (`|`) que obstaculizan el movimiento
- **10 pistas** en total: 3 Huellas, 3 Coartadas, 2 Testimonios, 2 Pruebas
- **5 testigos** (`W`) distribuidos por la ciudad

---

## Pistas y sus efectos

Al pisar una pista, suceden **dos cosas simultaneamente**:

1. **Se revela un atributo aleatorio del culpable** (estatura, cabello, piel, nariz, zurdo).
2. **La pista se apila** en tu `PilaPistas` para ser usada despues con `X`.

Cuando presionas `X`, se extrae la pista del **tope de la pila** (LIFO) y se activa su efecto especial. Despues, el mapa se re-cubre y la pista **vuelve al tablero** en una posicion nueva aleatoria.

### Efectos de cada pista

| Pista | Efecto al usar con `X` |
|-------|----------------------|
| **H - Huella** | Tu puntaje se **reduce a la mitad**. Beneficioso si tienes muchos movimientos acumulados. |
| **C - Coartada** | Se **eliminan 2 callejones** del mapa, abriendo nuevos caminos. |
| **T - Testimonio** | **Azar puro**: 50% de probabilidad de resetear el puntaje a 0, o 50% de duplicarlo. Alto riesgo, alta recompensa. |
| **P - Prueba forense** | Te **teletransporta** a una celda oculta no explorada, permitiendo descubrir zonas del mapa rapidamente. |

> La pila es LIFO: la ultima pista que recolectaste es la primera que usaras con `X`. Planifica el orden de uso.

### Testigos y la Cola

Al pisar un `W`, la declaracion del testigo se **encola** en la `ColaTestigos`. Presiona `I` para interrogar al siguiente testigo en orden FIFO (el mas antiguo primero). Cada declaracion revela un nuevo atributo del culpable.

---

## Los sospechosos

Al inicio de cada partida se generan **8 sospechosos** con atributos aleatorios:

| Atributo | Valores posibles |
|----------|-----------------|
| Estatura | alto, bajo, mediano |
| Cabello | negro, rubio, castano, rojo |
| Piel | claro, moreno, oscuro |
| Nariz | recta, aguilenya, respingada |
| Zurdo | si / no |

Uno de los 8 es el **culpable**, elegido al azar. Las pistas y los testimonios van revelando progresivamente sus atributos.

### Fase de Acusacion

El juego termina de dos formas:

- **Recolectaste 10 pistas**: la acusacion es **obligatoria**.
- **Presionas `0`**: se te pregunta si deseas acusar. Si dices que no, el caso queda abandonado y el puntaje no se registra.

En la fase de acusacion se muestra la tabla de sospechosos con los atributos confirmados del culpable, para que puedas deducir quien coincide. El sistema usa la **tabla hash** para buscar al acusado en O(1) promedio.

| Resultado | Consecuencia |
|-----------|-------------|
| Acusacion correcta | El puntaje se guarda tal cual |
| Acusacion incorrecta | El puntaje se **duplica** como penalizacion |

---

## Sistema de puntaje

> **Menor puntaje = mejor detective.** Cada movimiento suma 1.

El puntaje representa el numero de movimientos realizados. Un detective eficiente navega directo a las pistas con pocos pasos. Puntos clave:

- Cada vez que te mueves a una celda nueva: `puntaje++`
- Usar pista `H`: `puntaje /= 2`
- Usar pista `T`: `puntaje = 0` o `puntaje *= 2` (50/50)
- Acusacion incorrecta: `puntaje *= 2`

---

## Ranking historico

El juego mantiene un **ranking persistente durante la sesion** usando un Arbol Binario de Busqueda (ABB). El arbol esta ordenado por puntaje de menor a mayor.

Desde el menu principal puedes:
- **Ver el ranking** completo (recorrido inorden del ABB = lista ordenada de menor a mayor puntaje).
- **Buscar un detective** por nombre para ver su mejor puntaje registrado.

Si un detective juega varias veces, solo se guarda su **mejor puntaje** (el mas bajo).

```
====== RANKING HISTORICO ======
  (menor puntaje = mejor detective)
  Maria    ->  8 movimientos
  Carlos   -> 14 movimientos
  Juan     -> 23 movimientos
===============================
```

---

## Estructuras de datos utilizadas

Este proyecto fue desarrollado como practica de estructuras de datos. Cada modulo principal usa una estructura distinta:

### Red doblemente enlazada bidireccional — `Mapa` / `NodoMapa`

El mapa es una **red de punteros en 4 direcciones**. Cada `NodoMapa` tiene punteros a sus 4 vecinos (`arriba`, `abajo`, `izquierda`, `derecha`). Esto permite navegar la cuadricula sin necesidad de un array 2D, y es la base estructural del juego.

```
        [arriba]
           |
[izq] -- [nodo] -- [der]
           |
        [abajo]
```

Operaciones principales:
- `buildGrid()`: construye la red enlazando 121 nodos (11x11)
- `mostrar()`: recorre la red fila por fila siguiendo punteros
- `eliminarCallejones()`: busca y convierte nodos `|` en `o`
- `resetVisibilidad()`: oculta el mapa recorriendo todos los nodos

### Tabla Hash — `GestorSospechosos`

Usa `std::unordered_map<string, Sospechoso>` para almacenar los 8 sospechosos. La busqueda al momento de acusar es **O(1) promedio**, lo que el juego reporta explicitamente en pantalla como demostracion.

```
tablaHash["Carlos"]   -> Sospechoso{alto, negro, moreno, recta, false}
tablaHash["Diana"]    -> Sospechoso{baja, rubio, claro, aguilenya, true}
...
```

### Pila (LIFO) — `PilaPistas`

Usa `std::stack<char>` para las pistas recolectadas. Implementa las operaciones clasicas `push`, `pop` y `top`. La pista mas reciente es siempre la primera en usarse con `X`.

```
Tope -> [ P ]  <- se usa con X
        [ T ]
        [ H ]
        [ C ]  <- primera recolectada
```

### Cola (FIFO) — `ColaTestigos`

Usa `std::queue<string>` para las declaraciones de testigos. El primer testigo encontrado es el primero en ser interrogado con `I`.

```
Frente -> [ "El culpable tiene: cabello rojo" ]  <- I lo dequeue
          [ "El culpable tiene: estatura alta" ]
          [ "El culpable tiene: nariz recta"   ]  <- ultimo encolado
```

### Arbol Binario de Busqueda (ABB) — `ArbolPuntajes`

Almacena los puntajes del ranking. El criterio de orden es el **puntaje numerico** (menor a la izquierda, mayor a la derecha). El recorrido **inorden** produce la lista ordenada de menor a mayor puntaje. Si un jugador ya tiene puntaje registrado, se guarda solo si el nuevo es menor.

```
           [14 - Carlos]
          /              \
   [8 - Maria]     [23 - Juan]
```

Recorrido inorden: Maria(8) -> Carlos(14) -> Juan(23)

---

## Arquitectura del proyecto

```
Proy_Detective_EST/
|
+-- main.cpp               Punto de entrada, menu principal, instancia ArbolPuntajes
|
+-- Juego.h / Juego.cpp    Controlador principal del juego, loop de input
|
+-- Mapa.h / Mapa.cpp      Red doblemente enlazada, generacion y gestion del tablero
+-- NodoMapa.h             Struct de cada celda del mapa (4 punteros + datos)
|
+-- GestorSospechosos.h/cpp  Tabla hash de sospechosos, logica de revelacion
+-- sospechoso.h / .cpp      Modelo de datos del sospechoso
|
+-- PilaPistas.h / .cpp    Pila LIFO para pistas recolectadas
+-- ColaTestigos.h / .cpp  Cola FIFO para declaraciones de testigos
+-- ArbolPuntajes.h / .cpp ABB de puntajes ordenados para el ranking
|
+-- Detective.h / .cpp     (version legacy del detective, reemplazado por Juego)
+-- Tablero.h / .cpp       (version legacy del tablero con std::list)
```

### Flujo de ejecucion

```
main()
  |
  +-- menu principal
        |
        +-- [1] Jugar
        |     |
        |     +-- Juego::jugar()
        |           |
        |           +-- loop: mostrar mapa, leer input
        |           |     |
        |           |     +-- mover()       -> puntaje++, recolectarElemento()
        |           |     +-- usarPista()   -> aplicarEfecto(), resetVisibilidad()
        |           |     +-- interrogarTestigo() -> ColaTestigos::desencolar()
        |           |
        |           +-- fasePrincipalAcusacion()
        |                 |
        |                 +-- GestorSospechosos::buscarSospechoso() [O(1)]
        |                 +-- GestorSospechosos::esCulpable()
        |                 +-- retorna puntaje final
        |
        +-- [2] Ver Ranking  -> ArbolPuntajes::mostrarRanking() (inorden)
        +-- [3] Buscar       -> ArbolPuntajes::buscar() (busqueda por nombre)
```

---

## Compilacion

El proyecto usa **CMake**. Para compilar:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

O directamente con g++:

```bash
g++ -std=c++17 -o detective \
    main.cpp Juego.cpp Mapa.cpp GestorSospechosos.cpp \
    sospechoso.cpp PilaPistas.cpp ColaTestigos.cpp \
    ArbolPuntajes.cpp Detective.cpp Tablero.cpp
```

Requiere C++17 o superior.

---

*Proyecto desarrollado para la asignatura de Estructuras de Datos.*
