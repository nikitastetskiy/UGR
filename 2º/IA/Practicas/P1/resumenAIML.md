# AIML(Artificial Intelligence Markup Language) resumen : leguaje de marcas

El conocimiento o las respuestas se guarda en la carpeta aiml con extwnsion .aiml 

## conceptos basicos:
1. comienzo de todos los ficheros de conocimiento aiml 2.0:
~~~xml
    <?xml version="1.0" encoding="UTF-8"?>
    <aiml version="2.0">
    ...
    </aiml>
~~~
2. para crear una regla:
~~~xml
aiml busca entre todas las reglas disponibles si hay una sola regla que coincida es esa la que se diapara, si hay mas de una se coge la que tiene mas prioridad

    <category> //regla
        <pattern>"entrada de la regla"</pattern>
        <template>"respuesta"</template>
    </category>
~~~
3. comentarios:
~~~xml
    <!-- comentario -->
~~~

## comodines (dejar un espacio entre comodin y <>)
1. __"*"__ captura una o mas palabras
2. __"^"__ captura 0 o mas palabras  
-> la adaptaciop exacta de una regla tiene mayor prioridad, "^" tiene mas prioridad que "*", por lo tanto ^ sa lanza antes
3. **"_"** una o más palabras(= *)
4. __"#"__  cero o más palabras(= ^)  
_unica diferencia la prioridad_  

_Prioridad:_
~~~
    # > _ > adaptacion exacta > ^ > *
~~~
5. "$" que indica que ese patrón
tiene la mayor prioridad si la adaptación contiene esa palabra.   
ej: `<pattern>`$Quien * Luis`</pattern>`  
$ no es un comodín, es sólo un marcador de prioridad.

 ___star___:  
Los comodines puedes __ser capturados__ deltro del `<templete>` usando `<star/>`
~~~xml
<category>
    <pattern>Mi nombre es *</pattern>
    <template>Hola <star/></template>
</category>
~~~

cuando hay mas de un comodin se usa
~~~xml
    <star index=“x”/>

donde x indica la posicion de aparicion del comodin
~~~

## Variables
hay 3 tipos de variables:  
+ **propiedades del bot**: define la info que se le quiera dar al bot (se lo da el creador)
+ **Predicados o Variables Globales**: en AIML una variable es global cuando su valor puede ser consultado o modificado fuera de una regla (categoría).
+ **Variables Locales**: ambito solo dentro de la regla (categoria), no puede ser consultada fuera de dicha regla

#### propiedades del bot:
se define en `propiedades.txt` __“program-ab/bots/mybots/config/”__  
->añadir variables con formato:
~~~
    <nombre variable>:<valor>
~~~

EL uso de estas variables sigue la sintaxis `<bot name="x"/>`, x es la propiedad que se desea. eje:
~~~xml
<category>
    <pattern>Cual es tu edad</pattern>
    <template>Tengo <bot name=“age”/> anios</template>
</category>
~~~

#### Predicados o Variables Globales <set name=“x”>value</set>
`<set name=“x”>value</set>`, donde x es el nombre de la variable. hay que tener  cuidado con el nombre que se le da.  
Para acceder : `<get name="x">`  
ej:
~~~xml
<pattern> ^ me llamo * </pattern>
<templete>
    <set name="nombre"><atar index="2"></set>
    <get name="nombre"/> es un nombre bonito.
</templete>
~~~
Si se llama a una variable que no se ha creado o esta bacia devuelve `unknown`
#### Variables Locales
Tienen como ambito el *__template__* de la regla.
1. sintaxis `<set var=“x”>value</set>`, x es elnombre de la variable
2. para acceder `<get var="x"/>`, x = nombre variable

#### El tag \<thing>
se usa para evitar el "eco" por pantalla que proboca una variable(en el aacceso y en la asignacion).  
Para ello la asignacion o el aaceso se encierra entre `<thing> <get var="color/"> </thing>` 
## Reduccion Simbolica \<srai>
Enlaza distintas entradas sinonimas en un mismo _template_. Eliminar palabras innecesarias en las entradas. En realidad es una invocacion recursiva a la base de conocimiento(conjunto de categorias), con intencion de reducir las el tamaño del conociemiento
1. `<srai> PATRON A BUSCAR </srai>`
~~~xml
<!--Regla base-->
<category>
    <pattern>Cual es mi nombre</pattern>
    <template><srai>Tu nombre es <get name="nombre"></srai></template>
