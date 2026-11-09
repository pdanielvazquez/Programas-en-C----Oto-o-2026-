# Práctica Guiada de Laboratorio: Red de Rutas e Inspección de Saltos Mínimos (Grafo con Lista de Adyacencia y BFS)

**Asignatura:** Programación Avanzada y Algoritmos  
**Tema:** 3.5 Árboles y Grafos (Grafos, Listas de Adyacencia y Búsqueda en Anchura - BFS)  
**Duración Estimada:** 60 a 80 minutos  
**Modalidad:** Individual / Parejas (en entorno de laboratorio C++)  

---

## 1. Objetivos de Aprendizaje

1. **Representación Eficiente de Grafos en C++:** Diseñar e implementar una red de nodos mediante una Lista de Adyacencia (`std::vector<std::vector<int>>`), comprendiendo la optimización de espacio en memoria $\mathcal{O}(V + E)$ para grafos dispersos.
2. **Algoritmo de Búsqueda en Anchura (BFS - *Breadth-First Search*):** Implementar la exploración por niveles utilizando una cola (`std::queue<int>`) para determinar la ruta con el menor número de saltos o tramos intermedios entre dos vértices.
3. **Control de Estados y Prevención de Ciclos:** Aplicar un vector de visitados (`std::vector<bool>`) y gestionar correctamente el marcado inmediato de nodos al momento de su encolado para evitar redundancia y desbordamientos de memoria.
4. **Reconstrucción de Caminos Mínimos:** Almacenar la jerarquía de predecesores mediante un vector de padres (`std::vector<int> padre`) para reconstruir y desplegar la secuencia exacta de nodos del camino óptimo.

---

## 2. Escenario y Problemática Industrial

Una empresa de logística y distribución metropolitana opera una red de centros de transferencia para la entrega rápida de paquetes. Debido a restricciones operativas en los peajes y tiempos de carga/descarga en cada centro intermediario, la empresa requiere minimizar el **número total de saltos o tramos** que realiza un paquete desde la sucursal de origen hasta la sucursal de destino.

El equipo de desarrollo de software debe construir un módulo en C++ que represente la red de distribución como un **grafo no dirigido e inponderado**. El sistema debe ofrecer métodos para registrar conexiones entre centros, visualizar la topología de la red mediante listas de adyacencia y ejecutar un algoritmo determinista (BFS) que devuelva la distancia en saltos y la secuencia de sucursales que componen la ruta más corta.

---

## 3. Demostración Teórica: La Trampa Pedagógica del "Marcado Tardío de Visitados"

Al implementar el algoritmo BFS para recorrer grafos, existe un error clásico de diseño que degrada severamente el rendimiento y puede provocar el agotamiento de la memoria del sistema.

### El Error: Marcar como Visitado al Desencolar (`pop`)

Muchos estudiantes cometen la equivocación de marcar un nodo como visitado únicamente cuando este es extraído de la cola para su procesamiento:

```cpp
// ❌ CÓDIGO INCORRECTO: Marcado tardío al desencolar
void bfsIncorrecto(int origen) {
    std::queue<int> q;
    std::vector<bool> visitado(numVertices, false);
    
    q.push(origen);
    // NOTA: No se marca 'visitado[origen] = true' aquí
    
    while (!q.empty()) {
        int actual = q.front();
        q.pop();
        
        // El nodo se marca como visitado HASTA que sale de la cola
        visitado[actual] = true;
        
        for (int vecino : listaAdyacencia[actual]) {
            if (!visitado[vecino]) {
                q.push(vecino); // ⚠️ ¡Se inserta 'vecino' múltiples veces!
            }
        }
    }
}
```

### ¿Por qué este enfoque destruye el rendimiento?

Considere un nodo $B$ que es vecino común de tres nodos distintos ($A_1, A_2, A_3$) ubicados en el mismo nivel. Si el nodo $B$ no se marca como visitado inmediatamente en el momento en que el primer nodo $A_1$ lo descubre y lo encola con `push()`:

1. Cuando el algoritmo explora los vecinos de $A_1$, observa que $B$ no está visitado y ejecuta `q.push(B)`.
2. Cuando el algoritmo pasa a explorar los vecinos de $A_2$, observa que $B$ sigue figurando como `false` en el vector de visitados (porque aún no ha sido desencolado), y vuelve a ejecutar `q.push(B)`.
3. Lo mismo ocurre con $A_3$, encolando el nodo $B$ por tercera vez.

