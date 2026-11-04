# Práctica Guiada de Laboratorio: Simulador de Cola de Atención al Cliente (Cola FIFO Manual con Nodos)

**Asignatura:** Programación Avanzada y Algoritmos  
**Tema:** 3.4 Listas y Colas (Implementación Manual sin STL)  
**Duración Estimada:** 60 a 80 minutos  
**Modalidad:** Individual / Parejas (en entorno de laboratorio C++)  

---

## 1. Objetivos de Aprendizaje

1. **Construcción y Manejo de Nodos en Memoria Dinámica:** Comprender la estructura interna de un nodo dinámico (`struct`) que contiene datos y punteros autorreferenciados asignados en el Montículo (*Heap*).
2. **Arquitectura FIFO (*First-In, First-Out*) con Punteros Dobles:** Diseñar e implementar una cola de atención manual gestionada mediante punteros independientes de extremo: `frente` (*front*) y `final` (*back*).
3. **Eficiencia Algorítmica $\mathcal{O}(1)$:** Implementar las operaciones fundamentales de encolar (`encolar`) y desencolar (`desencolar`) garantizando un tiempo de ejecución constante sin necesidad de recorrer la lista.
4. **Prevención de Punteros Colgados (*Dangling Pointers*) y Fugas de Memoria:** Aplicar la gestión limpia de memoria dinámica en C++, gestionando correctamente los casos límite (como desencolar el único elemento restante) y liberando toda la memoria en el destructor de la clase.

---

## 2. Escenario y Problemática Industrial

Una sucursal bancaria de alto flujo requiere renovar su sistema de gestión de turnos para el área de cajas. El sistema debe registrar la llegada de los clientes asignándoles un número de turno y un nombre, y debe atenderlos en un orden estrictamente secuencial **FIFO** (*First-In, First-Out*): el primer cliente en llegar a la sucursal es el primero en ser atendido por el cajero.

Por restricciones de arquitectura de sistemas embebidos en los terminales de turno, **está prohibido utilizar la biblioteca estándar de plantillas (`std::queue` o `std::list`)**. El equipo de desarrollo debe implementar una solución limpia, modular y segura desde cero en C++ utilizando memoria dinámica gestionada manualmente mediante punteros.

---

## 3. Demostración Teórica: La Trampa Pedagógica del "Puntero Colgado"

Al implementar una cola FIFO manual con punteros `frente` y `final`, existe un error de diseño muy común que suele provocar errores de segmentación (*Segmentation Fault*) o comportamientos indefinidos impredecibles.

### El Caso Límite de la Cola con 1 Solo Elemento

Cuando la cola contiene **un único nodo**, tanto el puntero `frente` como el puntero `final` apuntan a la misma dirección de memoria en el *Heap*:

```text
  [frente] ──────────┐
                     ▼
                 ┌───────────────┬────────┐
                 │ Cliente: Ana  │  sig   │ ──► nullptr
                 └───────────────┴────────┘
                     ▲
  [final]  ──────────┘
```

Si el estudiante implementa el método `desencolar()` de forma ingenuo:

```cpp
// ❌ CÓDIGO INCORRECTO CON ERROR DE PUNTERO COLGADO
void desencolarIncorrecto() {
    if (frente == nullptr) return; // Cola vacía
    
    NodoCliente* aux = frente;
    frente = frente->sig; // frente pasa a ser nullptr
    delete aux;           // Se libera el nodo en el Heap
    
    // ERROR CRÍTICO: ¡No se actualizó el puntero 'final'!
    // 'final' sigue apuntando a la memoria liberada por 'aux' (Dangling Pointer).
}
```

### ¿Qué sucede en la siguiente inserción (`encolar`)?

Si posteriormente se intenta encolar un nuevo cliente (`Carlos`), el método `encolar()` intentará acceder a `final->sig = nuevoNodo;`. Como `final` contiene una dirección de memoria que ya fue liberada con `delete`, el programa intentará escribir en un área de memoria no válida, provocando una caída por **Segmentation Fault**.

### La Solución Correcta

Es indispensable verificar si, tras avanzar `frente`, la cola ha quedado completamente vacía. En dicho caso, debe forzarse `final = nullptr;`:

```cpp
// ✅ CÓDIGO CORRECTO Y SEGURO
void desencolarCorrecto() {
    if (frente == nullptr) return;
    
    NodoCliente* aux = frente;
    frente = frente->sig;
    delete aux;
    
    // Si la cola se quedó sin elementos, corregir el puntero final
    if (frente == nullptr) {
        final = nullptr;
    }
}
```

