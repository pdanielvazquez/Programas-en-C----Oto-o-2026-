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
