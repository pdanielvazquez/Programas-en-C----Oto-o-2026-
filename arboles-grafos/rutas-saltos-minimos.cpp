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