---

## 4. Código Fuente C++ Completo y Funcional

A continuación se presenta la implementación completa en un único archivo C++ compilable.

```cpp
/**
 * ============================================================================
 * Práctica Guiada: Simulador de Cola FIFO Manual de Atención al Cliente
 * Asignatura: Programación Avanzada y Algoritmos
 * ============================================================================
 */

#include <iostream>
#include <string>

// ----------------------------------------------------------------------------
// 1. Estructura de Nodo para el Cliente
// ----------------------------------------------------------------------------
struct NodoCliente {
    int numeroTurno;
    std::string nombreCliente;
    NodoCliente* sig; // Puntero al siguiente cliente en la fila

    // Constructor del Nodo
    NodoCliente(int turno, const std::string& nombre) 
        : numeroTurno(turno), nombreCliente(nombre), sig(nullptr) {}
};

// ----------------------------------------------------------------------------
// 2. Clase Contenedora: ColaAtencion
// ----------------------------------------------------------------------------
class ColaAtencion {
private:
    NodoCliente* frente; // Apunta al primer cliente a ser atendido (salida)
    NodoCliente* final;  // Apunta al último cliente que llegó (entrada)
    int totalClientes;   // Contador de clientes actualmente en la cola

public:
    // Constructor: Inicializa la cola vacía
    ColaAtencion() : frente(nullptr), final(nullptr), totalClientes(0) {}

    // Destructor: Garantiza la liberación limpia de memoria dinámica (RAII)
    ~ColaAtencion() {
        vaciarCola();
    }

    // Prohibir copias explícitamente para evitar punteros duplicados en el Heap
    ColaAtencion(const ColaAtencion&) = delete;
    ColaAtencion& operator=(const ColaAtencion&) = delete;

    // ------------------------------------------------------------------------
    // Método: estaVacia
    // ------------------------------------------------------------------------
    bool estaVacia() const {
        return frente == nullptr;
    }

    // ------------------------------------------------------------------------
    // Método: encolar (Enqueue) - Complejidad O(1)
    // Agrega un nuevo cliente al final de la cola.
    // ------------------------------------------------------------------------
    void encolar(int turno, const std::string& nombre) {
        NodoCliente* nuevo = new NodoCliente(turno, nombre);

        if (estaVacia()) {
            // Si la cola está vacía, el nuevo nodo es tanto el frente como el final
            frente = nuevo;
            final = nuevo;
        } else {
            // Conectar el nuevo nodo al final existente y actualizar 'final'
            final->sig = nuevo;
            final = nuevo;
        }
        totalClientes++;
        std::cout << " -> [REGISTRO] Cliente '" << nombre << "' con Turno #" 
                  << turno << " ingresó a la cola.\n";
    }

    // ------------------------------------------------------------------------
    // Método: desencolar (Dequeue) - Complejidad O(1)
    // Atiende y elimina al cliente ubicado al frente de la cola.
    // ------------------------------------------------------------------------
    bool desencolar() {
        if (estaVacia()) {
            std::cout << " ⚠️  [ADVERTENCIA] No hay clientes en espera para atender.\n";
            return false;
        }

        // Respaldar el nodo del frente
        NodoCliente* aux = frente;

        std::cout << " <- [ATENCIÓN] Atendiendo a '" << aux->nombreCliente 
                  << "' (Turno #" << aux->numeroTurno << ")...\n";

        // Avanzar el puntero frente
        frente = frente->sig;

        // Liberar la memoria dinámica del nodo atendido
        delete aux;
        totalClientes--;

        // CONTROL DE PUNTERO COLGADO:
        // Si la cola quedó vacía tras la eliminación, final debe ser nullptr
        if (frente == nullptr) {
            final = nullptr;
        }

        return true;
    }

    // ------------------------------------------------------------------------
    // Método: verFrente (Peek) - Complejidad O(1)
    // Muestra los datos del cliente al frente sin desencolarlo.
    // ------------------------------------------------------------------------
    void verFrente() const {
        if (estaVacia()) {
            std::cout << " ℹ️  [INFO] La cola está completamente vacía.\n";
        } else {
            std::cout << " 🔍 [Siguiente en Fila] Turno #" << frente->numeroTurno 
                      << " - " << frente->nombreCliente << "\n";
        }
    }

    // ------------------------------------------------------------------------
    // Método: mostrarCola - Complejidad O(N)
    // Recorre e imprime la cola de clientes desde el frente hasta el final.
    // ------------------------------------------------------------------------
    void mostrarCola() const {
        if (estaVacia()) {
            std::cout << "\n --- Estado de la Cola: (VACÍA) ---\n";
            return;
        }

        std::cout << "\n --- Estado de la Cola de Atención (Total: " 
                  << totalClientes << ") ---\n";
        std::cout << " [FRENTE] ";

        NodoCliente* actual = frente;
        while (actual != nullptr) {
            std::cout << "[#" << actual->numeroTurno << ": " 
                      << actual->nombreCliente << "]";
            if (actual->sig != nullptr) {
                std::cout << " ──► ";
            }
            actual = actual->sig;
        }
        std::cout << " [FINAL]\n\n";
    }

    // ------------------------------------------------------------------------
    // Método: vaciarCola - Libera todos los nodos restantes en el Heap
    // ------------------------------------------------------------------------
    void vaciarCola() {
        int eliminados = 0;
        while (frente != nullptr) {
            NodoCliente* aux = frente;
            frente = frente->sig;
            delete aux;
            eliminados++;
        }
        final = nullptr;
        totalClientes = 0;
        if (eliminados > 0) {
            std::cout << " 🧹 [DESTRUCTOR] Se liberaron " << eliminados 
                      << " nodo(s) de la memoria Heap.\n";
        }
    }

    // Obtener total de clientes activos
    int getTotalClientes() const { return totalClientes; }
};

// ----------------------------------------------------------------------------
// 3. Función Principal (main)
// ----------------------------------------------------------------------------
int main() {
    std::cout << "=========================================================\n";
    std::cout << "  SISTEMA DE GESTIÓN DE TURNOS (COLA FIFO MANUAL C++)\n";
    std::cout << "=========================================================\n\n";

    // Instanciación de la cola de atención en el Stack
    ColaAtencion cola;

    // 1. Inserción de clientes iniciales
    cola.encolar(101, "Ana Martinez");
    cola.encolar(102, "Bruno Diaz");
    cola.encolar(103, "Carla Gomez");
    cola.mostrarCola();

    // 2. Consulta del cliente en turno
    cola.verFrente();
    std::cout << "\n";

    // 3. Atención de los primeros 2 clientes
    cola.desencolar();
    cola.desencolar();
    cola.mostrarCola();

    // 4. Llegada de un nuevo cliente
    cola.encolar(104, "David Lopez");
    cola.mostrarCola();

    // 5. Atender a todos hasta vaciar la cola (Probando caso límite)
    std::cout << "--- Atendiendo a los clientes restantes ---\n";
    cola.desencolar(); // Atiende a Carla (Queda solo David)
    cola.desencolar(); // Atiende a David (La cola se vacía completamente)

    // 6. Intento de desencolar sobre cola vacía
    cola.desencolar();

    // 7. Reinsertar tras vaciado para verificar integridad del puntero 'final'
    std::cout << "\n--- Verificación de Integridad tras Vaciado Completo ---\n";
    cola.encolar(105, "Elena Torres");
    cola.mostrarCola();

    std::cout << "Fin del programa. Al salir del ámbito se ejecutará el destructor...\n";
    return 0;
}
```