En grafos medianos o densos, esta duplicación masiva provoca que la cola crezca de forma exponencial, duplicando miles de veces los mismos nodos en memoria y arruinando la complejidad temporal de $\mathcal{O}(V + E)$.

### La Solución Correcta: Marcado Inmediato al Encolar (`push`)

El nodo **debe marcarse como visitado en el instante exacto en que se inserta en la cola**, impidiendo que cualquier otro vecino vuelva a encolarlo:

```cpp
// ✅ CÓDIGO CORRECTO: Marcado inmediato al encolar
void bfsCorrecto(int origen) {
    std::queue<int> q;
    std::vector<bool> visitado(numVertices, false);
    
    // Se marca e inserta el origen simultáneamente
    visitado[origen] = true;
    q.push(origen);
    
    while (!q.empty()) {
        int actual = q.front();
        q.pop();
        
        for (int vecino : listaAdyacencia[actual]) {
            if (!visitado[vecino]) {
                visitado[vecino] = true; // 🔒 Bloqueo inmediato contra duplicados
                q.push(vecino);
            }
        }
    }
}
```

---

## 4. Código Fuente C++ Completo y Funcional

A continuación se presenta la implementación completa en C++ compilable (`g++ -Wall -std=c++17 main.cpp`).

```cpp
/**
 * ============================================================================
 * Práctica Guiada: Red de Rutas e Inspección de Saltos Mínimos (BFS)
 * Asignatura: Programación Avanzada y Algoritmos
 * Tema: 3.5 Árboles y Grafos
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

class RedDistribucion {
private:
    int numVertices;
    std::vector<std::vector<int>> listaAdyacencia;
    std::vector<std::string> nombresSucursales;

public:
    // Constructor
    RedDistribucion(int vertices) : numVertices(vertices) {
        listaAdyacencia.resize(numVertices);
        nombresSucursales.resize(numVertices);
        for (int i = 0; i < numVertices; ++i) {
            nombresSucursales[i] = "Sucursal " + std::to_string(i);
        }
    }

    // Asignar un nombre descriptivo a una sucursal
    void setNombreSucursal(int id, const std::string& nombre) {
        if (id >= 0 && id < numVertices) {
            nombresSucursales[id] = nombre;
        }
    }

    // Agregar una conexión bidireccional (Grafo No Dirigido)
    void agregarConexion(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            listaAdyacencia[u].push_back(v);
            listaAdyacencia[v].push_back(u); // Grafo no dirigido
        } else {
            std::cerr << "[ERROR] Identificador de sucursal fuera de rango (" 
                      << u << " - " << v << ").\n";
        }
    }

    // Mostrar la topología de la red mediante Lista de Adyacencia
    void mostrarRed() const {
        std::cout << "\n======================================================\n";
        std::cout << "        TOPOLOGÍA DE LA RED DE DISTRIBUCIÓN           \n";
        std::cout << "======================================================\n";
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "[" << i << "] " << nombresSucursales[i] << " -> ";
            for (size_t j = 0; j < listaAdyacencia[i].size(); ++j) {
                int vecino = listaAdyacencia[i][j];
                std::cout << nombresSucursales[vecino] << " (" << vecino << ")";
                if (j + 1 < listaAdyacencia[i].size()) std::cout << ", ";
            }
            std::cout << "\n";
        }
        std::cout << "------------------------------------------------------\n";
    }

    // Algoritmo BFS para encontrar la ruta con menor número de saltos
    void buscarRutaMinimaBFS(int origen, int destino) const {
        if (origen < 0 || origen >= numVertices || destino < 0 || destino >= numVertices) {
            std::cout << "[ERROR] Origen o destino inválidos.\n";
            return;
        }

        std::cout << "\n------------------------------------------------------\n";
        std::cout << "Buscando ruta mínima entre: " << nombresSucursales[origen] 
                  << " -> " << nombresSucursales[destino] << "\n";
        std::cout << "------------------------------------------------------\n";

        // Estructuras auxiliares para BFS
        std::vector<bool> visitado(numVertices, false);
        std::vector<int> distancia(numVertices, -1);
        std::vector<int> padre(numVertices, -1);
        std::queue<int> q;

        // Marcado e inserción inicial del nodo origen
        visitado[origen] = true;
        distancia[origen] = 0;
        q.push(origen);

        bool encontrado = false;

        while (!q.empty()) {
            int actual = q.front();
            q.pop();

            if (actual == destino) {
                encontrado = true;
                break; // Se alcanzó el destino deseado
            }

            for (int vecino : listaAdyacencia[actual]) {
                if (!visitado[vecino]) {
                    visitado[vecino] = true;       // Marcado inmediato
                    distancia[vecino] = distancia[actual] + 1;
                    padre[vecino] = actual;          // Registro de precedencia
                    q.push(vecino);
                }
            }
        }

        if (!encontrado) {
            std::cout << "❌ No existe ninguna ruta disponible entre " 
                      << nombresSucursales[origen] << " y " 
                      << nombresSucursales[destino] << ".\n";
            return;
        }

        // Reconstrucción de la ruta desde el destino hacia el origen
        std::vector<int> ruta;
        int curr = destino;
        while (curr != -1) {
            ruta.push_back(curr);
            curr = padre[curr];
        }
        std::reverse(ruta.begin(), ruta.end());

        // Despliegue de resultados
        std::cout << "✅ Ruta Mínima Encontrada:\n";
        std::cout << "   - Distancia Total (Saltos/Tramos): " << distancia[destino] << "\n";
        std::cout << "   - Secuencia de Trayecto: ";
        for (size_t i = 0; i < ruta.size(); ++i) {
            std::cout << nombresSucursales[ruta[i]] << " [" << ruta[i] << "]";
            if (i + 1 < ruta.size()) std::cout << " ──► ";
        }
        std::cout << "\n------------------------------------------------------\n";
    }
};

int main() {
    // Instanciar red logística con 7 centros de distribución (Nodos 0 al 6)
    RedDistribucion red(7);

    // Personalizar nombres de las sucursales
    red.setNombreSucursal(0, "Centro Matriz CDMX");
    red.setNombreSucursal(1, "Hub Toluca");
    red.setNombreSucursal(2, "Hub Querétaro");
    red.setNombreSucursal(3, "Bodega Pachuca");
    red.setNombreSucursal(4, "Centro Puebla");
    red.setNombreSucursal(5, "Hub San Luis Potosí");
    red.setNombreSucursal(6, "Terminal Monterrey");

    // Construir conexiones de la red logística
    red.agregarConexion(0, 1); // CDMX <-> Toluca
    red.agregarConexion(0, 2); // CDMX <-> Querétaro
    red.agregarConexion(0, 3); // CDMX <-> Pachuca
    red.agregarConexion(1, 4); // Toluca <-> Puebla
    red.agregarConexion(2, 5); // Querétaro <-> San Luis Potosí
    red.agregarConexion(3, 4); // Pachuca <-> Puebla
    red.agregarConexion(5, 6); // San Luis Potosí <-> Monterrey

    // Mostrar topología
    red.mostrarRed();

    // Consulta 1: Ruta entre CDMX (0) y Monterrey (6)
    red.buscarRutaMinimaBFS(0, 6);

    // Consulta 2: Ruta entre Puebla (4) y San Luis Potosí (5)
    red.buscarRutaMinimaBFS(4, 5);

    return 0;
}
```

