// PARTE 1: Librerías y Definición de la Clase dentro del Namespace
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
namespace SeguridadNet {
	namespace ControlAcceso {
	    class SesionRed {
	    private:
	        // --- ATRIBUTOS DE INSTANCIA (Ámbito de Miembro) --
	        int idSesion;
	        std::string usuario;
	        std::string ipOrigen;
	        // --- ATRIBUTOS DE CLASE (Ámbito de Clase / Static) --
	        static int sesionesActivas;
	        static int contadorCorrelativoId;
	        static const int MAX_SESIONES = 3; // Límite estricto de concurrencia
	    public:
	        // Constructor parametrizado con SHADOWING (Ocultamiento)
	        SesionRed(std::string usuario, std::string ipOrigen) {
	            if (sesionesActivas >= MAX_SESIONES) {
	                throw std::runtime_error("ERROR 403: Límite de sesiones alcanzado (" 
	                                         + std::to_string(MAX_SESIONES) + ").");
	            }
	            // Desambiguación explícita mediante el puntero this->
	            this->usuario = usuario;   // Atributo = Parámetro local
	            this->ipOrigen = ipOrigen; // Atributo = Parámetro local
	            contadorCorrelativoId++;
	            this->idSesion = contadorCorrelativoId;
	            sesionesActivas++;
	            std::cout << " [+] [SESIÓN INICIADA] ID: " << idSesion 
	                      << " | Usuario: " << this->usuario 
	                      << " | IP: " << this->ipOrigen 
	                      << " (Activas: " << sesionesActivas << "/" << MAX_SESIONES << ")\n";
	        }
	        // Destructor: Se ejecuta al salir del Ámbito Local del objeto
	        ~SesionRed() {
	            sesionesActivas--;
	            std::cout << " [-] [SESIÓN CERRADA] ID: " << idSesion 
	                      << " | Usuario: " << usuario 
	                      << " (Activas restantes: " << sesionesActivas << ")\n";
	        }
	        // Métodos Estáticos (Ámbito de Clase)
	        static int obtenerSesionesActivas() { return sesionesActivas; }
	        static int obtenerMaxSesiones() { return MAX_SESIONES; }
	        void mostrarInfo() const {
	            std::cout << "     Detail -> ID: " << idSesion << " | User: " << usuario 
	                      << " | IP: " << ipOrigen << "\n";
	        }
	    };
	
		// PARTE 2: Inicialización de Miembros Estáticos fuera de la clase
	    // Asignación de memoria única en el Data Segment
	    int SesionRed::sesionesActivas = 0;
	    int SesionRed::contadorCorrelativoId = 1000;
	    
	} // namespace ControlAcceso
} // namespace SeguridadNet

// PARTE 3: Función Main y Pruebas de Ámbito
int main() {
    using namespace SeguridadNet::ControlAcceso;
    std::cout << "==========================================================" << std::endl;
    std::cout << " AUDITORÍA DE SESIONES - DEMOSTRACIÓN DE ÁMBITOS Y STATIC " << std::endl;
    std::cout << "==========================================================" << std::endl;
    std::cout << "\n1. Estado inicial de clase (sin objetos):" << std::endl;
    std::cout << "   Sesiones activas: " << SesionRed::obtenerSesionesActivas() 
              << " / " << SesionRed::obtenerMaxSesiones() << std::endl;
    try {
        std::cout << "\n2. Creación de sesiones en ámbito del main:" << std::endl;
        SesionRed s1("admin_mendoza", "192.168.1.10");
        SesionRed s2("analista_garcia", "192.168.1.15");
        std::cout << "\n3. Demostración de ÁMBITO DE BLOQUE LOCAL { ... }:" << std::endl;
        { // Inicio de bloque local
            std::cout << "   ---> Entrando al bloque interno..." << std::endl;
            SesionRed s3("invitado_temporal", "10.0.0.5");
            std::cout << "   ---> Activas en bloque: " << SesionRed::obtenerSesionesActivas() << "\n";
            std::cout << "   ---> Saliendo del bloque interno..." << std::endl;
        } // s3 destruido automáticamente aquí por salir de ámbito local
        std::cout << "   ---> Fuera del bloque. Activas restantes: " 
                  << SesionRed::obtenerSesionesActivas() << std::endl;
        std::cout << "\n4. Intento de exceder el límite de sesiones (MAX=3):" << std::endl;
        SesionRed s4("operador_rodriguez", "192.168.1.20"); // Activa #3
        SesionRed s5("intruso_excedente", "10.0.0.99");     // Lanza excepción
    } catch (const std::exception& e) {
        std::cout << "\n [EXCEPCIÓN CAPTURADA EN MAIN] " << e.what() << std::endl;
    }
    std::cout << "\n5. Verificación final tras cierre de bloque try:" << std::endl;
    std::cout << "   Sesiones activas finales: " << SesionRed::obtenerSesionesActivas() << std::endl;
    return 0;
}