---

## 5. Desglose Temporal de la Sesión (80 Minutos)

| Intervalo | Tiempo | Actividad del Estudiante | Rol del Docente |
| :---: | :---: | :--- | :--- |
| **00 – 15 min** | 15 min | Exposición teórica del funcionamiento de la Cola FIFO, arquitectura de punteros `frente`/`final` y demostración del caso límite de punteros colgados. | Presentación con apoyo de diagrama de nodos en pizarrón. Explicación de la trampa pedagógica. |
| **15 – 35 min** | 20 min | Declaración de la estructura `NodoCliente` y la clase `ColaAtencion`. Codificación del constructor, destructor y método `estaVacia()`. | Supervisión del uso correcto de punteros e inicializadores en la lista de inicialización de C++. |
| **35 – 60 min** | 25 min | Implementación de las funciones centrales: `encolar()` (con enlace por `final`) y `desencolar()` (con la validación del puntero colgado). | Revisión individual del control del caso límite cuando `frente == nullptr`. |
| **60 – 75 min** | 15 min | Codificación de la función `main()`, ejecución de pruebas interactivas en consola y verificación de ausencia de *memory leaks*. | Apoyo en la depuración de errores de compilación y verificación de punteros. |
| **75 – 80 min** | 5 min | Limpieza del entorno de trabajo, entrega del código fuente y resolución de dudas finales. | Cierre pedagógico y retroalimentación colectiva. |

---

