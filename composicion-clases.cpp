#include <iostream>
#include <string>
using namespace std;
// ============================================================================
// CLASE COMPONENTE: FECHA
// ============================================================================
class Fecha {
private:
    int dia;
    int mes;
    int agno;

public:
    // NOTA: Al definir este constructor parametrizado, el compilador NO generará
    // el constructor por defecto automático. Esto obligará a inicializarlo explícitamente.
    Fecha(int d, int m, int a) : dia(d), mes(m), agno(a) {
        cout << "   >>> [Constructor Fecha] Inicializando memoria para: " 
                  << dia << "/" << mes << "/" << agno << endl;
    }

    // Métodos constantes de acceso (Solo lectura para mantener la protección)
    int obtenerDia() const { return dia; }
    int obtenerMes() const { return mes; }
    int obtenerAgno() const { return agno; }

    void mostrar() const {
        cout << dia << "/" << mes << "/" << agno;
    }
};

// ============================================================================
// CLASE CONTENEDORA: FICHA (Expediente del Colaborador)
// ============================================================================
class Ficha {
private:
    string nombre;
    string departamento;
    const Fecha cumple; // Subobjeto constante por composición (Tiene un)

public:
    // ------------------------------------------------------------------------
    // CONSTRUCTOR CORRECTO (Utiliza lista de inicialización de miembros)
    // ------------------------------------------------------------------------
    Ficha(string n, string dep, int d, int m, int a) 
        : nombre(n)
        , departamento(dep)
        , cumple(d, m, a) // Fuerza la invocación directa del constructor de Fecha
    {
        cout << "[Constructor Ficha] Ficha del colaborador creada." << endl;
    }

    // ------------------------------------------------------------------------
    // TRAMPA PEDAGÓGICA: Descomenta este bloque y comenta el constructor de arriba 
    // para observar el bloqueo inmediato del compilador.
    // ------------------------------------------------------------------------
    /*
    Ficha(string n, string dep, int d, int m, int a) {
        nombre = n;
        departamento = dep;
        
        // Intento de inicialización por asignación o modificadores:
        // cumple = Fecha(d, m, a); // ERROR: 'cumple' es constante y no permite asignación.
    }
    */

    void mostrarFicha() const {
        cout << "========================================" << endl;
        cout << "  COLABORADOR: " << nombre << endl;
        cout << "  DEPARTAMENTO: " << departamento << endl;
        cout << "  CUMPLEANOS: ";
        cumple.mostrar(); // Acceso controlado a los servicios del subobjeto cumple
        cout << endl;
        cout << "========================================" << endl;
    }
};

// ============================================================================
// PROGRAMA PRINCIPAL
// ============================================================================
int main() {
    cout << "--- Creando Expedientes de la Universidad ---" << endl;
    
    // Instanciación de objetos compuestos
    Ficha colaborador1("Juan Perez", "Sistemas", 14, 8, 1995);
    colaborador1.mostrarFicha();

    Ficha colaborador2("Maria Gomez", "Logistica", 3, 5, 1998);
    colaborador2.mostrarFicha();

    return 0;
}