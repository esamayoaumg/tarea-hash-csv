# tarea-hash-csv


# Explicacion del Proyecto: Guardar Datos de Estudiantes usando Tablas Hash

Este proyecto tiene dos programas (uno en C++ y otro en Java) que hacen exactamente lo mismo: leen un archivo con una lista de estudiantes (un archivo separado por comas llamado CSV), guardan la informacion en la memoria de la computadora de forma organizada y permiten buscar o borrar a cualquier estudiante ingresando su numero de ID.

---

## 1. ¿Como funciona el programa en C++? (Hecho a mano)

En C++ tuvimos que construir todo desde cero, como si armaramos un mueble pieza por pieza.

* **La Caja de Datos:** Creamos un contenedor para guardar los datos de cada estudiante (ID, Nombre, Carrera, Semestre, Notas) y lo conectamos a un "gancho" llamado Nodo.
* **El Organizador:** Imaginemos un casillero con 10 cajones. Cuando llega un estudiante, el programa usa una formula matematica simple (tomar su ID y ver cuanto sobra al dividirlo entre 10) para decidir en que cajon ponerlo.
* **¿Que pasa si dos estudiantes van al mismo cajon? (Colision):** Como no queremos que un estudiante borre a otro, los colgamos juntos en el mismo cajon usando una cadena de ganchos (Lista Enlazada). Si un cajon ya tiene a alguien, el nuevo estudiante se engancha al principio de la fila.
* **Limpieza de Memoria:** En C++ la computadora no limpia sola. Por eso, programamos un "destructor" que, al cerrar el juego o menu, saca a todos los estudiantes de los ganchos y limpia los cajones para no dejar trabada la memoria de la computadora.

---

## 2. ¿Como funciona el programa en Java? (Usando herramientas listas)

En Java no tuvimos que fabricar los cajones ni los ganchos a mano. Usamos una herramienta que ya viene incluida en el lenguaje llamada `HashMap`.

* **El Diccionario Automatico:** `HashMap` funciona como un diccionario de contactos del telefono. Tu guardas el numero de ID (que es la llave) y el telefono te da el perfil completo del estudiante (el valor).
* **Trabajo Automatico:** Java se encarga de calcular en que cajon va cada quien y de acomodar a los estudiantes si se juntan en el mismo lugar. Si el espacio se empieza a llenar, el mismo programa hace los casilleros mas grandes sin que nosotros se lo pidamos.
* **Limpieza Automatica:** Aqui no hace falta programar un limpiador. Java tiene un asistente interno (Recolector de Basura) que borra de la memoria todo lo que ya no se usa cuando cerramos el programa.

---

## 3. ¿Como se leen los archivos?

Ambos programas abren el archivo `estudiantes.csv`, descartan la primera linea (donde estan los titulos de las columnas) y leen el texto renglon por renglon.

* **En C++:** El programa lee el renglon completo y corta el texto cada vez que encuentra una coma para separar el ID, el Nombre y las Notas, y luego manda al estudiante a su cajon.
* **En Java:** Usamos una funcion que corta la linea en pedazos automaticamente usando las comas y guarda cada dato en una casilla para armar la ficha del estudiante de forma mas directa.

---

## 4. Resumen de Diferencias (C++ vs Java)

* **C++ es como un carro mecanico:** Tu tienes el control total de cada pieza, de los ganchos y de la memoria. Aprendes como funciona todo por dentro, pero es mas facil cometer un error si olvidas conectar un gancho.
* **Java es como un carro automatico:** Tu solo manejas. Le dices "guarda esto" o "busca esto" y el programa lo hace de inmediato de forma segura, sin preocuparte por ganchos rotos o cajones llenos.