## 6. Cuestionario de Control Técnico

### Pregunta 1
**¿Por qué en una Cola FIFO implementada con punteros `frente` y `final` tanto la operación `encolar` como `desencolar` tienen una complejidad de tiempo de $\mathcal{O}(1)$?**

> **Respuesta Esperada:**  
> Porque la clase mantiene referencias directas a los dos extremos de la estructura mediante los punteros `frente` y `final`. Al `encolar`, el nuevo elemento se engancha de forma directa utilizando `final->sig` y se actualiza `final`. Al `desencolar`, se remueve directamente el nodo apuntado por `frente`. Ninguna de las dos operaciones requiere recorrer iterativamente los nodos de la cola, por lo que el tiempo de ejecución es constante e independiente de la cantidad de elementos.

---

### Pregunta 2
**Si se desencola el único elemento de la cola y el programador realiza `delete frente; frente = nullptr;` pero olvida la sentencia `final = nullptr;`, ¿qué problema ocurre en la posterior llamada a `encolar()`?**

> **Respuesta Esperada:**  
> Ocurre un error de **puntero colgado (*Dangling Pointer*)** que provoca un fallo de segmentación (*Segmentation Fault*). Cuando la cola tiene 1 elemento, `frente` y `final` apuntan al mismo nodo. Si se libera la memoria de `frente` sin actualizar `final`, el puntero `final` mantendrá una dirección de memoria inválida. Al intentar llamar a `encolar()`, la línea `final->sig = nuevo;` intentará escribir en la memoria liberada, colapsando el programa.

---

### Pregunta 3
**¿Cómo garantiza el destructor `~ColaAtencion()` la prevención de fugas de memoria (*Memory Leaks*) al finalizar la ejecución del programa?**

> **Respuesta Esperada:**  
> El destructor aplica el principio **RAII** (*Resource Acquisition Is Initialization*) invocando al método `vaciarCola()`. Este método ejecuta un bucle `while (frente != nullptr)` que recorre nodo por nodo liberando explícitamente la memoria reservada en el *Heap* mediante el operador `delete` antes de que el objeto de la cola sea destruido en el *Stack*.

---

## 7. Rúbrica de Evaluación Académica

| Criterio de Evaluación | Ponderación | Excelente (100%) | Aceptable (70–89%) | Insuficiente (<70%) |
| :--- | :---: | :--- | :--- | :--- |
| **1. Estructura del Nodo y Encapsulamiento** | **25%** | Declara correctamente la estructura `NodoCliente` con punteros autorreferenciados. Encapsula los punteros `frente` y `final` como miembros privados de `ColaAtencion`. | Implementa el nodo y la clase, pero expone los atributos privados como públicos o presenta deficiencias en el constructor. | No logra estructurar correctamente el nodo o la clase contenedora de la cola. |
| **2. Lógica FIFO (`encolar` y `desencolar`)** | **30%** | Implementa `encolar()` y `desencolar()` con complejidad $\mathcal{O}(1)$ real, respetando el orden de llegada de los elementos sin recorridos innecesarios. | Las funciones operan correctamente en casos normales, pero presentan ineficiencias (como recorridos $\mathcal{O}(N)$) o detalles sintácticos menores. | La lógica de encolado/desencolado altera el orden FIFO o genera errores lógicos graves. |
| **3. Control de Memoria Dinámica y Punteros Colgados** | **25%** | Maneja adecuadamente la liberación de nodos con `delete`. Controla explícitamente el caso límite de 1 elemento ajustando `final = nullptr`. Destructor sin *memory leaks*. | Realiza la liberación de memoria, pero omite la validación del puntero colgado en el caso límite o presenta fugas menores al vaciar. | No libera la memoria con `delete`, genera *Segmentation Faults* o provoca desbordamientos en el *Heap*. |
| **4. Correctitud y Pruebas en `main()`** | **10%** | El programa compila sin advertencias (*warnings*). Realiza pruebas completas de inserción, atención, vaciado y reinserción exitosa. | El programa compila y funciona en los casos generales, pero falla o muestra salidas confusas en casos de cola vacía. | El programa no compila o se colapsa durante las pruebas de ejecución. |
| **5. Estilo y Buenas Prácticas en C++** | **10%** | Código limpio, bien comentado, formato monospaciado uniforme, nombres de variables descriptivos y uso de `const` en métodos de consulta. | Código funcional pero con comentarios escasos, nombres de variables poco claros o problemas menores de formato. | Código desordenado, sin comentarios y con malas prácticas de programación estructurada. |
