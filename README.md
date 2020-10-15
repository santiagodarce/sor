# Sistemas Operativos y Redes

## Trabajo Práctico de hilos y semáforos

Siguiendo los comentarios del template brindado, pude generar y sincronizar de forma correcta los semaforos de cada una de las acciones del programa.

Uno de los temas que no habia visto eran los struct, que me permiten definir una nueva estructura con los datos que formaran parte de la misma.

Tuve muchos problemas a la hora de querer agregar el texto al archivo, ya que en un principio no podia agregarlo, pero utilizando el metodo Fopen (miarchivo,"r") pude abrir el mismo, posteriormente cambie el tipo de apertura a "a+" el cual me permitiria agregar texto al archivo al final del mismo.
De esta forma pude agregar texto al archivo pero siempre lo agregaba al principio del archivo, para corregir esto utilice fseek junto con Seek_End para mover el cursor al final del archivo fseek (miarchivo, 0, SEEK_END);

Debajo dejo el contenido que genera el programa en el archivo log,txt al ejecutarse,

![Captura de pantalla de 2020-10-15 17-26-39](https://user-images.githubusercontent.com/72938718/96182369-c50db980-0f0b-11eb-89d2-b537a234159a.png)

Ejecutando equipo 3 
--------------------------------------------------x
	Equipo 3 - accion cortar 
 	Equipo 3 -----------ingredientes : ----------
	Equipo 3 ingrediente  0 : ajo 
	Equipo 3 ingrediente  1 : perejil 
	Equipo 3 ingrediente  2 : cebolla 
--------------------------------------------------
--------------------------------------------------x
	Equipo 3 - accion cortar2 
 	Equipo 3 -----------ingredientes : ----------
	Equipo 3 ingrediente  0 : lechuga 
	Equipo 3 ingrediente  1 : tomate 
--------------------------------------------------
--------------------------------------------------
Ejecutando equipo 1 
Ejecutando equipo 2 
--------------------------------------------------x
	Equipo 1 - accion cortar2 
 	Equipo 1 -----------ingredientes : ----------
	Equipo 1 ingrediente  0 : lechuga 
	Equipo 1 ingrediente  1 : tomate 
--------------------------------------------------
--------------------------------------------------x
	Equipo 2 - accion cortar 
 	Equipo 2 -----------ingredientes : ----------
	Equipo 2 ingrediente  0 : ajo 
	Equipo 2 ingrediente  1 : perejil 
	Equipo 2 ingrediente  2 : cebolla 
--------------------------------------------------
--------------------------------------------------x
	Equipo 1 - accion cortar 
 	Equipo 1 -----------ingredientes : ----------
	Equipo 1 ingrediente  0 : ajo 
	Equipo 1 ingrediente  1 : perejil 
	Equipo 1 ingrediente  2 : cebolla 
--------------------------------------------------
--------------------------------------------------x
	Equipo 2 - accion cortar2 
 	Equipo 2 -----------ingredientes : ----------
	Equipo 2 ingrediente  0 : lechuga 
	Equipo 2 ingrediente  1 : tomate 
--------------------------------------------------
	Equipo 3 empieza a usar el horno
 	Equipo 3 deja de usar el horno
--------------------------------------------------x
	Equipo 3 - accion mezclar 
 	Equipo 3 -----------ingredientes : ----------
	Equipo 3 ingrediente  0 : ajo 
	Equipo 3 ingrediente  1 : perejil 
	Equipo 3 ingrediente  2 : cebolla 
	Equipo 3 ingrediente  3 : carne picada 
--------------------------------------------------
--------------------------------------------------
--------------------------------------------------x
	Equipo 2 - accion mezclar 
 	Equipo 2 -----------ingredientes : ----------
	Equipo 2 ingrediente  0 : ajo 
	Equipo 2 ingrediente  1 : perejil 
	Equipo 2 ingrediente  2 : cebolla 
	Equipo 2 ingrediente  3 : carne picada 
--------------------------------------------------
--------------------------------------------------x
	Equipo 1 - accion mezclar 
 	Equipo 1 -----------ingredientes : ----------
	Equipo 1 ingrediente  0 : ajo 
	Equipo 1 ingrediente  1 : perejil 
	Equipo 1 ingrediente  2 : cebolla 
	Equipo 1 ingrediente  3 : carne picada 
--------------------------------------------------
--------------------------------------------------x
	Equipo 3 - accion salar 
 	Equipo 3 -----------ingredientes : ----------
	Equipo 3 ingrediente  0 : carne picada 
--------------------------------------------------
	Equipo 1 empieza a usar el horno
 	Equipo 1 deja de usar el horno
 --------------------------------------------------
	Equipo 3 toma el salero
 	Equipo 3 devuelve el salero
--------------------------------------------------x
	Equipo 3 - accion armar_medallones 
 	Equipo 3 -----------ingredientes : ----------
--------------------------------------------------
-------------------------------------------------x
	Equipo 1 - accion salar 
 	Equipo 1 -----------ingredientes : ----------
	Equipo 1 ingrediente  0 : carne picada 
--------------------------------------------------
	Equipo 2 empieza a usar el horno
 	Equipo 2 deja de usar el horno
 	Equipo 1 toma el salero
 	Equipo 1 devuelve el salero
--------------------------------------------------x
	Equipo 3 - accion cocinar_medallones 
 	Equipo 3 -----------ingredientes : ----------
--------------------------------------------------
-------------------------------------------------x
	Equipo 1 - accion armar_medallones 
 	Equipo 1 -----------ingredientes : ----------
--------------------------------------------------
-------------------------------------------------x
	Equipo 2 - accion salar 
 	Equipo 2 -----------ingredientes : ----------
	Equipo 2 ingrediente  0 : carne picada 
--------------------------------------------------
	Equipo 2 toma el salero
 	Equipo 2 devuelve el salero
 	Equipo 3 empieza a usar la plancha
 	Equipo 3 deja de usar la plancha
--------------------------------------------------x
	Equipo 3 - accion armar_hamburguesas 
 	Equipo 3 -----------ingredientes : ----------
	Equipo 3 ingrediente  0 : hamburguesa_1 
	Equipo 3 ingrediente  1 : hamburguesa_2 
--------------------------------------------------
--------------------------------------------------x
	Equipo 2 - accion armar_medallones 
 	Equipo 2 -----------ingredientes : ----------
--------------------------------------------------
--------------------------------------------------x
	Equipo 1 - accion cocinar_medallones 
 	Equipo 1 -----------ingredientes : ----------
--------------------------------------------------
	---------------EQUIPO 3 ES EL GANADOR!!!-------------










