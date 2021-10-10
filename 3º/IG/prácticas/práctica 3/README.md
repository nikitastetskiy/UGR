## Práctica 3

Se ha realizado un cubo de Rubik, el cual puede ser de las dimensiones que se quieran, ya que he realizado una especie de algoritmo que calcula las posiciones de cada cubo para que se pueda calcular con cualquier dimensión. Aunque para dimensiones grandes no he tenido tiempo para mejorar las animaciones y dicho algoritmo, aun así, llegan a funcionar.

---

- 'R' -> Cubo de Rubik (ARTICULADO)
- 'Q' -> Salir
- '1' -> Puntos
- '2' -> Aristas
- '3' -> Sólido
- '4' -> Sólido Ajedrez
- '5' -> Rubik (Diferencia los colores Blanco, Azul, Verde, Amarillo y Naranja)

---

Para mover las caras -> {A, S, D, W, E, F}.
Cada cara se puede mover con varios grados de libertad hasta que empiecen a chocarse las unas con otras, es decir, para que no colapsen. Cada letra mueve una cara, ya sea la blanca, azul, amarilla o naranja respectivamente.
Para moverlas al sentido contrario -> {-}.

También se ha añadido un modo que mueve las caras de manera aleatoria -> {X}.
Para resolver el cubo ya sea con este modo o moviendo las caras arbitrariamente -> {V}.