---

## 5. Guión de Laboratorio Paso a Paso (Planificación de 80 Minutos)

Para asegurar la consecución de los objetivos pedagógicos en la sesión de 80 minutos, se recomienda seguir el siguiente cronograma de trabajo:

### Fase 1: Introducción Teórica y Configuración (00–15 min)
* Explicación de la representación de grafos mediante Listas de Adyacencia vs. Matrices de Adyacencia.
* Revisión del concepto de BFS y demostración del riesgo de marcado tardío de nodos visitados.

### Fase 2: Implementación de la Clase `RedDistribucion` (15–35 min)
* Declaración del `std::vector<std::vector<int>>` en el encabezado de la clase.
* Implementación del constructor y del método `agregarConexion()` para grafos no dirigidos.
* Verificación de la construcción correcta de la lista imprimiendo la topología en consola.

### Fase 3: Desarrollo del Algoritmo BFS y Rastreo de Padres (35–60 min)
* Integración de las estructuras auxiliares `std::queue<int>`, `visitado`, `distancia` y `padre`.
* Garantizar el marcado inmediato de `visitado[vecino] = true` durante el bucle de exploración.
* Implementación del bucle de reconstrucción de la ruta mediante `std::reverse()`.

### Fase 4: Pruebas, Casos Límite y Conclusiones (60–80 min)
* Ejecución de pruebas con distintas combinaciones de nodos de origen y destino.
* Validación de casos límite (nodos desconectados o idénticos).
* Discusión guiada respondiendo al cuestionario de control técnico.