</category>
<!--Reglas sinonimas-->
<category>
    <pattern>* mi nombre</pattern>
    <template><srai>CUAL ES MI NOMBRE</srai></template>
</category>
<category>
    <pattern>^ como me llamo</pattern>
    <template><srai>CUAL ES MI NOMBRE</srai></template>
</category>
~~~
## Sets y Maps
Se  ubican en las carpetas sets y maps respectibamente, los ficheros tienen extension .txt.  
__Sets__: La secuencia es un valor en cada línea del archivo txt.  
ejemplo uso:
~~~xml
<category>
    <pattern>Es <set>color</set> un color</pattern>
    <template>Si, <star/> es un color </template>
</category>
<category>
    <pattern> Es * un color</pattern>
    <template>No, <star/> no es un color</template>
</category>
~~~
Set tiene mayor prioridad que “*” y “^”, pero menos que “_
“y “#”

__Maos__: cada line del fichero key:dato o cadena1:cadena2
+ La operación `<map name=“capital”>KEY</map>` devuelve el valor asociado a la clave KEY.  

Para que no ocurra que no encuentre la respuesta se suele definir un set con las claves del map.
ejemplo de uso:
~~~xml
<category>
    <pattern>Caul es la capital de <set>pais</set></pattern>
    <template>La capital de <star/> es <map name="capital"><star/></map></template>
</category>
<category>
    <pattern> Es * un color</pattern>
    <template>No, <star/> no es un color</template>
</category>
~~~

AIML tiene definidos implicitamente los siguientes sets y maps:
+ `<set>number</set>`. Números naturales
+ `<map name=“successor”>`. Dado un número natural “n” devuelve “n+1”
+ `<map name=“predecessor”>`. Dado un número natural “n” devuelve “n-1”
+ `<map name=“plural”>`. Devuelve el plurar de un palabra en singular (sólo Inglés)
+ `<map name=“singular”>`. Devuelve el singular de un palabra en plural (sólo Inglés)

## Contexto
Basicamente que una combersacion tenga coerancia y recordar cosas ya dichas. 3 elementos para recordar contexto predicados globales, \<taht> y un set predefinido en el lenguaje llamado “topic”

### 1. El tag `<that>`
El bot recuerda la ultima respuesta. Segun a esa respuesta puede alternar la respuesta del siguiente mensaje.  
Regla 1:
~~~xml
<category>
    <pattern>Si</pattern>
  <that> TE GUSTA EL CAFE</that>
    <template>
    Lo prefieres solo o con leche
    </template>
</category>
~~~
Regla 2:
~~~xml
<category>
    <pattern>^ cafe ^</pattern>
    <template>Te gusta el cafe</template>
</category>
~~~
para que se dispare Regla 1, justo antes se ha tenido que disparar Regla 2.
#### 2. `<set name=“topic”>` / `<topic name=“x”></topic>`
Esta variable global predefinida en el lenguaje permite agrupar las reglas de
manera que estas sólo se activen cuando la conversación se centra en un tema
concreto.
Por defecto, el valor de “topic” es “unknown”.  
Definir un bloque de reglas sobre un tema, se encierra entre`<topic name=”tema”> ... </topic>`

    <topic name=“cafe”>
    <category> ..... </category>
    ..........................
    <category> ..... </category>
    </topic>
Para fijar un tema, en el “template” de alguna regla se usa `<set name=”topic”>`  
~~~xml
<template> te gusta el <set name=“topic”> cafe </set></template>
~~~
## Random, Estructura Condicional y Ciclos
#### 1. El tag `<ramdon>` (para que no se responda siempre lo mismo)
~~~xml
<tempalte>
<random>
    <li> ... </li>
    <li> ... </li>
    ......
    <li> ... <li>
</random>
</template>
~~~
#### 2.Estructura condicional (funciona como un switch)
~~~xml
<condition var =“x”> o <concondition name="x">
    <li value=“x1”> .... </li>
    <li value=“x2”> ... </li>
    ......
    <li> ... <li> <!-- se aplica cuando ningun caso coincide-->
</condition>
~~~
### 5.Ciclos
Son ciclos del tipo “mientras condición hacer un bloque de
operaciones”, con lo que se necesita la operacion condicion
## Aprender (No hace falta)