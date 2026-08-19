#include <iostream>
#include <string>

using namespace std;

class Persona {
	string nombre="Daniel";
	int edad=10;
	
	public:
		string getNombre(){
			return nombre;
		}
		
		void setNombre(string valor){
			nombre = valor;
		}
		
		int getEdad(){
			return edad;
		}
};

int main(){
	
	Persona p;
	// p.setNombre("Paulo");
	cout << "Mi nombre es " << p.getNombre() << " y tengo " << p.getEdad() << " anios." ; 
	return 0;
}