---

## 6. Cuestionario de Control Técnico

Los estudiantes deberán resolver las siguientes preguntas de análisis conceptual al finalizar la práctica:

1. **¿Por qué el algoritmo BFS garantiza encontrar la ruta con el menor número de saltos en un grafo no ponderado, mientras que el algoritmo DFS no lo garantiza?**  
   *Respuesta esperada:* BFS explora la red nivel por nivel (en anchura), garantizando que se visiten primero todos los nodos situados a distancia 1, luego a distancia 2, etc. Por ende, la primera vez que BFS alcanza el nodo destino, la ruta descubierta es de manera determinista la más corta en número de aristas. En cambio, DFS profundiza arbitrariamente por una sola rama y puede encontrar el destino a través de un camino mucho más largo antes de explorar otras opciones.

2. **¿Qué sucede si intentamos usar BFS para encontrar la ruta más corta en una red donde las carreteras tienen distancias en kilómetros muy desiguales (grafo ponderado)?**  
   *Respuesta esperada:* BFS no considera los pesos de las aristas; asume que todas tienen el mismo costo (1). Si las aristas tienen pesos distintos, una ruta de 2 saltos que sume 500 km podría ser elegida por BFS sobre una ruta de 3 saltos que sume solo 150 km. Para grafos ponderados con pesos positivos, debe emplearse el **Algoritmo de Dijkstra**.

3. **¿Cuál es la ventaja en memoria de usar una Lista de Adyacencia en lugar de una Matriz de Adyacencia para esta red de distribución urbana?**  
   *Respuesta esperada:* Una Matriz de Adyacencia requiere un espacio fijo de $\mathcal{O}(V^2)$ (ej. para 10,000 sucursales se requerirían 100,000,000 de celdas), independientemente de cuantas conexiones existan. La Lista de Adyacencia consume únicamente $\mathcal{O}(V + E)$ espacios de memoria, guardando solo las aristas reales activas.

---

## 7. Tabla de Rúbrica de Evaluación Académica

La evaluación del desempeño de los estudiantes se realizará conforme a los siguientes criterios ponderados:

| Criterio de Evaluación | Ponderación | Excelente (100%) | Aceptable (70–89%) | Insuficiente (<70%) |
| :--- | :---: | :--- | :--- | :--- |
| **1. Representación del Grafo y Lista de Adyacencia** | **25%** | Declara y gestiona correctamente la lista de adyacencia usando vectores dinámicos. Inserta aristas bidireccionales de forma limpia. | Implementa la lista de adyacencia pero comete errores menores en la inserción bidireccional o la validación de límites. | No logra estructurar la lista de adyacencia o confunde grafos dirigidos con no dirigidos. |
| **2. Algoritmo BFS y Marcado de Visitados** | **25%** | Implementa BFS usando `std::queue` y aplica el marcado de visitados inmediatamente al encolar, evitando redundancias. | Implementa BFS pero comete el marcado de visitados al desencolar, generando duplicados innecesarios en la cola. | No utiliza una cola para el recorrido BFS o genera bucles infinitos por omitir el vector de visitados. |
| **3. Reconstrucción de la Ruta Mínima** | **25%** | Utiliza un vector de padres para rastrear y reconstruir adecuadamente la secuencia de nodos mediante inversión de elementos. | Calcula la distancia mínima correctamente pero falla en la reconstrucción del camino o imprime la ruta en orden inverso. | No almacena la información de predecesores ni logra imprimir la secuencia de nodos de la ruta. |
| **4. Análisis de Casos Límite y Cuestionario** | **15%** | Responde correctamente el cuestionario técnico y valida en código casos como nodos desconectados o fuera de rango. | Responde parcialmente el cuestionario o falta validar algún caso límite secundario en el programa. | No responde el cuestionario técnico o el programa se cae ante entradas de nodos inválidos. |
| **5. Calidad del Código, Compilación y Formato** | **10%** | El código compila sin errores ni *warnings*, tiene formato monospaciado limpio, nombres descriptivos e impresiones claras. | El código compila pero presenta problemas menores de formato, nombres poco claros o falta de comentarios. | El código no compila o presenta errores graves de sintaxis durante la ejecución. |
