#include <iostream>
#include <string>
using namespace std;

class Persona {
	private:
	    string nombre; // Atributos privados para proteger el estado del objeto
	    int edad;
	public:
	    // 1. Constructor por defecto
	    // Se invoca automáticamente cuando declaramos un objeto sin argumentos.
	    // Garantiza un estado inicial coherente y evita valores "basura" en memoria.
	    Persona():
	        nombre("Desconocido"),
	        edad(0)
	    {
	        cout << "[Constructor por defecto llamado]" << endl;
	    }
	
	    // 2. Constructor parametrizado
	    // Permite al usuario instanciar el objeto con valores específicos desde el inicio.
	    // Emplea listas de inicialización para optimizar el rendimiento.
	    Persona(string nombre_val, int edad_val):
	        nombre(nombre_val),
	        edad(edad_val)
	    {
	        cout << "[Constructor parametrizado llamado]" << endl;
	    }
	
	    // 3. Constructor de copia
	    // Crea una nueva instancia duplicando de forma segura el estado de un objeto existente.
	    // Recibe obligatoriamente una referencia constante para evitar bucles infinitos de copia.
	    Persona(const Persona& otra):
	        nombre(otra.nombre),
	        edad(otra.edad)
	    {
	        cout << "[Constructor de copia llamado]" << endl;
	    }
	
	    // Método para imprimir el estado del objeto
	    void mostrar() const {
	        cout << "Nombre: " << nombre << ", Edad: " << edad << " anos" << endl << endl;
	    }
    	
};

int main(){

	cout << "--- Instanciando Persona 1 ---" << endl;
    Persona p1; // Se invoca automáticamente el constructor por defecto
    p1.mostrar();

    cout << "--- Instanciando Persona 2 ---" << endl;
    Persona p2("Juan", 25); // Se invoca el constructor parametrizado
    p2.mostrar();

    cout << "--- Instanciando Persona 3 ---" << endl;
    Persona p3 = p2; // Se invoca implícitamente el constructor de copia
    p3.mostrar();
	
	return 0;
}